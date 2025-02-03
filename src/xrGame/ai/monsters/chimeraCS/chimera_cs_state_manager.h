#pragma once

#include "../monster_state_manager.h"

class CStateManagerChimeraCS : public CMonsterStateManager 
{
	using inherited = CMonsterStateManager;

public:
	CStateManagerChimeraCS(CChimeraCS*obj);
	virtual				~CStateManagerChimeraCS() override;

	virtual	void		execute					() override;
    virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};

