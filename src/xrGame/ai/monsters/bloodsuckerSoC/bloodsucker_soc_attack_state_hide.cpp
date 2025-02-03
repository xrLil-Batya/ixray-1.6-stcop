#include "stdafx.h"

#include "../basemonster/base_monster.h"

#include "../../../Actor.h"
#include "../bloodsucker/IBloodsucker.h"

#include "../control_animation_base.h"
#include "../control_direction_base.h"

#include "ai_object_location.h"

#include "../ai_monster_squad.h"
#include "../ai_monster_squad_manager.h"

#include "bloodsucker_soc.h"
#include "bloodsucker_soc_attack_state.h"
#include "bloodsucker_soc_vampire_execute.h"
#include "bloodsucker_soc_attack_state_hide.h"

#include "../states/state_move_to_point.h"

#include "bloodsucker_soc_predator_lite.h"

#include "../../../cover_point.h"
#include "../monster_cover_manager.h"
#include "../monster_home.h"

CBloodsuckerSoCStateAttackHide::CBloodsuckerSoCStateAttackHide(CBloodsuckerSoC *obj) : inherited(obj)
{
	m_pBloodsucker = smart_cast<CBloodsuckerSoC*>(object);
	
	m_target_node = {};

	add_state	(eStateAttack_HideInCover, new CStateMonsterMoveToPointEx (obj));
	add_state	(eStateAttack_CampInCover, new CStateBloodsuckerSoCPredatorLite(obj));
}

CBloodsuckerSoCStateAttackHide::~CBloodsuckerSoCStateAttackHide()
{

}

void CBloodsuckerSoCStateAttackHide::reinit()
{
	inherited::reinit	();
}

void CBloodsuckerSoCStateAttackHide::initialize()
{
	inherited::initialize	();

	m_target_node			= u32(-1);

	m_pBloodsucker->start_invisible_predator();
}

void CBloodsuckerSoCStateAttackHide::reselect_state()
{
	if (prev_substate == u32(-1)) 
	{
		select_state(eStateAttack_HideInCover);
		return;
	}

	select_state(eStateAttack_CampInCover);
}

void CBloodsuckerSoCStateAttackHide::finalize()
{
	inherited::finalize							();

	if (m_target_node != u32(-1))
		monster_squad().get_squad(object)->unlock_cover(m_target_node);
}

void CBloodsuckerSoCStateAttackHide::critical_finalize()
{
	inherited::critical_finalize				();

	if (m_target_node != u32(-1))
		monster_squad().get_squad(object)->unlock_cover(m_target_node);
}

bool CBloodsuckerSoCStateAttackHide::check_completion()
{
	if (current_substate == eStateAttack_CampInCover)
		return (get_state_current()->check_completion());

	return false;
}

void CBloodsuckerSoCStateAttackHide::setup_substates()
{
	state_ptr state = get_state_current();

	if (current_substate == eStateAttack_HideInCover) 
	{
		select_camp_point();

		SStateDataMoveToPointEx data;

		data.vertex				= m_target_node;
		data.point				= ai().level_graph().vertex_position(data.vertex);
		data.action.action		= ACT_RUN;
		data.action.time_out	= 0;
		data.completion_dist	= 0.f;
		data.time_to_rebuild	= 0;
		data.accelerated		= true;
		data.braking			= true;
		data.accel_type 		= eAT_Aggressive;
		data.action.sound_type	= MonsterSound::eMonsterSoundIdle;
		data.action.sound_delay = object->db().m_dwIdleSndDelay;

		state->fill_data_with(&data, sizeof(SStateDataMoveToPointEx));
		return;
	}
}

void CBloodsuckerSoCStateAttackHide::check_force_state()
{

}

void CBloodsuckerSoCStateAttackHide::select_camp_point()
{
	if (m_target_node != u32(-1))
		monster_squad().get_squad(object)->unlock_cover(m_target_node);

	m_target_node = u32(-1);

	if (object->Home->has_home()) 
	{
		m_target_node							= object->Home->get_place_in_cover();

		if (m_target_node == u32(-1)) 
		{
			m_target_node						= object->Home->get_place();
		}
	} 

	if (m_target_node == u32(-1)) 
	{
		const CCoverPoint	*point = object->CoverMan->find_cover(object->Position(),10.f,30.f);

		if (point) 
		{
			m_target_node				= point->level_vertex_id	();
		} 
	}

	if (m_target_node == u32(-1)) 
		m_target_node = object->ai_location().level_vertex_id();

	monster_squad().get_squad(object)->lock_cover(m_target_node);
}


