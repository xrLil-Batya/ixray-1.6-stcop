#pragma once

#include "../BaseMonster/base_monster.h"

class CChimeraCS : public CBaseMonster {
	typedef		CBaseMonster	inherited;

	bool		b_upper_state;

	SVelocityParam		m_fsVelocityWalkUpper;
	SVelocityParam		m_fsVelocityJumpGround;
	SVelocityParam		m_fsVelocityRunAttack;

public:
	CChimeraCS();
	virtual			~CChimeraCS();

	virtual void	Load				(LPCSTR section);
	virtual void	reinit				();
	virtual	void	UpdateCL			();

	virtual	void	SetTurnAnimation			(bool turn_left);
	virtual void	CheckSpecParams				(u32 spec_params);
	virtual	EAction	CustomVelocityIndex2Action	(u32 velocity_index);
	virtual	void	TranslateActionToPathParams ();
	virtual void	HitEntityInJump				(const CEntity *pEntity);

	virtual	char* get_monster_class_name()		{ return const_cast<char*>("chimera_cs"); }

	IC		void	SetUpperState				(bool state = true) {b_upper_state = state;}
	
	DECLARE_SCRIPT_REGISTER_FUNCTION
	
};
