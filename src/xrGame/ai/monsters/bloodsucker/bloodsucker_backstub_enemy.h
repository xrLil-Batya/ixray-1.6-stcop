#pragma once
#include "../states/monster_state_attack.h"

class CBloodsukerBackstubEnemy : public CState
{
protected:
	using inherited = CState;

public:
	struct StateParams : SStateDataMoveToPointEx
	{
		bool   start_with_encircle;
		StateParams() : start_with_encircle(false) {}
	} data;

protected:
	float                   m_last_health;
	bool                    m_encircle;
	TTime                   m_encircle_end_tick;
	TTime                   m_next_change_behaviour_tick;

public:
	CBloodsukerBackstubEnemy(CBloodsuckerBase* object);
	virtual				~CBloodsukerBackstubEnemy() override;

	virtual void		initialize() override;
	virtual	void		execute() override;
	virtual bool 		check_start_conditions() override;
	virtual bool		check_completion() override;
	virtual void		remove_links(CObject* object) override { inherited::remove_links(object); }
};