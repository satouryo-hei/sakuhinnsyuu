//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"homing.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"effect.h"

/*��肽������*/
/*�e�̉�]�@������̂��H
�`���[�W�V���b�g
�`���[�W�V���b�g�Œe�̊g��*/

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CHoming::m_pTexture = NULL;

//=============================================================================
// �e�̃R���X�g���N�^
//=============================================================================
CHoming::CHoming(int nPriority) : CScene2D(PRIORITY_H_BULLET)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_bUse = false;
	memset(&m_Homing, 0, sizeof(m_Homing));
	m_nPriority = nPriority;

	m_nLife = 0;
}


//=============================================================================
// �e�̃f�X�g���N�^
//=============================================================================
CHoming::~CHoming()
{

}


//=============================================================================
// �e�̐�������
//=============================================================================
CHoming *CHoming::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, D3DXVECTOR2 lastPoint, int nAttack)
{
	CHoming* pHoming = NULL;

	pHoming = new CHoming;

	if (pHoming != NULL)
	{
		pHoming->Init(pos, Size);
		pHoming->m_Move = move;
		pHoming->Bindtexture(6);
		pHoming->m_bUse = false;
		pHoming->m_Homing.dPoint3[0] = (int)lastPoint.x;
		pHoming->m_Homing.dPoint3[1] = (int)lastPoint.y;
	}

	return pHoming;
}

//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CHoming::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);

	m_nLife = 30;
	int nItem = CPlayer::GetItem();
	m_nLife += nItem;
	m_Pos = pos;
	m_Size = Size;	

	m_Homing.nCounter = 0;		
	m_Homing.nDivNum = 50;
	m_Homing.dPoint0[0] = m_Pos.x;
	m_Homing.dPoint0[1] = m_Pos.y;
	m_Homing.dPoint1[0] = rand() % 1280;
	m_Homing.dPoint1[1] = 640;
	m_Homing.dPoint2[0] = rand() % 640;
	m_Homing.dPoint2[1] = 120;
	
	return S_OK;
}	// �|���S���̏����������I��



	//=============================================================================
	// �e�̏I������
	//=============================================================================
void CHoming::Uninit(void)
{
	//CScene2D::Uninit();

	Release();

}// �|���S���̏I�������I��


 //=============================================================================
 // �e�̍X�V����
 //=============================================================================
void CHoming::Update(void)
{

	if (m_bUse)
	{
		Uninit();
		return;
	}
	// ��ʊO����
	if (m_Pos.x >= SCREEN_WIDTH - (m_Size.x / 2))
	{
		m_bUse = true;
	}
	else if (m_Pos.x <= (m_Size.x / 2))
	{
		m_bUse = true;
	}
	if (m_Pos.y >= SCREEN_HEIGHT - (m_Size.y / 2))
	{
		m_bUse = true;
	}
	else if (m_Pos.y <= (m_Size.y / 2))
	{
		m_bUse = true;
	}

	m_Pos = SetCurve();

	m_Homing.nCounter++;

	// �����J�E���^�[���������ɒB���Ă�����O�ɖ߂�
	if (m_Homing.nCounter == m_Homing.nDivNum)
	{
		m_Homing.nCounter = 0;
		m_bUse = true;
	}
	SetPosition(m_Pos);
	if (m_Homing.nCounter >= 2)
	{
		CEffect::Create(m_Pos, m_Size, D3DXVECTOR2(0.1f, 0.1f), D3DXCOLOR(10, 15, 40, 10),1);
	}


	CScene2D::Update();

}// �|���S���̍X�V�����I��



 //=============================================================================
 // �e�̕`�揈��
 //=============================================================================
void CHoming::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��


//=============================================================================
// �e�̃x�W�F�Ȑ��̌v�Z����
//=============================================================================
D3DXVECTOR3 CHoming::SetCurve(void)
{
	/*�n�_����ꂭ���ƂŏI�_��Ԃ��ă|�X�ɑ��������
 */
	double dNum = 0;

	// �x�W�F�Ȑ��p�̕ϐ�5��
	double dPoint[2] = {};
	D3DXVECTOR2 Point0, Point1, Point2;

	// ���_�p�̕ϐ���3��
	double dPoint02[2], dPoint03[2], dPoint04[2];	

	// (1/������)/�J�E���g��
	dNum = (1.0 / m_Homing.nDivNum) * m_Homing.nCounter;

	// �p�΂��Ă�Ƃ��낪2���邩��
	// �p�΂��Ă�Ƃ��낪���邩��_��2�_�ł�

	// 2�����̃x�W�F�Ȑ�(����_��1��)
	// dPoint10(�p�΂��Ă���Ƃ���̈ꂩ���ڂ̓_�̂P��(x���W)) = (1-������) * �n�_(x���W) + ������ * ���_(x���W)
	dPoint[0] = (1.0 - dNum) * m_Homing.dPoint0[0] + dNum * m_Homing.dPoint1[0];
	// dPoint11(�p�΂��Ă���Ƃ���̈ꂩ���ڂ̓_��2��(y���W)) = (1-������) * �n�_(y���W) + ������ * ���_(y���W)
	dPoint[1] = (1.0 - dNum) * m_Homing.dPoint0[1] + dNum * m_Homing.dPoint1[1];

	Point0 = D3DXVECTOR2(dPoint[0], dPoint[1]);

	// dPoint12(�p�΂��Ă���Ƃ���̓񂩏��ڂ̓_��1��(x���W)) = (1-������) * ���_(x���W) + ������ * �I�_(x���W)or���ԓ_�i3�����j
	dPoint[0] = (1.0 - dNum) * m_Homing.dPoint1[0] + dNum * m_Homing.dPoint2[0];
	// dPoint13(�p�΂��Ă���Ƃ���̓񂩏��ڂ̓_��2��(y���W)) = (1-������) * ���_(y���W) + ������ * �I�_(y���W)or���ԓ_�i3�����j
	dPoint[1] = (1.0 - dNum) * m_Homing.dPoint1[1] + dNum * m_Homing.dPoint2[1];

	Point1 = D3DXVECTOR2(dPoint[0], dPoint[1]);

	// 3�����̃x�W�F�Ȑ�(����_��2��)
	// dPoint14(�p�΂��Ă���Ƃ���̓񂩏��ڂ̓_��1��(x���W)) = (1-������) * �n�_(x���W) + ������ * �I�_(y���W)
	dPoint[0] = (1.0 - dNum) * m_Homing.dPoint2[0] + dNum * m_Homing.dPoint3[0];

	// dPoint15(�p�΂��Ă���Ƃ���̓񂩏��ڂ̓_��2��(z���W)) = (1-������) * �n�_(y���W) + ������ * �I�_(y���W)
	dPoint[1] = (1.0 - dNum) * m_Homing.dPoint2[1] + dNum * m_Homing.dPoint3[1];

	Point2 = D3DXVECTOR2(dPoint[0], dPoint[1]);

	// dPoint02(2�_����������̐^��)�@= (1- ������) * dPoint10 + ������ ��dPoint12
	dPoint02[0] = (1.0 - dNum) * Point0.x + dNum * Point1.x;
	// dPoint02(2�_����������̐^��)�@= (1- ������) * dPoint11 + ������ ��dPoint13
	dPoint02[1] = (1.0 - dNum) * Point0.y + dNum* Point1.y;

	// dPoint03(2�_����������̐^��)�@= (1- ������) * dPoint10 + ������ ��dPoint12
	dPoint03[0] = (1.0 - dNum) * Point1.x + dNum * Point2.x;
	// dPoint03(2�_����������̐^��)�@= (1- ������) * dPoint10 + ������ ��dPoint12
	dPoint03[1] = (1.0 - dNum) * Point1.y + dNum * Point2.y;

	// dPoint04(2�_����������̐^��)�@= (1- ������) * dPoint02 + ������ ��dPoint03
	dPoint04[0] = (1.0 - dNum) * dPoint02[0] + dNum * dPoint03[0];
	// dPoint04(2�_����������̐^��)�@= (1- ������) * dPoint02 + ������ ��dPoint03
	dPoint04[1] = (1.0 - dNum) * dPoint02[1] + dNum* dPoint03[1];

	return D3DXVECTOR3(dPoint04[0], dPoint04[1],0);
}