#pragma once

#include "../monster_state_manager.h"

class CChimeraCS;

class CStateManagerChimeraCS : public CMonsterStateManager<CChimeraCS> {
	
	typedef CMonsterStateManager<CChimeraCS> inherited;

public:
	CStateManagerChimeraCS(CChimeraCS*obj);
	virtual				~CStateManagerChimeraCS();

	virtual	void		execute					();
    virtual void		remove_links(CObject* object) { inherited::remove_links(object); }
};

