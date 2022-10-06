//=============================================================================
//
// �I�u�W�F�N�g2D�̏��� [scene2D.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"scene2D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// �I�u�W�F�N�g2D�̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D()
{
	m_pTexTure = NULL;
	m_pVlxBuff = NULL;			
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
}


//=============================================================================
// �I�u�W�F�N�g2D�̃f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// �I�u�W�F�N�g2D�̃e�N�X�`���̐ݒ菈��
//=============================================================================
void CScene2D::BindTextuer(int nTex)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTex);
}

//=============================================================================
// �I�u�W�F�N�g2D�̃f�t�H���g����������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;
	
	//�f�o�C�X�̎擾
	pDevice = pManager->GetRenderer()->GetDevice();

	m_pos = pos;	
	m_Size = Size;

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
// �I�u�W�F�N�g2D�̓����n�̏���������
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size)
{
	CScene2D::Init(pos,Size);
	m_Move = move;
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g2D�̏I������
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
	Release();

}// �|���S���̏I�������I��

//=============================================================================
// �I�u�W�F�N�g2D�̍X�V����
//=============================================================================
void CScene2D::Update(void)
{		
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

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
	
	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetStreamSource(0, m_pVlxBuff, 0, sizeof(VERTEX_2D));//
																  // ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexTure);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// �|���S���̕`�揈���I��

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

//=============================================================================
// �A�j���[�V�����̃e�N�X�`���ݒ菈��
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W 
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���ݒ菈��
//=============================================================================
void CScene2D::SetTex(float fSizeMin, float fSizeMax)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(fSizeMin, fSizeMin);
	pVtx[1].tex = D3DXVECTOR2(fSizeMax, fSizeMin);
	pVtx[2].tex = D3DXVECTOR2(fSizeMin, fSizeMax);
	pVtx[3].tex = D3DXVECTOR2(fSizeMax, fSizeMax);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
}