#include "StdAfx.h"
#include "chimera_cs.h"
#include "chimera_cs_state_attack_run.h"

#include "../states/monster_state_attack_run.h"
#include "../states/monster_state_home_point_attack.h"
#include "../states/monster_state_attack_melee.h"

CStateChimeraCSAttackRun::CStateChimeraCSAttackRun(CChimeraCS* obj) : inherited(obj)
{
	add_state(eStateAttack_MoveToHomePoint,	new CStateMonsterAttackMoveToHomePoint(obj));	
 	add_state(eStateAttack_Run,				new CStateMonsterAttackRun			(obj));
 	add_state(eStateAttack_Melee,			new CStateMonsterAttackMelee			(obj));	
}

CStateChimeraCSAttackRun::~CStateChimeraCSAttackRun()
{
}

bool CStateChimeraCSAttackRun::check_home_point_cs()
{
	if (prev_substate != eStateAttack_MoveToHomePoint) {
		if (get_state(eStateAttack_MoveToHomePoint)->check_start_conditions())	return true;
	} else {
		if (!get_state(eStateAttack_MoveToHomePoint)->check_completion())		return true;
	}

	return false;
}

void CStateChimeraCSAttackRun::initialize()
{
	inherited::initialize			();
}

void CStateChimeraCSAttackRun::execute()
{
	object->anim().clear_override_animation	();
	
	if	( check_home_point_cs() )
	{
		select_state					(eStateAttack_MoveToHomePoint);
		get_state_current()->execute	();
		prev_substate				=	current_substate;
		return;
	}	
	
	EMonsterState		state_id	=	eStateUnknown;
	const CEntityAlive* enemy		=	object->EnemyMan.get_enemy();

	if (current_substate == eStateAttack_Melee)
	{
		if (get_state(eStateAttack_Melee)->check_completion())
			state_id = eStateAttack_Run;
		else
			state_id = eStateAttack_Melee;
	}
	else
	{
		if ( get_state(eStateAttack_Melee)->check_start_conditions() )
			state_id = eStateAttack_Melee;
		else
			state_id = eStateAttack_Run;
	}
	
	select_state						(state_id);
	get_state_current()->execute		();
	prev_substate					=	current_substate;	
	
}

void CStateChimeraCSAttackRun::choose_action()
{
}

void CStateChimeraCSAttackRun::finalize_cs()
{
	inherited::finalize();
}

void CStateChimeraCSAttackRun::critical_finalize_cs()
{
	inherited::critical_finalize();
}
