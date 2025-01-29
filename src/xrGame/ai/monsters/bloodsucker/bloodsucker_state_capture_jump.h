#pragma once

#include "../state.h"

class	CBloodsukerStateJump : public CState 
{
protected:
	using inherited = CState;
	using state_ptr = CState*;

public:
	CBloodsukerStateJump(CBloodsuckerBase* object);
	virtual				~CBloodsukerStateJump() override;

	virtual	void		execute() override;
	virtual void		setup_substates() override;
	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};
