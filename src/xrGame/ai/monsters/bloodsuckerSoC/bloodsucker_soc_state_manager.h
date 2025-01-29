#pragma once
#include "../monster_state_manager.h"

class CBloodsuckerSoC;

class CStateManagerBloodsuckerSoC : public CMonsterStateManager
{
	typedef CMonsterStateManager inherited;

	CBloodsuckerSoC* pBloodsuckerBase;

public:
					CStateManagerBloodsuckerSoC (CBloodsuckerSoC* monster);
	virtual void	execute						();
	virtual void	remove_links				(CObject* object) { inherited::remove_links(object); }
	bool			check_vampire();
};
