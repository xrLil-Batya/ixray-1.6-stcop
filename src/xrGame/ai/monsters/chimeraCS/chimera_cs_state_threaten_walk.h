#pragma once

#include "../state.h"

class CStateChimeraCSThreatenWalk : public CStateMonsterMoveToPointEx 
{
	using inherited = CStateMonsterMoveToPointEx;

	CChimeraCS* pChimeraCS;

public:
	CStateChimeraCSThreatenWalk(CChimeraCS* obj);
	virtual ~CStateChimeraCSThreatenWalk() override;

	virtual	void		initialize					() override;
	virtual	void		execute						() override;
	virtual bool		check_completion			() override;
	virtual bool		check_start_conditions		() override;
};
