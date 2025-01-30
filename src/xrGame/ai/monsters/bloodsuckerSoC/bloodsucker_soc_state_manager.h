#pragma once
#include "../monster_state_manager.h"

class CBloodsuckerSoC;

class CStateManagerBloodsuckerSoC : public CMonsterStateManager
{
	typedef CMonsterStateManager inherited;

	CBloodsuckerSoC* pBloodsuckerBase;

public:
					CStateManagerBloodsuckerSoC (CBloodsuckerSoC* monster);
					virtual ~CStateManagerBloodsuckerSoC() override;

	virtual void	execute						() override;
	virtual void	remove_links				(CObject* object) override { inherited::remove_links(object); }
	bool			check_vampire();
};
