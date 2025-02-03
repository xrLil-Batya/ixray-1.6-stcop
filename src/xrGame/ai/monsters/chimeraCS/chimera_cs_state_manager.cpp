#include "stdafx.h"

#include "chimera_cs.h"
#include "chimera_cs_state_manager.h"

#include "../control_animation_base.h"
#include "../control_direction_base.h"
#include "../control_movement_base.h"
#include "../control_path_builder_base.h"

#include "../states/monster_state_rest.h"
#include "../states/monster_state_attack.h"
#include "../states/monster_state_panic.h"
#include "../states/monster_state_eat.h"
#include "../states/monster_state_hear_int_sound.h"
#include "../states/monster_state_hear_danger_sound.h"
#include "../states/monster_state_hitted.h"
#include "../states/monster_state_attack_melee.h"
#include "../states/monster_state_attack_run.h"
#include "chimera_cs_state_threaten.h"
#include "chimera_cs_state_attack_run.h"

CStateManagerChimeraCS::CStateManagerChimeraCS(CChimeraCS* obj) : inherited(obj)
{
	add_state(eStateRest, new CStateMonsterRest(obj));
	add_state(eStatePanic, new CStateMonsterPanic(obj));
	add_state(eStateAttack, new CStateChimeraCSAttackRun(obj));
	add_state(eStateEat, new CStateMonsterEat(obj));
	add_state(eStateHearInterestingSound, new CStateMonsterHearInterestingSound(obj));
	add_state(eStateHearDangerousSound, new CStateMonsterHearDangerousSound(obj));
	add_state(eStateHitted, new CStateMonsterHitted(obj));
	add_state(eStateThreaten, new CStateChimeraCSThreaten(obj));
}

CStateManagerChimeraCS::~CStateManagerChimeraCS()
{

}

void CStateManagerChimeraCS::execute()
{
	u32 state_id = u32(-1);

	const CEntityAlive* enemy	= object->EnemyMan.get_enemy	();

	if (enemy) 
	{
		switch (object->EnemyMan.get_danger_type()) 
		{
			case eStrong:	
				state_id = eStatePanic; break;
			case eWeak:		
				state_id = eStateAttack; break;
		}
	} 
	else if (object->HitMemory.is_hit()) 
	{
		state_id = eStateHitted;
	} 
	else if (object->hear_dangerous_sound) 
	{
		state_id = eStateHearDangerousSound;
	} 
	else if (object->hear_interesting_sound)
	{
		state_id = eStateHearInterestingSound;
	} 
	else
	{
		if (can_eat())	
			state_id = eStateEat;
		else			
			state_id = eStateRest;
	}
	
	select_state(state_id); 

	get_state_current()->execute();

	prev_substate = current_substate;
}

