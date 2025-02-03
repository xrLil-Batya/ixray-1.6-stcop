#pragma once

#include "../state.h"

class CStateChimeraCSThreatenRoar : public CState 
{
	using inherited = CState;

public:
	CStateChimeraCSThreatenRoar(CChimeraCS* obj);
	virtual ~CStateChimeraCSThreatenRoar() override;

	virtual	void		initialize					() override;
	virtual	void		execute						() override;
	virtual bool		check_completion			() override;
	virtual void		remove_links				(CObject* object) { inherited::remove_links(object);}
};
