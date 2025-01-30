#pragma once

#include "../../../../xrEngine/effectorPP.h"
#include "../../../CameraEffector.h"
#include "../../../../xrEngine/cameramanager.h"

class CVampirePPEffectsocor : public CEffectorPP
{
    typedef CEffectorPP inherited;

    SPPInfo state;
    float m_total;

public:
    CVampirePPEffectsocor(const SPPInfo& ppi, float life_time);

    virtual BOOL Process(SPPInfo& pp);
};

class CVampireCameraEffectorsoc : public CEffectorCam
{
    typedef CEffectorCam inherited;

    float m_time_total;
    Fvector dangle_target;
    Fvector dangle_current;

    float m_dist;
    Fvector m_direction;

public:
    CVampireCameraEffectorsoc(float time, const Fvector& src, const Fvector& tgt);

    virtual BOOL ProcessCam(SCamEffectorInfo& info);
};
