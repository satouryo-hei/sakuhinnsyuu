//=============================================================================
//
// Polygon����
// Author : �V���K�G & ������
//
//=============================================================================
#include "Polygon.h"
#include "manager.h"
#include "Renderer.h"
#include "scene2D.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPolygon::CPolygon(OBJTYPE nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{

}
//------------------------------------------------------------
//���_���W�̐ݒ�
//------------------------------------------------------------

void CPolygon::SetPos(D3DXVECTOR3 pos)
{

	CScene::SetPos(pos);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_Scale.x, pos.y - m_Scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_Scale.x, pos.y - m_Scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_Scale.x, pos.y + m_Scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_Scale.x, pos.y + m_Scale.y, 0.0f);

	m_pVtxBuff->Unlock();

}
//=============================================================================
//������
//=============================================================================
HRESULT CPolygon::Init(void)
{
	CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CScene2D::SetPos(m_Pos, m_Scale);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
//�I��
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//�X�V
//=============================================================================
void CPolygon::Update(void)
{
	CScene2D::Update();
}

//=============================================================================
//�`��
//=============================================================================
void CPolygon::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
//�N���G�C�g
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	//�C���X�^���X����
	CPolygon *pPolygon = new CPolygon(OBJTYPE_POLYGON);

	pPolygon->m_Pos = pos;
	pPolygon->m_Scale = scale;
	pPolygon->m_Tex = texture;

	if (pPolygon != NULL)
	{
		pPolygon->Init();
	}

	return pPolygon;
}