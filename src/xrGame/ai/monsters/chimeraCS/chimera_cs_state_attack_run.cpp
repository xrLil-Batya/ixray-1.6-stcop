#include "StdAfx.h"
#include "chimera_cs_state_attack_run.h"

CStateChimeraCSAttackRun::CStateChimeraCSAttackRun(CChimeraCS* obj) : inherited(obj)
{
	add_state(eStateAttack_MoveToHomePoint,	new CStateMonsterAttackMoveToHomePoint(obj));	
 	add_state(eStateAttack_Run_chimera,				new CStateMonsterAttackRun			(obj));
 	add_state(eStateAttack_Melee_chimera,			new CStateMonsterAttackMelee			(obj));	
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

	if (current_substate == eStateAttack_Melee_chimera)
	{
		if (get_state(eStateAttack_Melee_chimera)->check_completion())
			state_id = eStateAttack_Run_chimera;
		else
			state_id = eStateAttack_Melee_chimera;
	}
	else
	{
		if ( get_state(eStateAttack_Melee_chimera)->check_start_conditions() )
			state_id = eStateAttack_Melee_chimera;
		else
			state_id = eStateAttack_Run_chimera;
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
