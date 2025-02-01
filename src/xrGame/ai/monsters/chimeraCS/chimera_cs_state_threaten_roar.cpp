#include "StdAfx.h"
#include "chimera_cs_state_threaten_roar.h"

void CStateChimeraCSThreatenRoar::initialize()
{
	inherited::initialize	();

}

void CStateChimeraCSThreatenRoar::execute()
{
	object->set_action				(ACT_STAND_IDLE);
	object->anim().SetSpecParams	(ASP_THREATEN);
	object->set_state_sound			(MonsterSound::eMonsterSoundThreaten);
	object->dir().face_target		(object->EnemyMan.get_enemy(), 1200);
}

#define STATE_TIME_OUT	4000

bool CStateChimeraCSThreatenRoar::check_completion()
{	
	if (time_state_started + STATE_TIME_OUT < Device.dwTimeGlobal) return true;
	return false;
}
