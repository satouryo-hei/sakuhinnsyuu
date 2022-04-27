//=============================================================================
//
// �e�N�X�`���̏��� [texture.h]
// Author : �����ĕ�
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
int CTexture::m_nMaxTex = 0;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̏���������
//=============================================================================
HRESULT CTexture::Init(void)
{
	Lode();
	return S_OK;
}

//=============================================================================
// �e�N�X�`���̏I������
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nMaxTex; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
void CTexture::Lode(void)
{
	CManager * pManager = NULL;
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	char aFile[256];
	int nCnt = 0;

	FILE *pFile = fopen(TEXTURE_TEXT, "r");

	if (pFile != NULL)//��x�t�@�C����ǂݍ���ŕK�v�ȏ��𔲂�
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTURE�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxTex);
			}

			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAME�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);			
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_pTexture[nCnt]);
				
				nCnt++;
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}
		}
	}
	fclose(pFile);
}