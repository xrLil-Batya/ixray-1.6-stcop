#include "StdAfx.h"
#include "chimera_cs_state_hunting_move_to_cover.h"

CStateChimeraCSHuntingMoveToCover::CStateChimeraCSHuntingMoveToCover(CChimeraCS *obj) : inherited(obj)
{
}

void CStateChimeraCSHuntingMoveToCover::initialize()
{
	inherited::initialize();
}

bool CStateChimeraCSHuntingMoveToCover::check_completion()
{
	return false;
}

void CStateChimeraCSHuntingMoveToCover::execute()
{
	
}
