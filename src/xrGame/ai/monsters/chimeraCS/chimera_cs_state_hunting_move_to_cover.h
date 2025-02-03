#pragma once

#include "../state.h"

class	CStateChimeraCSHuntingMoveToCover : public CState 
{
protected:
	using inherited = CState;

public:
	CStateChimeraCSHuntingMoveToCover(CChimeraCS *obj);
	virtual ~CStateChimeraCSHuntingMoveToCover() override;

	virtual void		initialize						() override;
	virtual	void		execute							() override;
	virtual bool 		check_completion				() override;

	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};
