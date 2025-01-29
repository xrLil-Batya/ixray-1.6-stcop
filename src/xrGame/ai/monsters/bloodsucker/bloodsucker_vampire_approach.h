#pragma once
#include "../state.h"

class CBloodsukerVampireApproach : public CState
{
protected:
	using inherited = CState;

public:
	CBloodsukerVampireApproach(CBloodsuckerBase* object);
	virtual				~CBloodsukerVampireApproach() override;

	virtual void		initialize() override;
	virtual	void		execute() override;
	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};

