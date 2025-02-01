#pragma once

#include "../state.h"

class	CStateChimeraCSHuntingComeOut : public CState {
protected:
	typedef CState inherited;

public:
	CStateChimeraCSHuntingComeOut(CChimeraCS *obj);

	virtual	void		reselect_state				();
	virtual bool 		check_start_conditions		();	
	virtual bool 		check_completion			();	

};
