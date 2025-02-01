#pragma once

#include "../state.h"

class CStateChimeraCSThreatenSteal : public CStateMonsterMoveToPointEx {
	typedef CStateMonsterMoveToPointEx		inherited;

	CChimeraCS* pChimeraCS;

public:
						CStateChimeraCSThreatenSteal(CChimeraCS* obj);
						virtual ~CStateChimeraCSThreatenSteal() override;

	virtual	void		initialize					();	
	virtual void		finalize					();
	virtual	void		execute						();
	virtual bool		check_completion			();
	virtual bool		check_start_conditions		();
};
