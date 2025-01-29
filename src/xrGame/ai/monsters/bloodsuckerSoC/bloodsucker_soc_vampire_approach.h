#pragma once
#include "../state.h"

class CStateBloodsuckerSoCVampireApproach : public CState
{
    typedef CState inherited;

public:
    CStateBloodsuckerSoCVampireApproach(CBloodsuckerSoC* obj);
    virtual ~CStateBloodsuckerSoCVampireApproach();

    virtual void initialize();
    virtual void execute();
    virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};
