//----------------------------------
//�|���S���̏���
//-----------------------------------
#include "texture.h"
#include "shadow.h"
#include "manager.h"
#include "Renderer.h"
#include "collision.h"
#include "stage.h"
#include "game.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow(OBJTYPE nPriority) :CScene3D(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{

}
void CShadow::BindTexture(CTexture::Type type)
{
	m_pTexture = CManager::GetTexture()->GetTexture(type);
}
//---------------------------------------------------------------
//�C���X�^���X��������
//---------------------------------------------------------------
CShadow *CShadow::Create(D3DXVECTOR3 pos, float fSize, CTexture::Type texture)
{
	//�C���X�^���X����
	CShadow *pShadow = new CShadow(OBJTYPE_EFFECT);

	if (pShadow != NULL)
	{
		pShadow->BindTexture(texture);
		pShadow->Init();
		pShadow->m_pos.y = 0.0f;
		pShadow->SetPos(pos.x, pos.z, D3DXVECTOR3(fSize, 0.0f, fSize));
	}

	return pShadow;

}

HRESULT CShadow::Init(void)
{
	m_fGravitySpeed = SHADOWGRAVITY;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	// ���_����ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, 0.0f, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, 0.0f, -m_size.z);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CShadow::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================

void CShadow::Update(void)
{
	if (m_fGravitySpeed > 0.0f)
	{
		m_fGravity -= m_fGravitySpeed;
		m_pos.y += m_fGravity;

	}
	if (m_pos.y <= -100.0f)
	{
		m_pos.y = -100.0f;
	}
	m_LastPos = m_pos;
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
																	 //���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//m_mtxWorld._11 = m_size.x;
	//m_mtxWorld._33 = m_size.z;
	////���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	////�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���Ńo�X�̂Ł[�����Ƃ�[�ނɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//�ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//------------------------------------------------------------
//���_���W�̐ݒ�
//------------------------------------------------------------

void CShadow::SetPos(const float fposX, const float fposZ, D3DXVECTOR3 scale)
{
	CScene::SetScale(scale);

	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(fposX - scale.x, m_pos.y, fposZ + scale.z);
	pVtx[1].pos = D3DXVECTOR3(fposX + scale.x, m_pos.y, fposZ + scale.z);
	pVtx[2].pos = D3DXVECTOR3(fposX - scale.x, m_pos.y, fposZ - scale.z);
	pVtx[3].pos = D3DXVECTOR3(fposX + scale.x, m_pos.y, fposZ - scale.z);

	m_pVtxBuff->Unlock();

}

void CShadow::SetCol(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	m_pVtxBuff->Unlock();

}
