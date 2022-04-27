#include "main.h"
#include "Particle.h"
#include "effect.h"
#include "texture.h"

#include <stdio.h>
#include <stdlib.h> // move, smoveä÷êî
#include <time.h>   // timeä÷êî

int CParticle::m_nTime;
CParticle::CParticle()
{
	
}

CParticle::~CParticle()
{

}

void CParticle::SetParticle(void)
{
	srand((unsigned int)time(NULL));
	float move = 0.1;
	//éûä‘Çâ¡éZ
	m_nTime++;
	//for (int nCntEffect = 0; nCntEffect < 1; nCntEffect++)
	{
		if (m_nTime >= 50)
		{
			//ägéU
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,1.0f,     move), D3DXVECTOR3(3.0f, 3.0f,  1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0  ,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.75f, 0.25f,  move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0   ,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.75f, 0.25f, move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0   ,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f, 0.5f,    move), D3DXVECTOR3(3.0f, 3.0f,    1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f,0.5f,    move), D3DXVECTOR3(3.0f, 3.0f,   1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0 ,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.25f, 0.75f,  move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0   ,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.25f,0.75f,  move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0   ,CTexture::Text);
																					  
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,  -1.0f,  move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f,  -0.5f,  move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, -0.5f,  move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.25f, -0.75f, move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.25f,-0.75f, move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3( 0.75f, -0.25f,move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);
			CEffect::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.75f, -0.25f,move), D3DXVECTOR3(3.0f, 3.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0,CTexture::Text);

			m_nTime = 0;
		}
	}
}