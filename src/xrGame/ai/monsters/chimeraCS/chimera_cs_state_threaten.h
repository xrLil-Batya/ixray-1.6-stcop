#pragma once

#include "../state.h"

class	CStateChimeraCSThreaten : public CState 
{
protected:
	using inherited = CState;
	using state_ptr = CState*;

	enum 
	{
		eStateWalk			= u32(0),
		eStateFaceEnemy,
		eStateThreaten,
		eStateSteal
	};

	u32					m_last_time_threaten;

	CChimeraCS* pChimeraCS;

public:
	CStateChimeraCSThreaten(CChimeraCS *obj);
	virtual				~CStateChimeraCSThreaten() override;

	virtual void		reinit					() override;

	virtual	void		initialize				() override;

	virtual	void		reselect_state			() override;
	virtual void 		finalize				() override;
	virtual void 		critical_finalize		() override;
	virtual bool 		check_start_conditions	() override;
	virtual bool 		check_completion		() override;

	virtual void        remove_links(CObject* object) override { inherited::remove_links(object); }
};
