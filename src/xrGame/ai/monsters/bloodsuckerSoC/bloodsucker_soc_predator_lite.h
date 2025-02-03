#pragma once
#include "../state.h"

class	CStateBloodsuckerSoCPredatorLite : public CState 
{
	using inherited = CState		;
	using state_ptr = CState*;

	u32							m_target_node;
	bool						m_freezed;

	CBloodsuckerSoC* m_pBloodsucker;

public:
						CStateBloodsuckerSoCPredatorLite		(CBloodsuckerSoC* obj);
						virtual ~CStateBloodsuckerSoCPredatorLite() override;

	virtual void		reinit							() override;

	virtual void		initialize						() override;
	virtual	void		reselect_state					() override;
	virtual	void		finalize						() override;
	virtual	void		critical_finalize				() override;
	virtual bool		check_completion				() override;
	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }

	virtual void		setup_substates					() override;
	virtual void		check_force_state				() override;

private:
			void		select_camp_point				();
			bool		enemy_see_me					();
};
