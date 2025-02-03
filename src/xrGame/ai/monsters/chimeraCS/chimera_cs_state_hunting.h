#pragma once

#include "../state.h"

class	CStateChimeraCSHunting : public CState 
{
protected:
	using inherited = CState;
	using state_ptr = CState*;

	enum 
	{
		eStateMoveToCover,
		eStateComeOut
	};

public:
	CStateChimeraCSHunting(CChimeraCS*obj);

	virtual	void		reselect_state			() override;
	virtual bool 		check_start_conditions	() override;
	virtual bool 		check_completion		() override;
};
