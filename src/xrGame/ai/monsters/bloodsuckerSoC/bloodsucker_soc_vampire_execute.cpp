#include "stdafx.h"
#include "../../../xrCore/_vector3d_ext.h"
#include "sound_player.h"
#include "../control_animation_base.h"
#include "../control_direction_base.h"
#include "ai_object_location.h"
#include "bloodsucker_soc.h"
#include "bloodsucker_soc_vampire_execute.h"

#include "../../../../Include/xrRender/KinematicsAnimated.h"
#include "../../../actor.h"
#include "../../../../xrEngine/CameraBase.h"

#include "../../../HudManager.h"

#define VAMPIRE_TIME_HOLD 4000
#define VAMPIRE_HIT_IMPULSE 40.f
#define VAMPIRE_MIN_DIST 0.5f
#define VAMPIRE_MAX_DIST 1.f

CStateBloodsuckerSoCVampireExecute::CStateBloodsuckerSoCVampireExecute(CBloodsuckerSoC* object) : inherited(object)
{
    pBloodsuckerBase = smart_cast<CBloodsuckerSoC*>(object);

    m_action = {};
    time_vampire_started = {};

    m_effector_activated = {};
}

CStateBloodsuckerSoCVampireExecute::~CStateBloodsuckerSoCVampireExecute()
{

}

void CStateBloodsuckerSoCVampireExecute::initialize()
{
    inherited::initialize();

    pBloodsuckerBase->CControlledActor::install();

    look_head();

    m_action = eActionPrepare;
    time_vampire_started = 0;

    HUD().SetRenderable(false);
    NET_Packet P;
    Actor()->u_EventGen(P, GEG_PLAYER_WEAPON_HIDE_STATE, Actor()->ID());
    P.w_u16(INV_STATE_BLOCK_ALL);
    P.w_u8(u8(true));
    Actor()->u_EventSend(P);

    Actor()->set_inventory_disabled(true);

    m_effector_activated = false;
}

void CStateBloodsuckerSoCVampireExecute::execute()
{
    if (!pBloodsuckerBase->CControlledActor::is_turning() && !m_effector_activated)
    {
        pBloodsuckerBase->ActivateVampireEffector();
        m_effector_activated = true;
    }

    look_head();

    switch (m_action)
    {
    case eActionPrepare:
        execute_vampire_prepare();
        m_action = eActionContinue;
        break;

    case eActionContinue: 
        execute_vampire_continue();
        break;

    case eActionFire:
        execute_vampire_hit();
        m_action = eActionWaitTripleEnd;
        break;

    case eActionWaitTripleEnd:
        if (!object->com_man().ta_is_active())
        {
            m_action = eActionCompleted;
        }

    case eActionCompleted:
        break;
    }

    object->dir().face_target(object->EnemyMan.get_enemy());

    Fvector const enemy_to_self = object->EnemyMan.get_enemy()->Position() - object->Position();
    float const dist_to_enemy = magnitude(enemy_to_self);
    float const vampire_dist = pBloodsuckerBase->get_vampire_distance();

    if (angle_between_vectors(object->Direction(), enemy_to_self) < deg2rad(20.f) && 
        dist_to_enemy > vampire_dist)
    {
        object->set_action(ACT_RUN);
        object->anim().accel_activate(eAT_Aggressive);
        object->anim().accel_set_braking(false);

        u32 const target_vertex = object->EnemyMan.get_enemy()->ai_location().level_vertex_id();
        Fvector const target_pos = ai().level_graph().vertex_position(target_vertex);

        object->path().set_target_point(target_pos, target_vertex);
        object->path().set_rebuild_time(100);
        object->path().set_use_covers(false);
        object->path().set_distance_to_end(vampire_dist);
    }
    else
    {
        object->set_action(ACT_STAND_IDLE);
    }
}

void CStateBloodsuckerSoCVampireExecute::show_hud()
{
    HUD().SetRenderable(true);
    NET_Packet P;

    Actor()->u_EventGen(P, GEG_PLAYER_WEAPON_HIDE_STATE, Actor()->ID());
    P.w_u16(INV_STATE_BLOCK_ALL);
    P.w_u8(u8(false));
    Actor()->u_EventSend(P);
}

void CStateBloodsuckerSoCVampireExecute::cleanup()
{
    Actor()->set_inventory_disabled(false);

    if (object->com_man().ta_is_active())
        object->com_man().ta_deactivate();

    if (pBloodsuckerBase->CControlledActor::is_controlling())
        pBloodsuckerBase->CControlledActor::release();

    if (IsGameTypeSingle())
        show_hud();
}

void CStateBloodsuckerSoCVampireExecute::finalize()
{
    inherited::finalize();
    cleanup();
}

void CStateBloodsuckerSoCVampireExecute::critical_finalize()
{
    inherited::critical_finalize();
    cleanup();
}

//bool CStateBloodsuckerSoCVampireExecute::check_start_conditions()
//{
//    const CEntityAlive* enemy = object->EnemyMan.get_enemy();
//
//    float dist = object->MeleeChecker.distance_to_enemy(enemy);
//
//    if (Device.dwTimeGlobal < m_cooldown_time)
//    {
//        return false;
//    }
//
//    if ((dist > VAMPIRE_MAX_DIST) || (dist < VAMPIRE_MIN_DIST))					
//    {
//        Msg("2");
//        return false;
//    }
//
//    if (pBloodsuckerBase->CControlledActor::is_controlling())
//    {
//        Msg("3");
//        return false;
//    }
//
//    if (current_substate == eStateAttack_RunAttack)							
//    {
//        Msg("4");
//        return false;
//    }
//
//    if (pBloodsuckerBase->threaten_time() > 0)
//    {
//        Msg("5");
//        return false;
//    }
//
//    const CActor* m_actor = smart_cast<const CActor*>(enemy);
//
//    VERIFY(m_actor);
//
//    if (m_actor->input_external_handler_installed())						
//    {
//        Msg("6");
//        return false;
//    }
//
//    //if (b_controlling_value)
//    //{
//    //    Msg("7");
//    //    return false;
//    //}
//
//    if (!object->control().direction().is_face_target(enemy, PI_DIV_6))				
//    {
//        Msg("8");
//        return false;
//    }
//
//    return true;
//
//    //return (rand() % 2 == 0) ? false : true;
//}

bool CStateBloodsuckerSoCVampireExecute::check_start_conditions()
{
    const CEntityAlive* enemy = object->EnemyMan.get_enemy();

    float dist = object->MeleeChecker.distance_to_enemy(enemy);

    if ((dist > VAMPIRE_MAX_DIST) || (dist < VAMPIRE_MIN_DIST))					
        return false;

    u32 const vertex_id = ai().level_graph().check_position_in_direction(object->ai_location().level_vertex_id(),
        object->Position(), enemy->Position());

    if (!ai().level_graph().valid_vertex_id(vertex_id))
        return false;

    if (!object->MeleeChecker.can_start_melee(enemy))
        return false;

    if (!object->control().direction().is_face_target(enemy, PI_DIV_2))
        return false;

    if (!pBloodsuckerBase->WantVampire())
        return false;

    if (!smart_cast<CActor const*>(enemy))
        return false;

    if (pBloodsuckerBase->is_controlling())
        return false;

    const CActor* actor = smart_cast<const CActor*>(enemy);

    VERIFY(actor);

    if (actor->input_external_handler_installed())
        return false;

    return true;
}

bool CStateBloodsuckerSoCVampireExecute::check_completion() { return (m_action == eActionCompleted); }

void CStateBloodsuckerSoCVampireExecute::execute_vampire_prepare()
{
    object->com_man().ta_activate(pBloodsuckerBase->anim_triple_vampire);
    time_vampire_started = Device.dwTimeGlobal;

    object->sound().play(CBloodsuckerSoC::eVampireGrasp);
}

void CStateBloodsuckerSoCVampireExecute::execute_vampire_continue()
{
    const CEntityAlive* enemy = object->EnemyMan.get_enemy();

    if (!object->MeleeChecker.can_start_melee(enemy))
    {
        object->com_man().ta_deactivate();
        m_action = eActionCompleted;

        return;
    }

    object->sound().play(CBloodsuckerSoC::eVampireSucking);

    if (time_vampire_started + VAMPIRE_TIME_HOLD < Device.dwTimeGlobal)
    {
        m_action = eActionFire;
    }
}

void CStateBloodsuckerSoCVampireExecute::execute_vampire_hit()
{
    object->com_man().ta_pointbreak();
    object->sound().play(CBloodsuckerSoC::eVampireHit);
    pBloodsuckerBase->SatisfyVampire();
}

void CStateBloodsuckerSoCVampireExecute::look_head()
{
    IKinematics* pK = smart_cast<IKinematics*>(object->Visual());
    Fmatrix bone_transform = pK->LL_GetTransform(pK->LL_BoneID("bip01_head"));

    Fmatrix global_transform;
    global_transform.mul_43(object->XFORM(), bone_transform);

    pBloodsuckerBase->CControlledActor::look_point(global_transform.c);
}
