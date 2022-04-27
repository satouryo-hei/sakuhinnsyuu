#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"	
#include "Scene3D.h"
#include "goal.h"

CGoal::CGoal(OBJTYPE nPriority) :CBillboard(nPriority)
{

}

CGoal::~CGoal()
{

}

//---------------------------------------------------------------
//�C���X�^���X��������
//---------------------------------------------------------------
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::Type Tex)
{
	//�C���X�^���X����
	CGoal *pGoal = new CGoal();
	pGoal->m_pos = pos;
	pGoal->m_size = size;
	pGoal->SetScale(size);
	pGoal->SetPos(pos);
	if (pGoal != NULL)
	{
		pGoal->m_pBillboard = CBillboard::Create(pos, size, Tex);

		pGoal->Init();
	}

	return pGoal;
}


HRESULT CGoal::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGoal::Uninit(void)
{
	if (m_pBillboard != NULL)
	{
		m_pBillboard->Uninit();
		delete m_pBillboard;
		m_pBillboard = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGoal::Update(void)
{

}
//=======================================================================
//�`�揈��
//=======================================================================
void CGoal::Draw()
{
}

