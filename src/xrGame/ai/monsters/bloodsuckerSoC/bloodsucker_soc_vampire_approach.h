#pragma once
#include "../state.h"

class CStateBloodsuckerSoCVampireApproach : public CState
{
    typedef CState inherited;

public:
    CStateBloodsuckerSoCVampireApproach(CBloodsuckerSoC* obj);
    virtual ~CStateBloodsuckerSoCVampireApproach() override;

    virtual void initialize() override;
    virtual void execute() override;

    virtual void remove_links(CObject* object) override { inherited::remove_links(object); }
};
