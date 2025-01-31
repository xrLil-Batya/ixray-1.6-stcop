#include "stdafx.h"

#include "../basemonster/base_monster.h"

#include "../../../Actor.h"
#include "IBloodsucker.h"

#include "bloodsucker.h"
#include "bloodsucker_state_capture_jump.h"

#include "../control_animation_base.h"
#include "../control_direction_base.h"

#include "../states/state_custom_action.h"

CBloodsukerStateJump::CBloodsukerStateJump(CBloodsuckerBase* object) : inherited(object)
{
	add_state(eStateCustom, new CStateMonsterCustomAction(object));
}

CBloodsukerStateJump::~CBloodsukerStateJump()
{

}

void CBloodsukerStateJump::execute()
{
	select_state(eStateCustom);

	get_state_current()->execute();
	prev_substate = current_substate;
}

void CBloodsukerStateJump::setup_substates()
{
	state_ptr state = get_state_current();
	if (current_substate == eStateCustom) {
		SStateDataAction data{};

		data.action = ACT_STAND_IDLE;
		data.time_out = 0;			// do not use time out
		/*data.sound_type	= MonsterSound::eMonsterSoundIdle;
		data.sound_delay = object->db().m_dwIdleSndDelay;
		*/
		state->fill_data_with(&data, sizeof(SStateDataAction));

		return;
	}
}
