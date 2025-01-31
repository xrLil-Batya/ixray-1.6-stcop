#include "stdafx.h"

#include "../basemonster/base_monster.h"

#include "../../../Actor.h"
#include "IBloodsucker.h"

#include "actor.h"
#include "sound_player.h"
#include "bloodsucker.h"

#include "bloodsucker_vampire.h"

#include "bloodsucker_vampire_execute.h"
#include "../states/state_hide_from_point.h"
#include "bloodsucker_vampire_approach.h"
#include "bloodsucker_vampire_hide.h"

CBloodsukerStateVampire::CBloodsukerStateVampire(CBloodsuckerBase* object) : inherited(object)
{
	enemy = nullptr;

	pBloodsuckerBase = smart_cast<CBloodsuckerBase*>(object);

	add_state	(eStateVampire_ApproachEnemy,	new CBloodsukerVampireApproach(object));
	add_state	(eStateVampire_Execute,			new CBloodsukerStateVampireExecute(object));
	add_state	(eStateVampire_RunAway,			new CStateMonsterHideFromPoint		(object));
	add_state	(eStateVampire_Hide,			new CBloodsukerStateVampireHide(object));
}

CBloodsukerStateVampire::~CBloodsukerStateVampire()
{

}

void CBloodsukerStateVampire::reinit()
{
	inherited::reinit	();
}

void CBloodsukerStateVampire::initialize()
{
	inherited::initialize						();
	pBloodsuckerBase->set_visibility_state				(CBloodsuckerBase::partial_visibility);

	enemy	= object->EnemyMan.get_enemy		();

	pBloodsuckerBase->sound().play						(CBloodsuckerBase::eVampireStartHunt);
}

void CBloodsukerStateVampire::reselect_state()
{
	u32 state_id = u32(-1);
		
	// check if we can start execute
	if (prev_substate == eStateVampire_ApproachEnemy) {
		if (get_state(eStateVampire_Execute)->check_start_conditions())	
			state_id = eStateVampire_Execute;
	}

	// check if we executed 
	if (prev_substate == eStateVampire_Execute)
		state_id = eStateVampire_Hide;
	
	// check if reach time in vampire state is out - then hide
	if (prev_substate == eStateVampire_ApproachEnemy)
		state_id = eStateVampire_Hide;

	// check if we hiding - then hide again
	if (prev_substate == eStateVampire_Hide)
		state_id = eStateVampire_Hide;

	// else just 
	if (state_id == u32(-1)) state_id = eStateVampire_ApproachEnemy;

	select_state(state_id);
}

void CBloodsukerStateVampire::check_force_state()
{
	// check if we can start execute
	if (prev_substate == eStateVampire_ApproachEnemy) {
		if (get_state(eStateVampire_Execute)->check_start_conditions())
			current_substate = u32(-1);
	}
}

void CBloodsukerStateVampire::finalize()
{
	inherited::finalize();

	pBloodsuckerBase->set_visibility_state	(CBloodsuckerBase::full_visibility);
	CBloodsuckerBase::m_time_last_vampire				= Device.dwTimeGlobal;
}

void CBloodsukerStateVampire::critical_finalize()
{
	inherited::critical_finalize	();
	
	pBloodsuckerBase->set_visibility_state	(CBloodsuckerBase::full_visibility);
	CBloodsuckerBase::m_time_last_vampire				= Device.dwTimeGlobal;
}

bool CBloodsukerStateVampire::check_start_conditions()
{
	if (!pBloodsuckerBase->WantVampire()) return false;
	if (object->berserk_always) return false;
	
	// является ли враг актером
	const CEntityAlive *enemy = object->EnemyMan.get_enemy();
	if (!smart_cast<CActor const*>(enemy))			return false;
	if (!object->EnemyMan.see_enemy_now())			return false;
	if (pBloodsuckerBase->is_controlling())	return false;

	const CActor *actor = smart_cast<const CActor *>(enemy);
	VERIFY(actor);
	if (actor->input_external_handler_installed()) return false;

	if (CBloodsuckerBase::m_time_last_vampire + pBloodsuckerBase->m_vampire_min_delay > Device.dwTimeGlobal) return false;

	return true;
}

bool CBloodsukerStateVampire::check_completion()
{
	// если убежал
	if ((current_substate == eStateVampire_Hide) &&
		get_state_current()->check_completion())	return true;

	// если враг изменился
	if (enemy != object->EnemyMan.get_enemy())		return true;
	
	// если актера уже контролит другой кровосос
	if ((current_substate != eStateVampire_Execute) &&
		pBloodsuckerBase->is_controlling())	return true;

	return false;
}

void CBloodsukerStateVampire::setup_substates()
{
	state_ptr state = get_state_current();

	if (current_substate == eStateVampire_RunAway) {

		SStateHideFromPoint		data{};
		data.point				= object->EnemyMan.get_enemy_position();
		data.accelerated		= true;
		data.braking			= false;
		data.accel_type			= eAT_Aggressive;
		data.distance			= EntityDefinitions::CBloodsuckerBase::RUN_AWAY_DISTANCE;
		data.action.action		= ACT_RUN;
		data.action.sound_type	= MonsterSound::eMonsterSoundAggressive;
		data.action.sound_delay = object->db().m_dwAttackSndDelay;
		data.action.time_out	= 15000;

		state->fill_data_with(&data, sizeof(SStateHideFromPoint));

		return;
	}
}

void CBloodsukerStateVampire::remove_links	(CObject* object)
{
	if (enemy == object)
		enemy					= nullptr;
}