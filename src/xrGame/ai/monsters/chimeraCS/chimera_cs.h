#pragma once

#include "../BaseMonster/base_monster.h"

class CChimeraCS : public CBaseMonster 
{
	using		inherited = CBaseMonster;

	bool		b_upper_state;

	SVelocityParam		m_fsVelocityWalkUpper;
	SVelocityParam		m_fsVelocityJumpGround;
	SVelocityParam		m_fsVelocityRunAttack;

public:
	CChimeraCS();
	virtual			~CChimeraCS() override;

	virtual void	Load				(LPCSTR section) override;
	virtual void	reinit				() override;
	virtual	void	UpdateCL			() override;

	virtual	void	SetTurnAnimation			(bool turn_left) override;
	virtual void	CheckSpecParams				(u32 spec_params) override;
	virtual	EAction	CustomVelocityIndex2Action	(u32 velocity_index) override;
	virtual	void	TranslateActionToPathParams () override;
	virtual void	HitEntityInJump				(const CEntity *pEntity) override;

	virtual	char* get_monster_class_name()		override { return const_cast<char*>("chimera_cs"); }

	inline		void	SetUpperState				(bool state = true) { b_upper_state = state; }
	
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
