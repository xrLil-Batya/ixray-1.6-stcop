#pragma once

#include "../state.h"

class CStateChimeraCSThreatenWalk : public CStateMonsterMoveToPointEx {
	typedef CStateMonsterMoveToPointEx		inherited;

public:
	IC					CStateChimeraCSThreatenWalk(_Object *obj) : inherited(obj){}
	virtual	void		initialize					();	
	virtual	void		execute						();
	virtual bool		check_completion			();
	virtual bool		check_start_conditions		();
	
};
