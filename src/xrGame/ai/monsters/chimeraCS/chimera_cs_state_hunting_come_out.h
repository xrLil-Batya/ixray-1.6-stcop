#pragma once

#include "../state.h"

class	CStateChimeraCSHuntingComeOut : public CState 
{
protected:
	using inherited = CState;

	enum 
	{
		eStateMoveToCover,
		eStateComeOut
	};

public:
	CStateChimeraCSHuntingComeOut(CChimeraCS *obj);
	virtual ~CStateChimeraCSHuntingComeOut() override;

	virtual	void		reselect_state				() override;
	virtual bool 		check_start_conditions		() override;
	virtual bool 		check_completion			() override;

	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};
