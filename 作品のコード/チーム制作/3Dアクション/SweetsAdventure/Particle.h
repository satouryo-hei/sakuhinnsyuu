#ifndef _PARTICLE_H_
#define _PARTICLE_H_

class CParticle
{
public:
	CParticle();
	~CParticle();
	static void SetParticle();
private:
	static int m_nTime;
	
};


#endif // !_PARTICLE_H_

