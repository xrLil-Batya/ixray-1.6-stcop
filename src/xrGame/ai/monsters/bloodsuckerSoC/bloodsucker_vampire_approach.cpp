#include "stdafx.h"

#include "../control_animation_base.h"
#include "../control_direction_base.h"

#include "ai_object_location.h"

#include "bloodsucker.h"
#include "bloodsucker_vampire_approach.h"

CStateBloodsuckerSoCVampireApproach::CStateBloodsuckerSoCVampireApproach(CBloodsuckerSoC* obj) : inherited(obj) {}

CStateBloodsuckerSoCVampireApproach::~CStateBloodsuckerSoCVampireApproach() {}

void CStateBloodsuckerSoCVampireApproach::initialize()
{
    inherited::initialize();
    object->path().prepare_builder();
}

void CStateBloodsuckerSoCVampireApproach::execute()
{
    // установка параметров функциональных блоков
    object->set_action(ACT_RUN);
    object->anim().accel_activate(eAT_Aggressive);
    object->anim().accel_set_braking(false);

    u32 const target_vertex = object->EnemyMan.get_enemy()->ai_location().level_vertex_id();
    Fvector const target_pos = ai().level_graph().vertex_position(target_vertex);

    object->path().set_target_point(target_pos, target_vertex);
    object->path().set_rebuild_time(object->get_attack_rebuild_time());
    object->path().set_use_covers(false);
    object->path().set_distance_to_end(0.1f);
    object->set_state_sound(MonsterSound::eMonsterSoundAggressive);
}