#pragma once
#include "../state.h"

class	CBloodsuckerSoCStateAttackHide : public CState {
	typedef CState		inherited;
	typedef CState*	state_ptr;

	u32							m_target_node;

	CBloodsuckerSoC* m_pBloodsucker;

public:
	CBloodsuckerSoCStateAttackHide(CBloodsuckerSoC* obj);
	virtual ~CBloodsuckerSoCStateAttackHide() override;

	virtual void		reinit							() override;

	virtual void		initialize						() override;
	virtual	void		reselect_state					() override;
	virtual	void		finalize						() override;
	virtual	void		critical_finalize				() override;
	virtual bool		check_completion				() override;

	virtual void		setup_substates					() override;
	virtual void		check_force_state				() override;

private:
	void		select_camp_point				();
};
