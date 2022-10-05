//=============================================================================
//
// ����UI�̏��� [keyui.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"bulletui.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"
#include"number.h"
#include"player.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPolygon *CBulletui::m_pPolygon = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletui::CBulletui(PRIORITY Priority) :CScene(PRIORITY_UI)
{
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_Pos = D3DXVECTOR3(100.0f, 50.0f, 0);
	m_Size = D3DXVECTOR2(100.0f, 50.0f);
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletui::~CBulletui()
{

}

//=============================================================================
// ����UI�̐�������
//=============================================================================
CBulletui *CBulletui::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2D�G�t�F�N�g�̃|�C���^�[����
	CBulletui* pBulletui = NULL;

	// ���I�������̊m��
	pBulletui = new CBulletui;

	// NULL�`�F�b�N
	if (pBulletui != NULL)
	{
		pBulletui->m_Size = size;

		// ����UI�̏���������
		pBulletui->Init(pos);
	}
	return pBulletui;
}

//=============================================================================
// ����UI�̏���������
//=============================================================================
HRESULT CBulletui::Init(D3DXVECTOR3 pos)
{
	m_Pos = pos;
	m_pPolygon = CPolygon::Create(pos, m_Size, 17);

	D3DXVECTOR3 Pos = pos;
	Pos.x += m_Size.x*2;

	D3DXVECTOR2 Size = D3DXVECTOR2(20.0f, 30.0f);

	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(Pos, Size, 5);
		Pos.x += (Size.x * 2);
	}

	return S_OK;
}	//  ���S�̏����������̏I��



	//=============================================================================
	// ����UI�̏I������
	//=============================================================================
void CBulletui::Uninit(void)
{
	// �V�[���̉������
	CScene::Release();

}// ���S�̏I�������̏I��


 //=============================================================================
 // ����UI�̍X�V����
 //=============================================================================
void CBulletui::Update(void)
{
	int nBullet = CPlayer::GetBulletNum();
	SetNumbullet(nBullet);
}// ����UI�̍X�V�����I��



 //=============================================================================
 // ����UI�̕`�揈��
 //=============================================================================
void CBulletui::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEYNUMBER; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}	// ����UI�̕`�揈���I��


	//=============================================================================
	// ����UI�̐ݒ菈��
	//=============================================================================
void CBulletui::SetNumbullet(const int nNumbullet)
{
	static const int nData = 10;

	int nNum = MAX_KEYNUMBER;
	int iNum = MAX_KEYNUMBER - 1;

	// NUMSCORE����
	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++, nNum--, iNum--)
	{
		m_apNumber[nCnt]->SetNumber(nNumbullet % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
}