#pragma once

class CBloodsuckerSoC;
class CAlienEffectsoc;
class CAlienEffectsocPP;

class CBloodsuckerSoCAlien 
{
	CBloodsuckerSoC* m_object;
	
	bool						m_active;

	CAlienEffectsoc				*m_effector;
	CAlienEffectsocPP			*m_effector_pp;
	
	bool						m_crosshair_show;

public:
	CBloodsuckerSoCAlien();
	~CBloodsuckerSoCAlien();
	
	void	init_external		(CBloodsuckerSoC* obj);
	void	reinit				();

	void	activate			();
	void	deactivate			();

	bool	active				() { return m_active; }
};