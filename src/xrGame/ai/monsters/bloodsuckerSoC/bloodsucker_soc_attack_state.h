#pragma once
#include "../states/monster_state_attack.h"

class	CBloodsuckerSoCStateAttack : public CStateMonsterAttack
{
	using inherited_attack = CStateMonsterAttack;

	u32				m_time_stop_invis;
	Fvector			m_dir_point;

	CBloodsuckerSoC* m_pBloodsucker;

public:
	CBloodsuckerSoCStateAttack(CBloodsuckerSoC* obj);
	virtual			~CBloodsuckerSoCStateAttack() override;

	virtual	void	initialize					() override;
	virtual	void	execute						() override;
	virtual	void	finalize					() override;
	virtual	void	critical_finalize			() override;
	
	virtual void	setup_substates				() override;

private:
			void	update_invisibility			();
			bool	check_hiding				();
			bool	check_vampire				();
};
