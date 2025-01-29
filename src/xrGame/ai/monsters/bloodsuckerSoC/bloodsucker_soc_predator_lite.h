#pragma once
#include "../state.h"

class	CStateBloodsuckerSoCPredatorLite : public CState {
	typedef CState		inherited;
	typedef CState*	state_ptr;

	u32							m_target_node;
	bool						m_freezed;

	CBloodsuckerSoC* m_pBloodsucker;

public:
						CStateBloodsuckerSoCPredatorLite		(CBloodsuckerSoC* obj);

	virtual void		reinit							();

	virtual void		initialize						();
	virtual	void		reselect_state					();
	virtual	void		finalize						();
	virtual	void		critical_finalize				();
	virtual bool		check_completion				();
	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }

	virtual void		setup_substates					();
	virtual void		check_force_state				();

private:
			void		select_camp_point				();
			bool		enemy_see_me					();

};
