#include "stdafx.h"
#include "bloodsucker_soc_state_manager.h"
#include "bloodsucker_soc.h"

#include "../control_animation_base.h"
#include "../control_direction_base.h"
#include "../control_movement_base.h"
#include "../control_path_builder_base.h"

#include "../states/monster_state_rest.h"
#include "../states/monster_state_attack.h"
#include "../states/monster_state_panic.h"
#include "../states/monster_state_eat.h"
#include "../states/monster_state_hear_int_sound.h"
#include "../states/monster_state_hitted.h"

#include "bloodsucker_soc_predator.h"
#include "bloodsucker_soc_vampire_execute.h"

#include "bloodsucker_soc_attack_state.h"

CStateManagerBloodsuckerSoC::CStateManagerBloodsuckerSoC(CBloodsuckerSoC* monster) : inherited(monster)
{
	pBloodsuckerBase = smart_cast<CBloodsuckerSoC*>(object);

	add_state(eStateRest, new CStateMonsterRest(monster));
	add_state(eStatePanic, new CStateMonsterPanic(monster));
	add_state(eStateAttack, new CBloodsuckerSoCStateAttack(monster));
	add_state(eStateEat, new CStateMonsterEat(monster));
	add_state(eStateHearInterestingSound, new CStateMonsterHearInterestingSound(monster));
	add_state(eStateHitted, new CStateMonsterHitted(monster));
	add_state(eStateVampire_Execute, new CStateBloodsuckerSoCVampireExecute(monster));
}

CStateManagerBloodsuckerSoC::~CStateManagerBloodsuckerSoC()
{

}

bool CStateManagerBloodsuckerSoC::check_vampire()
{
	if (prev_substate != eStateVampire_Execute)
	{
		if (get_state(eStateVampire_Execute)->check_start_conditions())
			return true;
	}
	else
	{
		if (!get_state(eStateVampire_Execute)->check_completion())
			return true;
	}
	return false;
}

void CStateManagerBloodsuckerSoC::execute()
{
	u32 state_id = u32(-1);

	const CEntityAlive* enemy	= object->EnemyMan.get_enemy();
	
	if (enemy) 
	{
		if (check_vampire())
		{
			state_id = eStateVampire_Execute;
		}
		else
		{

			switch (object->EnemyMan.get_danger_type()) 
			{
			case eStrong:	state_id = eStatePanic; break;
			case eWeak:		state_id = eStateAttack; break;
			}
		}
	} 
	else if (object->HitMemory.is_hit()) 
	{
		state_id = eStateHitted;
	} 
	else if (object->hear_dangerous_sound || object->hear_interesting_sound) 
	{
		state_id = eStateHearInterestingSound;
	} 
	else 
	{
		if (can_eat())	state_id = eStateEat;
		else			state_id = eStateRest;
	}

	if ((prev_substate != eStateHearInterestingSound) && (state_id == eStateHearInterestingSound))
	{
		pBloodsuckerBase->predator_start();
	} 
	else if ((prev_substate == eStateHearInterestingSound) && (state_id != eStateHearInterestingSound)) 
	{
		pBloodsuckerBase->predator_stop();
	}

	select_state(state_id); 

	if ((current_substate == eStateAttack) && (current_substate != prev_substate)) 
	{
		pBloodsuckerBase->predator_stop();
		pBloodsuckerBase->start_threaten = true;
	}

	get_state_current()->execute();

	prev_substate = current_substate;
}
