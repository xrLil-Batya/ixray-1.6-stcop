#include "stdafx.h"
#include "bloodsucker_soc.h"
#include "bloodsucker_soc_predator_lite.h"

#include "ai_object_location.h"
#include "../ai_monster_squad.h"
#include "../ai_monster_squad_manager.h"

#include "../states/state_move_to_point.h"
#include "../states/state_look_point.h"
#include "../states/state_custom_action.h"
#include "../../../cover_point.h"
#include "../monster_cover_manager.h"
#include "../monster_home.h"

#include "../../../actor.h"
#include "../../../actor_memory.h"
#include "../../../visual_memory_manager.h"

CStateBloodsuckerSoCPredatorLite::CStateBloodsuckerSoCPredatorLite(CBloodsuckerSoC* obj) : inherited(obj)
{
	m_pBloodsucker = smart_cast<CBloodsuckerSoC*>(object);

	add_state	(eStatePredator_Camp, new CStateMonsterCustomAction(obj));
	add_state	(eStatePredator_MoveToCover, new CStateMonsterMoveToPointEx(obj));
	add_state	(eStatePredator_LookOpenPlace, new CStateMonsterLookToPoint(obj));
}

void CStateBloodsuckerSoCPredatorLite::reinit()
{
	inherited::reinit	();
}

void CStateBloodsuckerSoCPredatorLite::initialize()
{
	inherited::initialize						();

	m_pBloodsucker->predator_start						();

	m_target_node								= u32(-1);
	m_freezed									= false;
}

void CStateBloodsuckerSoCPredatorLite::reselect_state()
{
	if (prev_substate == u32(-1)) {
		if (enemy_see_me()) select_state(eStatePredator_MoveToCover);
		else select_state(eStatePredator_LookOpenPlace);
		return;
	}

	if (prev_substate == eStatePredator_MoveToCover) {
		if (enemy_see_me()) {
			select_state(eStatePredator_MoveToCover);
			object->set_berserk();
		}
		else select_state(eStatePredator_LookOpenPlace);
		return;
	}
	
	if (prev_substate == eStatePredator_LookOpenPlace) {
		select_state(eStatePredator_Camp);
		return;
	}

	if (prev_substate == eStatePredator_Camp) {
		select_state(eStatePredator_MoveToCover);
		return;
	}

	select_state(eStatePredator_MoveToCover);
}

void CStateBloodsuckerSoCPredatorLite::finalize()
{
	inherited::finalize							();
	m_pBloodsucker->predator_stop						();
	if (m_freezed)	m_pBloodsucker->predator_unfreeze	();

	if (m_target_node != u32(-1)) 
		monster_squad().get_squad(object)->unlock_cover(m_target_node);
}

void CStateBloodsuckerSoCPredatorLite::critical_finalize()
{
	inherited::critical_finalize				();
	m_pBloodsucker->predator_stop						();
	if (m_freezed)	m_pBloodsucker->predator_unfreeze	();

	if (m_target_node != u32(-1)) 
		monster_squad().get_squad(object)->unlock_cover(m_target_node);
}

bool CStateBloodsuckerSoCPredatorLite::check_completion()
{
	if (object->EnemyMan.see_enemy_now() && (object->Position().distance_to(object->EnemyMan.get_enemy()->Position()) < 4.f)) {
		object->set_berserk();
		return true;
	}
	if (object->conditions().health() > 0.9f) return true;

	return false;
}

void CStateBloodsuckerSoCPredatorLite::setup_substates()
{
	state_ptr state = get_state_current();

	if (current_substate == eStatePredator_Camp) {
		m_pBloodsucker->predator_freeze		();
		m_freezed					= true;
	} else {
		m_pBloodsucker->predator_unfreeze	();
		m_freezed					= false;
	}

	if (current_substate == eStatePredator_MoveToCover) {
		select_camp_point		();
		
		SStateDataMoveToPointEx data;
		data.vertex				= m_target_node;
		data.point				= ai().level_graph().vertex_position(data.vertex);
		data.action.action		= ACT_RUN;
		data.action.time_out	= 0;		// do not use time out
		data.completion_dist	= 0.f;		// get exactly to the point
		data.time_to_rebuild	= 0;		// do not rebuild
		data.accelerated		= true;
		data.braking			= true;
		data.accel_type 		= eAT_Aggressive;
		data.action.sound_type	= MonsterSound::eMonsterSoundIdle;
		data.action.sound_delay = object->db().m_dwIdleSndDelay;

		state->fill_data_with(&data, sizeof(SStateDataMoveToPointEx));
		return;
	}

	if (current_substate == eStatePredator_LookOpenPlace) {

		SStateDataLookToPoint	data;

		Fvector dir;
		object->CoverMan->less_cover_direction(dir);

		data.point.mad			(object->Position(),dir,10.f);
		data.action.action		= ACT_STAND_IDLE;
		data.action.time_out	= 2000;		
		data.action.sound_type	= MonsterSound::eMonsterSoundIdle;
		data.action.sound_delay = object->db().m_dwIdleSndDelay;
		data.face_delay			= 0;

		state->fill_data_with(&data, sizeof(SStateDataLookToPoint));
		return;
	}

	if (current_substate == eStatePredator_Camp) {

		SStateDataAction data;

		data.action		= ACT_STAND_IDLE;
		data.time_out	= 0;			// do not use time out
		data.sound_type	= MonsterSound::eMonsterSoundIdle;
		data.sound_delay = object->db().m_dwIdleSndDelay;

		state->fill_data_with(&data, sizeof(SStateDataAction));

		return;
	}
}

#define TIME_TO_RESELECT_CAMP	15000

void CStateBloodsuckerSoCPredatorLite::check_force_state()
{
	if (prev_substate == eStatePredator_Camp) {
		if (object->HitMemory.get_last_hit_time() > time_state_started) {
			
			if (object->EnemyMan.get_enemy() && 
				(object->EnemyMan.get_enemy()->Position().distance_to(object->Position()) < 10.f)) {
				object->set_berserk	();
			} else 
				current_substate	= u32(-1);
			
		}
	}
}

void CStateBloodsuckerSoCPredatorLite::select_camp_point()
{
	if (m_target_node != u32(-1)) 
		monster_squad().get_squad(object)->unlock_cover(m_target_node);
	
	m_target_node = u32(-1);
	if (object->Home->has_home()) {
		m_target_node							= object->Home->get_place_in_cover();
		if (m_target_node == u32(-1)) {
			m_target_node						= object->Home->get_place();
		}
	} 

	if (m_target_node == u32(-1)) {
		const CCoverPoint	*point = object->CoverMan->find_cover(object->Position(),20.f,30.f);
		if (point) {
			m_target_node				= point->level_vertex_id	();
		} 
	}

	if (m_target_node == u32(-1)) 
		m_target_node = object->ai_location().level_vertex_id();

	monster_squad().get_squad(object)->lock_cover(m_target_node);
}

bool CStateBloodsuckerSoCPredatorLite::enemy_see_me()
{
	//if (object->EnemyMan.get_enemy() == Actor()) 
	//	return (Actor()->memory().visual().visible_now(object));

	// if I see enemy then probably enemy see me :-)
	return object->EnemyMan.enemy_see_me_now();
}


