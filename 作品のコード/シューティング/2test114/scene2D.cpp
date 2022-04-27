//=============================================================================
//
// �|���S���̏��� [scene2D.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"scene2D.h"
#include"renderer.h"
#include"manager.h"


//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexTure = NULL;
	m_pVlxBuff = NULL;			
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_fRoll = 0;
	m_fHypot = 0;
	m_fAngle = 0;
	m_bAdd = true;
}


//=============================================================================
//�@�|���S���̃f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}


//=============================================================================
// �|���S���̃f�t�H���g����������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;
	
	//�f�o�C�X�̎擾
	pDevice = pManager->GetRenderer()->GetDevice();

	m_pos = pos;	
	m_Size = Size;

	m_fAngle = atan2f(1.0f, 1.0f);											//�p�x�����߂邽�߂ɂP�񂵂��g��Ȃ��i���W�A��//m_fAngle�Ɋp�x����m_fAngle�͊p�x
	m_fHypot = sqrtf(powf(m_Size.x, 2.0f) + powf(m_Size.y, 2.0f));					//�Εӂ����߂�

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVlxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

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
	m_pVlxBuff->Unlock();

	return S_OK;
}	// �|���S���̏����������I��


//=============================================================================
// �|���S���̓����n�̏���������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos,Size);
	m_Move = move;
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CScene2D::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVlxBuff != NULL)
	{
		m_pVlxBuff->Release();
		m_pVlxBuff = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Relese();

}// �|���S���̏I�������I��


//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::Update(void)
{		
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x*cosf(m_fAngle - m_fRoll), m_pos.y - m_Size.y*sinf(m_fAngle - m_fRoll), 0.0f);//�������a��cosf(�p�x)���p�x=g_fAngle
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x*cosf(m_fAngle + m_fRoll), m_pos.y - m_Size.y*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x*cosf(m_fAngle + m_fRoll), m_pos.y + m_Size.y*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x*cosf(m_fAngle - m_fRoll), m_pos.y + m_Size.y*sinf(m_fAngle - m_fRoll), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();

}// �|���S���̍X�V�����I��



//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;
	
	pDevice = pManager->GetRenderer()->GetDevice();

	pDevice->SetStreamSource(0, m_pVlxBuff, 0, sizeof(VERTEX_2D));//
																  // ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, m_pTexTure[m_Typ]);
	pDevice->SetTexture(0, m_pTexTure);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// �|���S���̕`�揈���I��

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CScene2D::SetUpdatePos(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);//�������a-�ΕӁ�cosf(�p�x)���p�x=g_fAngle
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}

//=============================================================================
// �����|���S���̍X�V����
//=============================================================================
void CScene2D::SetUpdateMovePos(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - Size.x+move.x, pos.y - Size.y+move.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Size.x+move.x, pos.y - Size.y+move.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - Size.x+move.x, pos.y + Size.y+move.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Size.x+move.x, pos.y + Size.y+move.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}


//=============================================================================
// �|���S���̉�]�̍X�V����
//=============================================================================
void CScene2D::SetUpdateRoll(void)
{
	m_fRoll += 0.01f;

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
// �|���S���̊g��k���̍X�V����
//=============================================================================
void CScene2D::SetUpdateScale(int nMAXSize, int nMINSize)
{
	if (m_bAdd == true)
	{
		m_fHypot++;
	}
	else
	{
		m_fHypot--;
	}

	if (m_fHypot > nMAXSize)
	{
		m_bAdd = false;

	}
	if (m_fHypot < nMINSize)
	{
		m_bAdd = true;
	}
}

//=============================================================================
// �A�j���[�V�����̃e�N�X�`���z�u����
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnim)
{	
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W (��8�p�^�[��)
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim + fSizeAnim, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim, 0.0f + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim + fSizeAnim, 0.0f + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}

//=============================================================================
// �A�j���[�V�����̃e�N�X�`���z�u����
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W (��8�p�^�[��)
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}

//=============================================================================
// �����e�N�X�`���̔z�u����
//=============================================================================
void CScene2D::SetTex(float fPosTexU, float fPosTexV)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W (��8�p�^�[��)
	pVtx[0].tex = D3DXVECTOR2(fPosTexU, fPosTexV);
	pVtx[1].tex = D3DXVECTOR2(fPosTexU + 1.0f, fPosTexV);
	pVtx[2].tex = D3DXVECTOR2(fPosTexU, fPosTexV+1.0f);
	pVtx[3].tex = D3DXVECTOR2(fPosTexU + 1.0f, fPosTexV+1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���̐F�̐ݒ菈��
//=============================================================================
void CScene2D::SetColor(int nRad, int nGreen, int nBlue, int nAlpha)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���̐F�̐ݒ菈��
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}