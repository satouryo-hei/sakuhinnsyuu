#include "main.h" 
#include "manager.h"
#include "renderer.h"
#include "time.h"


CTime::CTime(OBJTYPE nPriority) : CScene(nPriority)
{

}

CTime::~CTime()
{

}

CTime *CTime::Create(D3DXVECTOR3 pos, float fsize)
{
	CTime *pTime = NULL;
	pTime = new CTime;
	pTime->Init(pos, fsize);
	return pTime;
}

HRESULT CTime::Init(D3DXVECTOR3 pos, float fsize)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apScene2D[nCntTime] = CScene2D::Create(D3DXVECTOR3(pos.x + nCntTime * 80, pos.y, pos.z), fsize,CTexture::TIME);
		m_apScene2D[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_nTime = 60;
	return S_OK;
}

HRESULT CTime::Init(void)
{
	return 0;
}

void CTime::Uninit()
{
	Release();
}

void CTime::Update()
{
	m_nAddTime++;//フレームを回す
	//60フレーム回ったら1秒減らす
	if (m_nAddTime >= 60)
	{
		m_nAddTime = 0;
		m_nTime -= 1;
	}

	//20秒以下になったら赤色にする
	if (m_nTime <= 20)
	{
		for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
		{
			m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	//念のため0秒より低くならないように
	if (m_nTime <= 0)
	{
		m_nTime = 0;
	}
	SetTime();//描画の設定
}

void CTime::Draw()
{
	for (int nCntTime =0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apScene2D[nCntTime]->Draw();
	}
}

//描画の設定
void CTime::SetTime()
{
	int aTime[MAX_TIME];
	aTime[0] = m_nTime % 1000 / 100;
	aTime[1] = m_nTime % 100 / 10;
	aTime[2] = m_nTime % 10 / 1;

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apScene2D[nCntTime]->SetTex(0, aTime[nCntTime], 0.1);
	}
}