#include "StdAfx.h"
#include "chimera_cs.h"

#include "../states/state_move_to_point.h"

#include "chimera_cs_state_threaten_steal.h"

CStateChimeraCSThreatenSteal::CStateChimeraCSThreatenSteal(CChimeraCS* obj) : inherited(obj)
{
	pChimeraCS = smart_cast<CChimeraCS*>(obj);
}

CStateChimeraCSThreatenSteal::~CStateChimeraCSThreatenSteal()
{

}

void CStateChimeraCSThreatenSteal::initialize()
{
	inherited::initialize();
	
	pChimeraCS->SetUpperState	(false);

	data.action.action		= ACT_STEAL;
	
	data.accelerated		= true;
	data.braking			= false;
	data.accel_type 		= eAT_Calm;
	
	data.completion_dist	= 2.f;
	data.action.sound_type	= MonsterSound::eMonsterSoundIdle;
	data.action.sound_delay = object->db().m_dwIdleSndDelay;
}

void CStateChimeraCSThreatenSteal::finalize()
{
	inherited::finalize();
	pChimeraCS->SetUpperState	();
}

void CStateChimeraCSThreatenSteal::execute()
{
	data.point				= object->EnemyMan.get_enemy_position	();
	data.vertex				= object->EnemyMan.get_enemy_vertex		();
	data.time_to_rebuild	= object->get_attack_rebuild_time		();

	inherited::execute();
}

#define MIN_DISTANCE_TO_ENEMY	8.f

bool CStateChimeraCSThreatenSteal::check_completion()
{	
	if (inherited::check_completion()) return true;
	
	float dist_to_enemy = object->EnemyMan.get_enemy_position().distance_to(object->Position());
	if (dist_to_enemy < MIN_DISTANCE_TO_ENEMY) return true;

	return false;
}

bool CStateChimeraCSThreatenSteal::check_start_conditions()
{
	float dist_to_enemy = object->EnemyMan.get_enemy_position().distance_to(object->Position());
	if (dist_to_enemy > MIN_DISTANCE_TO_ENEMY) return true;
	return false;
}
