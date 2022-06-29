//=============================================================================
//
// �ėp�^�̃��f������ [model.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MODEL_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _MODEL_H_

#include"main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MODEL_TEX (128)//���f���̃e�N�X�`���̍ő吔

//*****************************************************************************
// �ėp�^�̃��f���N���X
//*****************************************************************************
class CModel 
{
public:																						// �N�ł��A�N�Z�X�\
	CModel();																				// �R���X�g���N�^
	~CModel();																				// �f�X�g���N�^
																							// �����o�֐�
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pModelFileName);	// ���f���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char *pModelFileName);				// ���f���̏������֐�
	void Uninit(void);																		// ���f���̏I���֐�
	void Update(void);																		// ���f���̍X�V�֐�
	void Draw(void);																		// ���f���̕`��֐�

	void SetUse(bool bUse) { m_bUse = bUse; }												// �g���Ă��邩�ǂ���
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }											// ���[���h�}�g���b�N�X�̎擾����
	void SetMtx(const D3DXMATRIX &mtxworld) {m_mtxWorld = mtxworld; }						// ���[���h�}�g���b�N�X�̐ݒ菈��
	void SetParent(CModel *pParent) { m_pParent = pParent; }								// �e�̃��f������
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	D3DXVECTOR3 GetPos() { return m_Pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	D3DXVECTOR3 GetSize() { return m_Size; }
	void ReleaseModel(void);

private:																					// �����������A�N�Z�X�\
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEX];											// �e�N�X�`���̃|�C���^�[�̐���
	D3DXMATRIX m_mtxWorld;																	// ���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;																		// ���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;																// �}�e���A���i�ގ����j�ւ̃|�C���^
	D3DXVECTOR3 m_vtxMin, m_vtxMax;															// ���f���̍ŏ��l�A�ő�l
	DWORD m_nNumMat;																		// �}�e���A���̐�
	D3DXVECTOR3 m_Pos;																		// ���݂̈ʒu
	D3DXVECTOR3 m_Size;																		// ���݂̑傫��
	D3DXVECTOR3 m_rot;																		// ���݂̌���
	D3DXVECTOR3 m_rotOld;																	// �O��̌���
	D3DXVECTOR3 m_Vtx[10];																	// �e���f���̒��_���̊i�[�ϐ�
	CModel *m_pParent;																		// �e�̃��f��
	bool m_bUse;																			// �g���Ă��邩�ǂ���
};

#endif // _POLYGON_H_//ifndef�ƃZ�b�g�i�K����ԉ�