#pragma once

#include "../state.h"

class	CStateChimeraCSHuntingMoveToCover : public CState {
protected:
	typedef CState inherited;

public:
	CStateChimeraCSHuntingMoveToCover(CChimeraCS *obj);

	virtual void		initialize						();
	virtual	void		execute							();
	virtual bool 		check_completion				();

	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};
