#pragma once

#include "../state.h"

class CStateChimeraCSThreatenSteal : public CStateMonsterMoveToPointEx 
{
	using inherited = CStateMonsterMoveToPointEx;

	CChimeraCS* pChimeraCS;

public:
	CStateChimeraCSThreatenSteal(CChimeraCS* obj);
	virtual ~CStateChimeraCSThreatenSteal() override;

	virtual	void		initialize					() override;
	virtual void		finalize					() override;
	virtual	void		execute						() override;
	virtual bool		check_completion			() override;
	virtual bool		check_start_conditions		() override;
};
