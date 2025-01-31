#include "stdafx.h"

#include "../../../Level.h"
#include "../../../Actor.h"
#include "../../../ActorEffector.h"
#include "../../../Inventory.h"
#include "../../../HudItem.h"
#include "../../../../xrEngine/CustomHUD.h"

#include "IBloodsucker.h"

#include "bloodsucker_alien_pp.h"
#include "bloodsucker_alien.h"

#include "bloodsucker.h"

#include "bloodsucker_alien_effector.h"

#define EFFECTOR_ID_GEN(type) (type( u32(u64(this) & u32(-1)) ))

CBloodsuckerAlien::CBloodsuckerAlien()
{
	m_active = false;
	m_crosshair_show = false;
	m_effector = nullptr;
	m_effector_pp = nullptr;
	m_object	= nullptr;
}

CBloodsuckerAlien::~CBloodsuckerAlien()
{

}

void CBloodsuckerAlien::init_external(IBloodsucker* object)
{
	m_object	= object;
}

void CBloodsuckerAlien::reinit()
{
	m_active				= false;	
	m_crosshair_show		= false;
}

void CBloodsuckerAlien::activate()
{
	if (m_active) return;

	VERIFY	(Actor());

	m_object->exe_install			(Actor());
	m_object->exe_dont_need_turn	();

	if (!m_object->has_enemy())
		m_object->add_enemy(Actor());

//.	Actor()->inventory().setSlotsBlocked			(true);
	Actor()->SetWeaponHideState(INV_STATE_BLOCK_ALL, true);

	// hide crosshair
	m_crosshair_show			= !!psHUD_Flags.is(HUD_CROSSHAIR_RT);
	if (m_crosshair_show)		psHUD_Flags.set(HUD_CROSSHAIR_RT,FALSE);

	// Start effector
	m_effector_pp				= new CBloodsukerAlienEffectorPP	(any_cast<SPPInfo>(m_object->get_spp_info()), EFFECTOR_ID_GEN(EEffectorPPType));
	Actor()->Cameras().AddPPEffector	(m_effector_pp);
	
	m_effector					= new CBloodsukerAlienEffector(EFFECTOR_ID_GEN(ECamEffectorType), m_object);
	Actor()->Cameras().AddCamEffector	(m_effector);

	// make invisible
	//m_object->state_invisible	= true;
	m_object->set_state_invisible(true);
	//m_object->setVisible		(false);
	m_object->set_visible(false);

	m_active					= true;
}

void CBloodsuckerAlien::deactivate()
{
	if (!m_active) return;

	m_object->exe_release();

	Actor()->SetWeaponHideState(INV_STATE_BLOCK_ALL, false);
	if (m_crosshair_show)							psHUD_Flags.set(HUD_CROSSHAIR_RT,TRUE);

	// Stop camera effector
	Actor()->Cameras().RemoveCamEffector(EFFECTOR_ID_GEN(ECamEffectorType));
	m_effector						= 0;
	
	// Stop postprocess effector
	Actor()->Cameras().RemovePPEffector(EFFECTOR_ID_GEN(EEffectorPPType));
	m_effector_pp->Destroy			();
	m_effector_pp					= 0;

	m_active						= false;

	// make visible
	//m_object->state_invisible	= false;
	m_object->set_state_invisible(false);
	//m_object->setVisible		(true);
	m_object->set_visible(true);
}
