//=============================================================================
//
// ����݂����ȃG�t�F�N�g�̏��� [water_circle_effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"water_crest_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"
#include"input.h"

//=============================================================================
// ����݂����ȃG�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CWater_Crest_Effect::CWater_Crest_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	m_col = D3DXCOLOR(255, 255, 255, 255);
	m_nLife = 30;
	m_bUse = false;
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CWater_Crest_Effect::~CWater_Crest_Effect()
{

}


//=============================================================================
// ����݂����ȃG�t�F�N�g�̐���
//=============================================================================
CWater_Crest_Effect *CWater_Crest_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col,
	CTexture::Tex type, D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	//�C���X�^���X����
	CWater_Crest_Effect *pWater_Crest_Effect = new CWater_Crest_Effect(CScene::PRIORITY_NOMAL);

	if (pWater_Crest_Effect != NULL)
	{
		pWater_Crest_Effect->Init(pos, move, size, col, type, addmove, addsize, addcol, nRadius, nDensity, nLife);
	}

	return pWater_Crest_Effect;
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̏���������
//=============================================================================
HRESULT CWater_Crest_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	 D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	CBilleffect::Init(pos,size);
	SetWater_Crest(pos, move, size, col, type, addmove, addsize, addcol, nRadius, nDensity, nLife);

	return S_OK;
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̏I������
//=============================================================================
void CWater_Crest_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̍X�V����
//=============================================================================
void CWater_Crest_Effect::Update(void)
{
	//int nRadius = 25;
	//
	//D3DXVECTOR3 rot;
	//
	//rot.y = -0.75f;

	//if (m_bUse == false)
	//{
	//	if (CManager::GetInputKeyboard()->GetTrigger(DIK_0) == true)
	//	{
	//		for (int nCnt = 0; nCnt < 50; nCnt++)
	//		{				
	//			//float fAngle = CIRCLE_HALF;
	//			//float fAngle = CIRCLE;
	//			//float rotX = cosf(fAngle) * rot.y;
	//			//float rotY = sinf(fAngle) * rot.y;
	//			//CEffect::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3((cosf(fAngle)*nRadius)*m_move.x, m_move.y, (sinf(fAngle)*nRadius) * m_move.z), m_size, m_col, CTexture::Effect, m_nLife);
	//			//CEffect::Create(D3DXVECTOR3((rotX*nRadius), m_pos.y, (rotY*nRadius)), D3DXVECTOR3(rotX*m_move.x,m_move.y, rotY * m_move.z), m_size, m_col, CTexture::Effect, m_nLife);
	//			//CEffect::Create(D3DXVECTOR3((cosf(fAngle)*nRadius), m_pos.y, (sinf(fAngle)*nRadius)), D3DXVECTOR3(cosf(fAngle)*m_move.x, m_move.y, sinf(fAngle) * m_move.z), m_size, m_col, CTexture::Effect, m_nLife);
	//			//CEffect::Create(D3DXVECTOR3((cosf(fAngle)*nRadius), m_pos.y, (sinf(fAngle)*nRadius)), D3DXVECTOR3((cosf(fAngle)*nRadius), m_move.y, (sinf(fAngle)*nRadius)), m_size, m_col, CTexture::Effect, m_nLife);
	//		}
	//	}
	//}


	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̕`�揈��
//=============================================================================
void CWater_Crest_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̐ݒ菈��
//=============================================================================
void CWater_Crest_Effect::SetWater_Crest(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	for (int nCnt = 0; nCnt < nDensity; nCnt++)
	{
		float fAngle = CIRCLE;
		m_pEffect = CEffect::Create(D3DXVECTOR3(pos.x, pos.y - move.y, pos.z), D3DXVECTOR3(move.x + (cosf(fAngle)*nRadius), move.y, move.z + (sinf(fAngle)*nRadius)),
			size, col, type, addmove, addsize,addcol, nLife);
		//CEffect::Create(D3DXVECTOR3(pos.x + (cosf(fAngle)*nRadius), pos.y, pos.z + (sinf(fAngle)*nRadius)), D3DXVECTOR3((cosf(fAngle)*nRadius), move.y, (sinf(fAngle)*nRadius)), size, col, CTexture::Effect, nLife);
		//CEffect::Create(D3DXVECTOR3(pos.x * (cosf(fAngle)*nRadius), pos.y, pos.z * (sinf(fAngle)*nRadius)), D3DXVECTOR3(cosf(fAngle)*move.x, move.y, sinf(fAngle) * move.z), size, col, CTexture::Effect, nLife);
		move = Addmove(move, D3DXVECTOR3(0,0.1f,0));
		//col = Addcol(col, addcol);
	}
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CWater_Crest_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	if (move.x < 0)
	{
		move.x = 0;
	}
	if (move.y < 0)
	{		 
		move.y = 0;
	}
	if (move.z < 0)
	{		 
		move.z = 0;
	}

	return move;
}

//=============================================================================
// ����݂����ȃG�t�F�N�g�̐F�̌��Z����
//=============================================================================
D3DXCOLOR CWater_Crest_Effect::Addcol(D3DXCOLOR col, D3DXCOLOR addcol)
{
	col -= addcol;

	return col;
}