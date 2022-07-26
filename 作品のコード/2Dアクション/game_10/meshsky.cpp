//=============================================================================
//
// ���b�V���̋�̏��� [meshsky.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"meshsky.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"scene3D.h"
#include"texture.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshSky::m_pTexTure = NULL;

//=============================================================================
// ���b�V���̋�̃R���X�g���N�^
//=============================================================================
CMeshSky::CMeshSky(PRIORITY Priority) : CScene(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMeshX =0;
	m_nMeshY =0;
}

//=============================================================================
//�@���b�V���̋�̃f�X�g���N�^
//=============================================================================
CMeshSky::~CMeshSky()
{

}


//=============================================================================
// ���b�V���̋�̐�������
//=============================================================================
CMeshSky *CMeshSky::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int meshX, int meshY)
{
	// ���b�V���̋�̃|�C���^�[����
	CMeshSky* pMeshSky = NULL;

	// ���I�������̊m��
	pMeshSky = new CMeshSky;

	//�@NULL�`�F�b�N
	if (pMeshSky != NULL)
	{
		pMeshSky->Init(pos, size, meshX, meshY);
		pMeshSky->m_rot = rot;
	}
	return pMeshSky;
}

//=============================================================================
// ���b�V���̋�̃f�t�H���g����������
//=============================================================================
HRESULT CMeshSky::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}
//=============================================================================
// �|���S���̏���������
//=============================================================================								
HRESULT CMeshSky::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int meshX, int meshY)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�������(X,Y,Z)
	m_Size = size;

	Init(pos);

	BindTextuer(2);

	m_nMeshX = meshX;
	m_nMeshY = meshY;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((meshX + 1) * (meshY + 1)) * 1,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	int nNum = 0;
	for (int nCntY = 0; nCntY < meshY + 1; nCntY++)
	{
		for (int nCntX = 0; nCntX < meshX + 1; nCntX++, nNum++)
		{
			pVtx[nNum].pos = D3DXVECTOR3(
				cos((D3DX_PI * 2 / meshX) * nCntX) * (sin(((D3DX_PI * 2 / meshX) * nCntY) + ((D3DX_PI * 2 / meshX) * meshY)) * (size.x / 2.0f)),
				sin((D3DX_PI * 2 / meshX) * nCntY) * (size.x / 2.0f),
				(sin((D3DX_PI * 2 / meshX) * nCntX) * (sin(((D3DX_PI * 2 / meshX) * nCntY) + ((D3DX_PI * 2 / meshX) * meshY)) * (size.x / 2.0f))));


			pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f / meshX * nCntX), 0.0f + (1.0f / meshY * nCntY));
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((meshY - 1) * (meshX + 3) + (meshX + 1) * (meshY + 1)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);


	WORD*pIdx; //�C���f�b�N�X���ւ̃|�C���^

			   //�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	/*�C���f�b�N�X�������߂����
	(�S�Ă̒��_��)+(���Ԃ蒸�_��)
	((x+1)*(z+1))+((x+3)*(z-1)) */
	for (int nCntZ = 0; nCntZ < meshY; nCntZ++)
	{
		for (int nCntX = 0; nCntX < meshX + 1; nCntX++)
		{
			//�ԍ��f�[�^�̐ݒ�
			pIdx[(nCntX * 2) + 0 + (meshX + 2) * 2 * nCntZ] = (meshX + 1) + nCntX + (meshX + 1) * nCntZ;
			pIdx[(nCntX * 2) + 1 + (meshX + 2) * 2 * nCntZ] = 0 + nCntX + (meshX + 1) * nCntZ;
		}
	}
	for (int nCntY = 0; nCntY < meshY - 1; nCntY++)
	{
		pIdx[((meshX + 1) * 2 + 0) * (nCntY + 1) + (2 * nCntY)] = meshX + (meshX + 1) * nCntY;
		pIdx[((meshX + 1) * 2 + 1) * (nCntY + 1) + (1 * nCntY)] = meshX * 2 + 2 + (meshX + 1) * nCntY;
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;

}

//=============================================================================
// ���b�V���̋�̏I������
//=============================================================================
void CMeshSky::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//=============================================================================
// ���b�V���̋�̍X�V����
//=============================================================================
void CMeshSky::Update(void)
{
	m_rot.y += 0.0005f;
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
}

//=============================================================================
// ���b�V���̋�̕`�揈��
//=============================================================================								
void CMeshSky::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�̃}�g���b�N�X

	//CManager*pManager = NULL;

	//�f�o�C�X���擾����
	pDevice = CManager::GetRenderer()->GetDevice();

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

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

								   //�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexTure);

	
	//�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, (m_nMeshY - 1) * (m_nMeshX + 3) + (m_nMeshX + 1) * (m_nMeshY + 1));

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		0,
		((m_nMeshX + 1) * (m_nMeshY + 1)),					//���_�̐�
		0,													//�J�n���钸�_�̃C���f�b�N�X
		2 * m_nMeshX * m_nMeshY + (m_nMeshY * 4) - 4);		//�`�悷��v���~�e�B�u��
}

//=============================================================================
// ���b�V���̋�̃e�N�X�`���̐ݒ�
//=============================================================================
void CMeshSky::BindTextuer(int nTextuer)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTextuer);
}