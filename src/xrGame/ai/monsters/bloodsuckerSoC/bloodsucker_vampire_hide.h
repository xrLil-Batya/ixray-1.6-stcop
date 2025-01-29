#pragma once
#include "../state.h"

class CStateBloodsuckerSoCVampireHide : public CState
{
    typedef CState inherited;
    typedef CState* state_ptr;

public:
    CStateBloodsuckerSoCVampireHide(CBloodsuckerSoC* obj);

    virtual void reselect_state();
    virtual void setup_substates();
    virtual bool check_completion();
    virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};
