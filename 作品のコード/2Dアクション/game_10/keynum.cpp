//=============================================================================
//
// ����UI�̏��� [keyui.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"keynum.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"
#include"number.h"
#include"player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKeynum::CKeynum(PRIORITY Priority) :CScene2D(PRIORITY_UI)
{
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_Pos = D3DXVECTOR3(100.0f, 50.0f, 0);	
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKeynum::~CKeynum()
{

}

//=============================================================================
// ����UI�̐�������
//=============================================================================
CKeynum *CKeynum::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2D�G�t�F�N�g�̃|�C���^�[����
	CKeynum* pKeyui = NULL;

	// ���I�������̊m��
	pKeyui = new CKeynum;

	// NULL�`�F�b�N
	if (pKeyui != NULL)
	{		
		// ����UI�̏���������
		pKeyui->Init(pos,size);
	}
	return pKeyui;
}

//=============================================================================
// ����UI�̏���������
//=============================================================================
HRESULT CKeynum::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_Pos = pos;

	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++)
	{
		m_Pos.x += (size.x * 2);
		m_apNumber[nCnt] = CNumber::Create(m_Pos, size, 5);
	}

	return S_OK;
}	//  ���S�̏����������̏I��



	//=============================================================================
	// ����UI�̏I������
	//=============================================================================
void CKeynum::Uninit(void)
{
	// �V�[���̉������
	CScene::Release();

}// ���S�̏I�������̏I��


 //=============================================================================
 // ����UI�̍X�V����
 //=============================================================================
void CKeynum::Update(void)
{
	int nItem = CPlayer::GetItem();
	SetNumKey(nItem);
}// ����UI�̍X�V�����I��



 //=============================================================================
 // ����UI�̕`�揈��
 //=============================================================================
void CKeynum::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEYNUMBER; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}	// ����UI�̕`�揈���I��


	//=============================================================================
	// ����UI�̐ݒ菈��
	//=============================================================================
void CKeynum::SetNumKey(const int nNumKey)
{
	static const int nData = 10;

	int nNum = MAX_KEYNUMBER;
	int iNum = MAX_KEYNUMBER - 1;

	// NUMSCORE����
	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++, nNum--, iNum--)
	{
		m_apNumber[nCnt]->SetNumber(nNumKey % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
}