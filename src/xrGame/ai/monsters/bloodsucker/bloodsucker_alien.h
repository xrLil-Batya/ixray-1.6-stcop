#pragma once

class CBloodsuckerBase;
class CBloodsukerAlienEffector;
class CBloodsukerAlienEffectorPP;

class CBloodsukerAlien
{
protected:
	CBloodsuckerBase			*m_object;
	
	bool						m_active;

	CBloodsukerAlienEffector*m_effector;
	CBloodsukerAlienEffectorPP*m_effector_pp;
	
	bool						m_crosshair_show;

public:
	CBloodsukerAlien();
	~CBloodsukerAlien();
	
	void	init_external		(CBloodsuckerBase* object);
	void	reinit				();

	void	activate			();
	void	deactivate			();

	bool	active				() {return m_active;}
};