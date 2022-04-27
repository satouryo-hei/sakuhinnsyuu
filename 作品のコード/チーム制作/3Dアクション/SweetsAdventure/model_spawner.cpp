//----------------------------------
//�|���S���̏���
//-----------------------------------
#include "model_spawner.h"
#include "input.h"
#include "Renderer.h"
#include "manager.h"
#include "texture.h"
#include "keyboard.h"
#include "model.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel_Spawner::CModel_Spawner(OBJTYPE nPriority) :CScene(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel_Spawner::~CModel_Spawner()
{

}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CModel_Spawner::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void CModel_Spawner::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}

	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CModel_Spawner::Update(void)
{
	m_fRot -= 0.01f;
	if (m_fRot <= -D3DX_PI)
	{
		m_fRot = D3DX_PI;
	}
	if (m_MoveRot == true)
	{
		m_pModel->SetRot(D3DXVECTOR3(0.0f, m_fRot, 0.0f));
	}
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CModel_Spawner::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

																	 //���݂̃}�e���A�����擾
	D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
	D3DMATERIAL9 Matdef;
	//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	////�����𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);
	//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}
//---------------------------------------------------------------
//�C���X�^���X��������
//---------------------------------------------------------------
CModel_Spawner *CModel_Spawner::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�C���X�^���X����
	CModel_Spawner *pSpawner = new CModel_Spawner();
	if (pSpawner != NULL)
	{
		pSpawner->Init();
	}
	//�p�x�����W�A���ɕϊ�
	float rot_x = D3DXToRadian(rot.x);
	float rot_y = D3DXToRadian(rot.y);
	float rot_z = D3DXToRadian(rot.z);

	pSpawner->m_pos = pos;

	if (pSpawner->m_pModel == NULL)
	{
		//���f���̐���
		pSpawner->m_pModel = CModel::Create(pos, D3DXVECTOR3(rot_x, rot_y, rot_z), pFileName);
		//�e���f����NULL�ɐݒ�
		pSpawner->m_pModel->SetParent(NULL);
	}

	return pSpawner;
}
