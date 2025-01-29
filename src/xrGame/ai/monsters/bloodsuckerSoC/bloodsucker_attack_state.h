#pragma once
#include "../states/monster_state_attack.h"

class	CBloodsuckerSoCStateAttack : public CStateMonsterAttack {
	typedef CStateMonsterAttack inherited_attack;

	u32				m_time_stop_invis;
	Fvector			m_dir_point;

public:
	CBloodsuckerSoCStateAttack(CBloodsuckerSoC* obj);
	virtual			~CBloodsuckerSoCStateAttack();

	virtual	void	initialize					();
	virtual	void	execute						();
	virtual	void	finalize					();
	virtual	void	critical_finalize			();
	
	virtual void	setup_substates				();
private:
			void	update_invisibility			();
			bool	check_hiding				();
			bool	check_vampire				();
};
