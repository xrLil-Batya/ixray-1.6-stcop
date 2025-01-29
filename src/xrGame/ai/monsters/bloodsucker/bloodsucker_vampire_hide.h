#pragma once
#include "../state.h"

class CBloodsukerStateVampireHide : public CState 
{
protected:
	using inherited = CState;
	using state_ptr = CState*;

public:
	CBloodsukerStateVampireHide(CBloodsuckerBase* object);
	virtual ~CBloodsukerStateVampireHide() override;

	virtual	void		reselect_state() override;
	virtual void		setup_substates() override;
	virtual bool		check_completion() override;
	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};

