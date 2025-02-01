#pragma once

#include "../state.h"

class	CStateChimeraCSHuntingMoveToCover : public CState {
protected:
	typedef CState inherited;

public:
	CStateChimeraCSHuntingMoveToCover(CChimeraCS *obj);

	virtual void		initialize						();
	virtual	void		execute							();
	virtual bool 		check_start_conditions			();
	virtual bool 		check_completion				();
};
