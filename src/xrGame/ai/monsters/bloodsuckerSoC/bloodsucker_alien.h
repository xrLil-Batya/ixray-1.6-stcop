#pragma once

class CAI_Bloodsucker;
class CAlienEffectsoc;
class CAlienEffectsocPP;

class CBloodsuckerAlien {
	
	CAI_Bloodsucker			*m_object;
	
	bool						m_active;

	CAlienEffectsoc				*m_effector;
	CAlienEffectsocPP			*m_effector_pp;
	
	bool						m_crosshair_show;

public:
			CBloodsuckerAlien	();
			~CBloodsuckerAlien	();
	
	void	init_external		(CAI_Bloodsucker *obj);	
	void	reinit				();

	void	activate			();
	void	deactivate			();

	bool	active				() {return m_active;}

};