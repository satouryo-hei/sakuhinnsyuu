//=============================================================================
//
// �G�t�F�N�g�̏��� [effect_sa.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "input.h"
#include "effect_sa.h"
#include "camera.h"
#include"scene.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"

// //�ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 m_pTexture = NULL;//�e�N�X�`���ւ̃|�C���^


//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CEffect_sa::CEffect_sa(OBJTYPE nPriority) : CBilleffect(nPriority)
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
// �G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CEffect_sa::~CEffect_sa()
{

}


//=============================================================================
// �G�t�F�N�g�̐�������
//=============================================================================
CEffect_sa *CEffect_sa::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife)
{
	//�C���X�^���X����
	CEffect_sa *pEffect_sa = new CEffect_sa(CScene::OBJTYPE_EFFECT);

	if (pEffect_sa != NULL)
	{		
		pEffect_sa->Init(pos, move, size, col, type, nLife);
	}

	return pEffect_sa;
}

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CEffect_sa::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife)
{
	CBilleffect::Init(type);
	m_pos = pos;
	m_move = move;
	m_size = size;
	m_col = col;
	m_nLife = nLife;
	m_bUse = false;

	return S_OK;
}


//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CEffect_sa::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CEffect_sa::Update(void)
{	
	m_pos += m_move;

	CBilleffect::Setposition(m_pos, m_size);//���_���̐ݒ�
	CBilleffect::SetColor(m_col);
	CBilleffect::Update();

	m_nLife -= 1;
	if (m_nLife <= 0)
	{
		m_nLife = 0;
		//�G�t�F�N�g������
		m_col.a -= 0.08f;
		if (m_col.a <= 0.0f)
		{
			m_bUse = true;
		}
	}

	if (m_bUse == true)
	{
		m_bUse = false;
		Uninit();
	}
}
		

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CEffect_sa::Draw(void)
{
	CBilleffect::Draw();
}

//void SaveEffect(void)
//{
//	FILE *pFile = fopen(SAVEFILENAME, "w");
//
//	if (pFile != NULL)
//	{
//		fprintf(pFile, "#========================================================================\n");
//		fprintf(pFile, "#�Z�b�g�����G�t�F�N�g�̃X�e�[�^�X�����̃e�L�X�g�t�@�C���ɏ����o���܂�\n");
//		fprintf(pFile, "#�ǂݍ��ރe�L�X�g�t�@�C���ɃR�s�y����Ȃ肵�ĉ�����\n");
//		fprintf(pFile, "#========================================================================\n\n\n");
//
//		fprintf(pFile, "EFFECTTYPE\n");
//		fprintf(pFile, "	EFFECTSTATE\n");
//		fprintf(pFile, "		DENSITY = %d\n", g_Effectstate.nDensity);
//		fprintf(pFile, "		TYPE = %d\n", g_Effectstate.SerectType);
//		fprintf(pFile, "		COLOR = %d %d %d %d\n", g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA);
//		fprintf(pFile, "		COLORMIN = %d %d %d %d\n", g_Effectstate.MinColorR, g_Effectstate.MinColorG, g_Effectstate.MinColorB, g_Effectstate.MinColorA);
//		fprintf(pFile, "		LIFE = %d\n", g_Effectstate.nLifeSerect);
//		fprintf(pFile, "		SIZE = %.1f %.1f\n", g_Effectstate.fWhidth, g_Effectstate.fHight);
//		fprintf(pFile, "		SIZEMIN = %.1f %.1f\n", g_Effectstate.fMinWhidth, g_Effectstate.fMinHight);
//
//		if (g_Effectstate.SerectType == EFFECTTYPE_CIRCLE)
//		{
//			fprintf(pFile, "		RADIUS = %d\n", g_Effectstate.nRadius);
//		}
//
//		fprintf(pFile, "	EFFECTSTATE_END\n");
//		fprintf(pFile, "EFFECTTYPE_END\n");
//
//	}
//	fclose(pFile);
//}