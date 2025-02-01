#pragma once

#include "../state.h"

class	CStateChimeraCSHunting : public CState {
protected:
	typedef CState inherited;
	typedef CState* state_ptr;

	enum {
		eStateMoveToCover,
		eStateComeOut
	};

public:
	CStateChimeraCSHunting(CChimeraCS*obj);

	virtual	void		reselect_state			();
	virtual bool 		check_start_conditions	();	
	virtual bool 		check_completion		();	

};
