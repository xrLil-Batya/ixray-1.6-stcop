#pragma once

#include "../state.h"

class CStateChimeraCSAttackRun : public CState 
{
	using inherited = CState;
	using state_ptr = CState*	;
	
	TTime				m_time_action_change;
	EAction				action;

public:
	CStateChimeraCSAttackRun(CChimeraCS*obj);
	virtual				~CStateChimeraCSAttackRun() override;

	virtual void		initialize				() override;
	virtual	void		execute					() override;
	virtual void		finalize				() override;
	virtual void		critical_finalize		() override;

			bool		check_home_point		();

	virtual void		remove_links			(CObject* object) override { inherited::remove_links(object);}

private:
	        void		choose_action			();
};
