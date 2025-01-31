#pragma once

class CBloodsukerAlienEffector : public CEffectorCam
{
protected:
	using inherited = CEffectorCam;

	float	m_time_total;
	Fvector	dangle_target;
	Fvector dangle_current;

	IBloodsucker* object;

	float		m_current_fov;
	Fmatrix		m_prev_eye_matrix;
	float		m_inertion;

public:
	CBloodsukerAlienEffector(ECamEffectorType type, IBloodsucker* object);
	virtual ~CBloodsukerAlienEffector() override;

	virtual BOOL	ProcessCam(SCamEffectorInfo& info) override;
};