#pragma once

class IBloodsucker
{
public:
    virtual bool get_state_invisible() = 0;
    virtual void set_state_invisible(bool val) = 0;

    virtual void set_visible(bool val) = 0;

    virtual void exe_release() = 0;

    virtual void exe_install(xr_any_type actor) = 0;

    virtual void exe_dont_need_turn() = 0;

    virtual bool has_enemy() = 0;
    virtual void add_enemy(xr_any_type actor) = 0;

    virtual xr_any_type get_spp_info() const = 0;

    virtual Fvector exe_get_head_position(CObject* object) = 0;

    virtual IBloodsucker* get_class_object() = 0;

    virtual float get_cur_speed() = 0;
};