#pragma once

#include "../state.h"

class	CStateChimeraCSHuntingComeOut : public CState {
protected:
	typedef CState inherited;

	enum {
		eStateMoveToCover,
		eStateComeOut
	};

public:
	CStateChimeraCSHuntingComeOut(CChimeraCS *obj);

	virtual	void		reselect_state				();
	virtual bool 		check_start_conditions		();	
	virtual bool 		check_completion			();	

	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};
