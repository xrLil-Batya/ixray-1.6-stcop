#pragma once
#include "../states/monster_state_attack.h"

class	CBloodsuckerStateAttack : public CStateMonsterAttack {
	typedef CStateMonsterAttack inherited_attack;

	u32				m_time_stop_invis;
	Fvector			m_dir_point;

public:
					CBloodsuckerStateAttack		(_Object *obj);
	virtual			~CBloodsuckerStateAttack	();

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

#include "bloodsucker_attack_state_inline.h"
