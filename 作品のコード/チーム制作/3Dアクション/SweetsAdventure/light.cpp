//----------------------------------
//�|���S���̏���
//-----------------------------------
#include "light.h"
#include "input.h"
#include "Renderer.h"
#include "manager.h"
int CLight::m_nCntLight = 0;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{
	//�������̃J�E���g
	m_nId = m_nCntLight;
	//�J�E���g����
	m_nCntLight++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
	m_nCntLight--;
}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CLight::Init(D3DXCOLOR Diffuse, D3DXVECTOR3 vecDir)
{
	//���C�g���N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 r_vecDir;//�ݒ�p�̃x�N�g��
	pDevice = CManager::GetRenderer()->GetDevice();
	//���C�g�̎�ނ�ݒ�
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	//���C�g�̊g�U��
	m_light.Diffuse = Diffuse;
	//���C�g�̕�����ݒ�
	r_vecDir = vecDir;
	D3DXVec3Normalize(&r_vecDir, &r_vecDir);//���K������
	m_light.Direction = r_vecDir;
	//���C�g�̐ݒ�
	pDevice->SetLight(m_nId, &m_light);
	//���C�g��L���ɂ���
	pDevice->LightEnable(m_nId, TRUE);


	return S_OK;
}

