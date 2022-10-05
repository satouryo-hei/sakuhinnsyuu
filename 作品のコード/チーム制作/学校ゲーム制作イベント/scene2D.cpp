//=============================================================================
//
// 2D�I�u�W�F�N�g�̏��� [scene2D.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"scene2D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
const int CScene2D::m_nNumVertex = 4;

//=============================================================================
// 2D�I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(PRIORITY Priority) : CScene(Priority)
{
	m_pTexTure = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_fRoll = 0;
	m_fHypot = 0;
	m_fAngle = 0;
	m_bSizeAdd = true;
}

//=============================================================================
// 2D�I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 2D�I�u�W�F�N�g�̐�������
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nTex)
{
	// �|���S���̃|�C���^�[����
	CScene2D* pScene2D = NULL;

	// ���I�������̊m��
	pScene2D = new CScene2D;

	// NULL�`�F�b�N
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, size);
		pScene2D->Bindtexture(nTex);
	}
	return pScene2D;
}

//=============================================================================
//�@2D�I�u�W�F�N�g�̃e�N�X�`���̐ݒ�
//=============================================================================
void CScene2D::Bindtexture(int nTex)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTex);
}

//=============================================================================
// 2D�I�u�W�F�N�g�̃f�t�H���g����������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 2D�I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Size = Size;
	// 2D�I�u�W�F�N�g�̃f�t�H���g�����������̌Ăяo��
	Init(pos);

	//�p�x�����߂邽�߂ɂP�񂵂��g��Ȃ��i���W�A��//m_fAngle�Ɋp�x����m_fAngle�͊p�x(45�x)
	m_fAngle = atan2f(1, 1);														// -1.0f�`1.0f�͈̔͂����W�A�����l(-3.14�`-3.14)�ɂȂ�
																					// �|���S�����̎Εӂ����߂�
	m_fHypot = sqrtf(powf(m_Size.x, 2.0f) + powf(m_Size.y, 2.0f));

	return S_OK;
}	// �|���S���̏����������I��

//=============================================================================
// 2D�I�u�W�F�N�g�̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();

}// �|���S���̏I�������I��S

 //=============================================================================
 // 2D�I�u�W�F�N�g�̍X�V����
 //=============================================================================
void CScene2D::Update(void)
{
	CScene2D::SetPosSize(m_pos, m_Size);

}// �|���S���̍X�V�����I��S

 //=============================================================================
 // 2D�I�u�W�F�N�g�̕`�揈��
 //=============================================================================
void CScene2D::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexTure);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// �|���S���̕`�揈���I��

//=============================================================================
// 2D�I�u�W�F�N�g�̈ʒu�Ƒ傫���̐ݒ菈��
//=============================================================================
void CScene2D::SetPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - Size.x, pos.y - Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Size.x, pos.y - Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - Size.x, pos.y + Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2D�I�u�W�F�N�g�̈ʒu�Ƒ傫���̒��_���Ƃ̐ݒ菈��
//=============================================================================
void CScene2D::SetVtxBuffPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	switch (nNum)
	{
	case 0:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x - m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);
		break;

	case 1:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x + Size.x, pos.y - Size.y, 0.0f);
		break;

	case 2:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x - Size.x, pos.y + Size.y, 0.0f);
		break;

	case 3:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);
		break;

	default:
		break;
	}
	//���_���W�̐ݒ�

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
// 2D�I�u�W�F�N�g��]�g�k�̍X�V�̐ݒ菈��
//=============================================================================
void CScene2D::SetUpdateRollingSize(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);//�������a��cosf(�p�x)�p�x=g_fAngle
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
// 2D�I�u�W�F�N�g��1��]�̍X�V����
//=============================================================================
void CScene2D::SetUpdateRoll(float fSpeed, bool bAdd)
{
	if (bAdd)
	{
		m_fRoll += fSpeed;
	}
	else
	{
		m_fRoll -= fSpeed;
	}

	if (m_fRoll > D3DX_PI)
	{
		m_fRoll = -D3DX_PI;
	}
	else if (m_fRoll < -D3DX_PI)
	{	
		m_fRoll = D3DX_PI;
	}
}

//=============================================================================
// 2D�I�u�W�F�N�g�̉�]�̐ݒ�X�V����
//=============================================================================
void CScene2D::SetRolling(float fSpeed, float fMin, float fMax)
{
	if (m_bRollAdd)
	{
		m_fRoll += fSpeed;
	}
	else
	{
		m_fRoll -= fSpeed;
	}

	if (m_fRoll > fMax)
	{
		m_bRollAdd = false;
	}
	else if (m_fRoll < fMin)
	{
		m_bRollAdd = true;
	}
}

//=============================================================================
// 2D�I�u�W�F�N�g�̊g��k���̍X�V����
//=============================================================================
void CScene2D::SetUpdateSize(int MaxSize, int MinSize)
{
	if (m_bSizeAdd)
	{
		m_fHypot++;
	}
	else
	{
		m_fHypot--;
	}

	if (m_fHypot > MaxSize)
	{
		m_bSizeAdd = false;

	}
	else if (m_fHypot < MinSize)
	{
		m_bSizeAdd = true;
	}
}

//=============================================================================
// 2D�I�u�W�F�N�g�̐F�̐ݒ菈��
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2D�I�u�W�F�N�g�̐F�̐ݒ菈��
//=============================================================================
void CScene2D::SetRgba(int nRed, int nGreen, int nBlue, int nAlpha)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2D�I�u�W�F�N�g�̒��_�̐F�̐ݒ菈��
//=============================================================================
void CScene2D::SetVtxBuffColor(D3DXCOLOR col, int nVtxBuff)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_�J���[
	pVtx[nVtxBuff].col = D3DXCOLOR(col);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̒��S����΂ߋ����̐ݒ菈��
//=============================================================================
void CScene2D::SetAngle(D3DXVECTOR2 Angle, D3DXVECTOR2 size)
{
	//�p�x�����߂邽�߂ɂP�񂵂��g��Ȃ��i���W�A��//m_fAngle�Ɋp�x����m_fAngle�͊p�x(45�x)
	m_fAngle = atan2f(Angle.y, Angle.x);														// -1.0f�`1.0f�͈̔͂����W�A�����l(-3.14�`-3.14)�ɂȂ�
																								// �|���S�����̎Εӂ����߂�
	m_fHypot = sqrtf(powf(size.x, 2.0f) + powf(size.y, 2.0f));
}

//=============================================================================
// �A�j���[�V�����̃e�N�X�`���z�u����
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}