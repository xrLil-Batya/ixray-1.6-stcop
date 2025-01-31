#pragma once

class IBloodsucker;
class CBloodsukerAlienEffector;
class CBloodsukerAlienEffectorPP;

class CBloodsuckerAlien
{
protected:
	IBloodsucker*				m_object;
	
	bool						m_active;

	CBloodsukerAlienEffector*m_effector;
	CBloodsukerAlienEffectorPP*m_effector_pp;
	
	bool						m_crosshair_show;

public:
	CBloodsuckerAlien();
	~CBloodsuckerAlien();
	
	void	init_external		(IBloodsucker* object);
	void	reinit				();

	void	activate			();
	void	deactivate			();

	bool	active				() { return m_active; }
};