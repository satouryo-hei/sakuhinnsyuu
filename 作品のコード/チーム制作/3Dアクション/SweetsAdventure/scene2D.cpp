//----------------------------------
//�|���S���̏���
//-----------------------------------
#include "scene2D.h"
#include "input.h"
#include "Renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(OBJTYPE nPriority) :CScene(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}
//---------------------------------------------------------------
//�C���X�^���X��������
//---------------------------------------------------------------
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float fSize, CTexture::Type texture)
{
	//�C���X�^���X����
	CScene2D *pScene2D = new CScene2D(OBJTYPE_NONE);
	if (pScene2D != NULL)
	{
		pScene2D->Init();
		pScene2D->BindTexture(texture);
		pScene2D->SetPos(pos, D3DXVECTOR3(fSize, fSize, 0.0f));
	}
	return pScene2D;
}

void CScene2D::BindTexture(CTexture::Type type)
{
	m_pTexture = CManager::GetTexture()->GetTexture(type);
}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene2D::Init(CTexture::Type type)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

																	 // ���_����ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	m_bUse = true;

	//�e�N�X�`���摜�̐ݒ�
	m_pTexture = CManager::GetTexture()->GetTexture(type);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}
HRESULT CScene2D::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

																	 // ���_����ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CScene2D::Uninit(void)
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
void CScene2D::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

																	 // ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,						//�`����J�n����ŏ��̒��_�C���f�b�N�X
		2);						//�|���S���̐�

}
//-------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//���_���W�̐ݒ�
//------------------------------------------------------------
void CScene2D::SetPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = vtx0;
	pVtx[1].pos = vtx1;
	pVtx[2].pos = vtx2;
	pVtx[3].pos = vtx3;

	m_pVtxBuff->Unlock();

}
//--------------------------------------------------------------------
//�ǉ����܂��� �X�P�[����pos�{���������₷����
//--------------------------------------------------------------------
void CScene2D::SetScalePos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	CScene::SetPos(pos);
	CScene::SetScale(scale);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y - scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + scale.x, pos.y - scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + scale.x, pos.y + scale.y, 0.0f);

	m_pVtxBuff->Unlock();

}


//------------------------------------------------------------
//���_���W�̐ݒ�
//------------------------------------------------------------

void CScene2D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	CScene::SetPos(pos);
	CScene::SetScale(scale);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(pos.x - scale.x, pos.y - scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + scale.x, pos.y - scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - scale.x, pos.y + scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + scale.x, pos.y + scale.y, 0.0f);

	m_pVtxBuff->Unlock();

}


//------------------------------------------------------------
//�e�N�X�`���̐ݒ�
//------------------------------------------------------------
void CScene2D::SetTex(int nAnim, int nPartU)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f / nPartU)*nAnim, 0.0);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nPartU)*(nAnim + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (1.0f / nPartU)*nAnim, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nPartU)*(nAnim + 1), 1.0f);

	m_pVtxBuff->Unlock();

}
//------------------------------------------------------------
//�e�N�X�`���̐ݒ�
//------------------------------------------------------------
void CScene2D::SetTex(int nType, int nPattern, float fSize)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern * fSize, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPattern * fSize + fSize, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattern * fSize, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPattern * fSize + fSize, 1.0f);

	m_pVtxBuff->Unlock();

}
void CScene2D::SetTex(float fSpeedX, float fSpeedY)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + fSpeedX, 0.0f + fSpeedY);
	pVtx[1].tex = D3DXVECTOR2(1.0f + fSpeedX, 0.0f + fSpeedY);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fSpeedX, 1.0f + fSpeedY);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fSpeedX, 1.0f + fSpeedY);

	m_pVtxBuff->Unlock();
}

void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	m_pVtxBuff->Unlock();

}
