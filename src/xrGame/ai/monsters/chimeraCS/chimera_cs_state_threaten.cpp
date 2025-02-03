#include "StdAfx.h"

#include "../states/state_move_to_point.h"

#include "chimera_cs.h"
#include "chimera_cs_state_threaten.h"

#include "chimera_cs_state_threaten_steal.h"
#include "chimera_cs_state_threaten_walk.h"
#include "chimera_cs_state_threaten_roar.h"

CStateChimeraCSThreaten::CStateChimeraCSThreaten(CChimeraCS *obj) : inherited(obj)
{
	pChimeraCS = smart_cast<CChimeraCS*>(obj);

	m_last_time_threaten = {};

	add_state(eStateWalk,		new CStateChimeraCSThreatenWalk	(obj));
	add_state(eStateThreaten,	new CStateChimeraCSThreatenRoar	(obj));
	add_state(eStateSteal,		new CStateChimeraCSThreatenSteal (obj));
}

CStateChimeraCSThreaten::~CStateChimeraCSThreaten()
{

}

void CStateChimeraCSThreaten::reinit()
{
	inherited::reinit	();

	m_last_time_threaten = 0;
}

#define MIN_DIST_TO_ENEMY	3.f
#define MORALE_THRESHOLD	0.8f
#define THREATEN_DELAY		10000

bool CStateChimeraCSThreaten::check_start_conditions()
{
	if (object->tfGetRelationType(object->EnemyMan.get_enemy()) == ALife::eRelationTypeWorstEnemy) 
		return false;

	if (object->Position().distance_to(object->EnemyMan.get_enemy_position()) < MIN_DIST_TO_ENEMY) 
		return false;

	if (object->HitMemory.is_hit())						
		return false;

	if (object->hear_dangerous_sound)					
		return false;

	if (m_last_time_threaten + THREATEN_DELAY > Device.dwTimeGlobal) 
		return false;

	return true;
}

bool CStateChimeraCSThreaten::check_completion()
{
	if (object->Position().distance_to(object->EnemyMan.get_enemy_position()) < MIN_DIST_TO_ENEMY)
		return true;

	if (object->HitMemory.is_hit()) 
		return true;

	if (object->tfGetRelationType(object->EnemyMan.get_enemy()) == ALife::eRelationTypeWorstEnemy) 
		return true;

	return false;
}

void CStateChimeraCSThreaten::initialize()
{
	inherited::initialize	();
	pChimeraCS->SetUpperState	();
}

void CStateChimeraCSThreaten::reselect_state()
{
	if (prev_substate == u32(-1)) 
	{
		select_state(eStateThreaten);
		return;
	}

	if (prev_substate == eStateSteal) 
	{
		select_state(eStateThreaten);
		return;
	}

	if (prev_substate == eStateThreaten) 
	{
		if (get_state(eStateSteal)->check_start_conditions()) 
		{
			select_state(eStateSteal);
			return;
		} 
		else if (get_state(eStateWalk)->check_start_conditions()) 
		{
			select_state(eStateWalk);
			return;
		}
	}

	select_state(eStateThreaten);
}

void CStateChimeraCSThreaten::finalize()
{
	inherited::finalize		();

	pChimeraCS->SetUpperState	(false);
	m_last_time_threaten	 = Device.dwTimeGlobal;
}

void CStateChimeraCSThreaten::critical_finalize()
{
	inherited::critical_finalize();

	pChimeraCS->SetUpperState	(false);
	m_last_time_threaten	 = Device.dwTimeGlobal;
}
