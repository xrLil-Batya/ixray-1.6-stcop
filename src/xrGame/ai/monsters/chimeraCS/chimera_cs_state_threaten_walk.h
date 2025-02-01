#pragma once

#include "../state.h"

class CStateChimeraCSThreatenWalk : public CStateMonsterMoveToPointEx {
	typedef CStateMonsterMoveToPointEx		inherited;

	CChimeraCS* pChimeraCS;

public:
						CStateChimeraCSThreatenWalk(CChimeraCS* obj);
						virtual ~CStateChimeraCSThreatenWalk() override;

	virtual	void		initialize					();	
	virtual	void		execute						();
	virtual bool		check_completion			();
	virtual bool		check_start_conditions		();
	
};
