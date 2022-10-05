//=============================================================================
//
// ���f���N���X [model.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_VTX 8
#define MODEL_TEX 5

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CXload;
//*****************************************************************************
//	���f���N���X
//*****************************************************************************
class CModel
{
public:
	CModel();	// �f�t�H���g�R���X�g���N�^
	~CModel();	// �f�X�g���N�^

	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	// ��������
	static CModel *Create(const char *pModelFileName);	

	// �擾����
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// �p�[�c�̈ʒu
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			// �p�[�c�̌���
	D3DXVECTOR3 GetSize(void) { return m_size; }			// �p�[�c�̑傫��

	// �ݒ菈��
	void SetModelFile(const char *pModelFileName) { m_pModelFileName = pModelFileName; }	// ���f���t�@�C����
	void SetParent(CModel *pModel) { m_pParent = pModel; }	// �e���f����ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// �p�[�c�̈ʒu
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// �p�[�c�̌���

private:
	LPDIRECT3DTEXTURE9	m_pTexture[MODEL_TEX];	// �e�N�X�`���̃|�C���^
	LPD3DXMESH			m_pMesh;				// ���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER		m_pBuffMat;				// �}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD				m_nNumMat;				// �}�g���b�N�X��
	CModel				*m_pParent;				// �e���f���ւ̃|�C���^
	int					m_nIdxParent;			// �e���f���̃C���f�b�N�X
	D3DXMATRIX			m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;					// �ʒu
	D3DXVECTOR3			m_rot;					// ����
	D3DXVECTOR3			m_size;					// �傫��
	D3DXVECTOR3			m_vtxMin, m_vtxMax;		// ���_�̍ŏ��l�A�ő�l
	const char			*m_pModelFileName;		// ���f���t�@�C����
};
#endif //!_MODEL_H_