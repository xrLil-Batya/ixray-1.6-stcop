#pragma once

#include "../state.h"

class CStateChimeraCSThreatenSteal : public CStateMonsterMoveToPointEx {
	typedef CStateMonsterMoveToPointEx		inherited;

public:
	IC					CStateChimeraCSThreatenSteal(_Object *obj) : inherited(obj){}
	virtual	void		initialize					();	
	virtual void		finalize					();
	virtual	void		execute						();
	virtual bool		check_completion			();
	virtual bool		check_start_conditions		();
};
