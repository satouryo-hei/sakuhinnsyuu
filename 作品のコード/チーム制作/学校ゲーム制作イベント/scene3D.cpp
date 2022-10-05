//=============================================================================
//
// 3D�I�u�W�F�N�g�̏��� [scene3D.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"scene3D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// 3D�I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CScene(Priority)
{
	m_pTexTure = NULL;
	m_pVtxBuff = NULL;
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
}


//=============================================================================
//�@3D�I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

#if 0
//=============================================================================
// 3D�I�u�W�F�N�g�̐�������
//=============================================================================
CScene3D *CScene3D::Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size, , D3DXVECTOR3 rot)
{
	CScene3D* pScene3D;

	pScene3D = new CScene3D;

	if (pScene3D != NULL)
	{
		pScene3D->Init(pos, size,rot);
		pScene3D->BindTextuer(0);
	}
	return pScene3D;
}
#endif // 0

//=============================================================================
// 3D�I�u�W�F�N�g�̃e�N�X�`���̐ݒ�
//=============================================================================
void CScene3D::BindTextuer(int nTex)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTex);
}

//=============================================================================
// 3D�I�u�W�F�N�g�̃f�t�H���g����������
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}

//=============================================================================
// 3D�I�u�W�F�N�g�̏���������
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 Rot)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	Init(pos);
	m_Size = Size;
	m_rot = Rot;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3( - m_Size.x, + m_Size.y, + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3( + m_Size.x, + m_Size.y, + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3( - m_Size.x, 0.0f, - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3( + m_Size.x, 0.0f, - m_Size.z);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
}	// �|���S���̏����������I��



//=============================================================================
// 3D�I�u�W�F�N�g�̏I������
//=============================================================================
void CScene3D::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();

}// �|���S���̏I�������I��


 //=============================================================================
 // 3D�I�u�W�F�N�g�̍X�V����
 //=============================================================================
void CScene3D::Update(void)
{

}// �|���S���̍X�V�����I��


 //=============================================================================
 // 3D�I�u�W�F�N�g�̕`�揈��
 //=============================================================================
void CScene3D::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//�f�o�C�X���擾����
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�̃}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexTure);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// �|���S���̕`�揈���I��

//=============================================================================
// 3D�I�u�W�F�N�g�̖@���x�N�g����ݒ�֐�
//=============================================================================
void CScene3D::SetNorVector(D3DXVECTOR3 nor)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�@���x�N�g��
	pVtx[0].nor = nor;
	pVtx[1].nor = nor;
	pVtx[2].nor = nor;
	pVtx[3].nor = nor;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================================================
// �A�j���[�V�����̃e�N�X�`���z�u����
//=============================================================================
void CScene3D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

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