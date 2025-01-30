#pragma once
#include "../state.h"

class CStateBloodsuckerSoCVampireHide : public CState
{
    typedef CState inherited;
    typedef CState* state_ptr;

public:
    CStateBloodsuckerSoCVampireHide(CBloodsuckerSoC* obj);
    virtual ~CStateBloodsuckerSoCVampireHide() override;

    virtual void reselect_state() override;
    virtual void setup_substates() override;

    virtual bool check_completion() override;
    virtual void remove_links(CObject* object) override { inherited::remove_links(object); }
};
