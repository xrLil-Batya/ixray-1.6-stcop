#pragma once

#include "../../../../xrEngine/effectorPP.h"
#include "../../../CameraEffector.h"
#include "../../../../xrEngine/cameramanager.h"

class CBloodsukerVampireCameraEffector : public CEffectorCam
{
protected:
	using inherited = CEffectorCam;

	float	m_time_total;
	Fvector	dangle_target;
	Fvector dangle_current;

	float	m_dist;
	Fvector m_direction;

public:
	CBloodsukerVampireCameraEffector(float time, const Fvector& src, const Fvector& tgt);
	virtual				~CBloodsukerVampireCameraEffector();

	virtual BOOL	ProcessCam(SCamEffectorInfo& info) override;
};