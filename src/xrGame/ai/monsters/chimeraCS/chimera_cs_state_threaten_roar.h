#pragma once

#include "../state.h"

class CStateChimeraCSThreatenRoar : public CState {
	typedef CState		inherited;

public:
	IC					CStateChimeraCSThreatenRoar(_Object *obj) : inherited(obj){}
	
	virtual	void		initialize					();	
	virtual	void		execute						();
	virtual bool		check_completion			();
	virtual void		remove_links				(CObject* object) { inherited::remove_links(object);}
};
