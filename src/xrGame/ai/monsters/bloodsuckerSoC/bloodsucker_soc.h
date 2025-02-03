#pragma once

#include "../basemonster/base_monster.h"
#include "../ai_monster_bones.h"
#include "../controlled_entity.h"
#include "../controlled_actor.h"
#include "../anim_triple.h"
#include "../../../../xrScripts/script_export_space.h"
#include "../bloodsucker/bloodsucker_alien.h"

class CBloodsuckerSoC : public CBaseMonster,
						public CControlledActor, public IBloodsucker
{
	using inherited =		CBaseMonster	;
	
public:
	CBloodsuckerSoC();
	virtual					~CBloodsuckerSoC() override;

	virtual void			reinit					() override;
	virtual	void			reload					(LPCSTR section) override;

	virtual void			UpdateCL				() override;
	virtual void			shedule_Update			(u32 dt) override;
	virtual void			Die						(CObject* who) override;
	virtual BOOL			net_Spawn				(CSE_Abstract* DC) override;
	virtual	void			Load					(LPCSTR section) override;

	virtual	void			CheckSpecParams			(u32 spec_params) override;
	virtual bool			ability_invisibility	() override {return true;}
	virtual bool			ability_pitch_correction() override {return false;}
	virtual	void			post_fsm_update			() override;
	
	virtual bool			use_center_to_aim		() const override {return true;}
	virtual bool			check_start_conditions	(ControlCom::EControlType) override;
	virtual void			on_activate_control		(ControlCom::EControlType) override;
			void			HitEntity				(const CEntity *pEntity, float fDamage, float impulse, Fvector &dir);
	
			void			move_actor_cam			();

private:
	static	void	    	BoneCallback			(CBoneInstance *B);
			void			vfAssignBones			();
			
	bonesManipulation		Bones;

	CBoneInstance			*bone_spine;
	CBoneInstance			*bone_head;

private:
	SMotionVel				invisible_vel;
	LPCSTR					invisible_particle_name;

public:
			void			start_invisible_predator	();
			void			stop_invisible_predator		();
			u32				threaten_time				() {return m_threaten_time;}

public:
	u32 m_vampire_min_delay;
	static u32 m_time_last_vampire;
	SAnimationTripleData anim_triple_vampire;
	SPPInfo pp_vampire_effector;
	void ActivateVampireEffector();
	bool WantVampire();
	void SatisfyVampire();

private:
	float m_vampire_want_value;
	float m_vampire_want_speed;
	float m_vampire_wound;
	float m_vampire_gain_health;
	float m_vampire_distance;
	void LoadVampirePPEffector(LPCSTR section);

	u32					m_threaten_time;	

public:
	CBloodsuckerAlien		m_alien_control;
	u32						m_time_lunge;
	
	CBloodsuckerSoC* pBloodsuckerSoC;

	void set_alien_control(bool val);

	virtual bool get_state_invisible() override 
	{
		return this->state_invisible
			;
	};

	virtual void set_state_invisible(bool val) override 
	{
		this->state_invisible = val;
	};

	virtual void set_visible(bool val) override 
	{
		this->setVisible(val);
	};

	virtual void exe_release() override 
	{
		this->release();
	}

	virtual void exe_install(xr_any_type actor) override 
	{
		if (actor.has_value()) 
		{
			if (auto* pActor = any_cast<CActor*>(actor)) 
			{
				this->install(pActor);
			}
		}
	};

	virtual void exe_dont_need_turn() override
	{
		this->dont_need_turn();
	}

	virtual bool has_enemy() override 
	{ 
		return this->EnemyMan.get_enemy(); 
	}

	virtual void add_enemy(xr_any_type actor) override
	{
		if (actor.has_value())
		{
			if (auto* pEnemy = any_cast<CEntityAlive*>(actor))
			{
				this->EnemyMan.add_enemy(pEnemy);
			}
		}
	};

	virtual xr_any_type get_spp_info() const override 
	{ 
		return pp_vampire_effector; 
	}

	virtual IBloodsucker* get_class_object() 
	{
		return pBloodsuckerSoC;
	};

	virtual Fvector exe_get_head_position(CObject* object) 
	{ 
		return get_head_position(object); 
	};

	virtual float get_cur_speed() override 
	{
		return this->m_fCurSpeed;
	}

public:
	shared_str				m_visual_default;
	LPCSTR					m_visual_predator;
	bool					m_predator;
			
			void			predator_start			();
			void			predator_stop			();
			void			predator_freeze			();
			void			predator_unfreeze		();
	
public:

	enum EBloodsuckerSounds 
	{
		eAdditionalSounds		= MonsterSound::eMonsterSoundCustom,
		eGrowl					= eAdditionalSounds | 1,
		eChangeVisibility		= eAdditionalSounds | 2,
		eAlien					= eAdditionalSounds | 3,
		eVampireGrasp			= eAdditionalSounds | 4,
		eVampireSucking			= eAdditionalSounds | 5,
		eVampireHit				= eAdditionalSounds | 6,
		eVampireStartHunt		= eAdditionalSounds | 7,
	};

public:
			void	set_manual_control	(bool value) {}
			void	manual_activate		();
			void	manual_deactivate	();
			bool	start_threaten;
			float	get_vampire_distance() const { return m_vampire_distance; }
			virtual	char* get_monster_class_name() override { return const_cast<char*>("bloodsucker_soc"); }

			DECLARE_SCRIPT_REGISTER_FUNCTION
public:
	virtual bool	can_be_seen				() const override { return !state_invisible; }
};
