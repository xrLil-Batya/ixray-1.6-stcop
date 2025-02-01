#pragma once

#include "../state.h"

class CStateChimeraCSAttackRun : public CState {
	typedef CState inherited;
	typedef CState*	state_ptr;
	
	TTime				m_time_action_change;
	EAction				action;

public:
	CStateChimeraCSAttackRun(CChimeraCS*obj);
	virtual				~CStateChimeraCSAttackRun();

	virtual void		initialize				();
	virtual	void		execute					();
	virtual void		finalize_cs				();
	virtual void		critical_finalize_cs	();
			bool		check_home_point_cs		();	
	virtual void		remove_links			(CObject* object) { inherited::remove_links(object);}

private:
	        void		choose_action			();

};
