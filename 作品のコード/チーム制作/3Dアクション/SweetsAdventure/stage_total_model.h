//----------------------------------
//���f���̏���
//�쐬�ҁF�с@�C�l
//----------------------------------
#ifndef _STAGE_TOTAL_MODEL_H
#define _STAGE_TOTAL_MODEL_H
#include "main.h"
#include "scene.h"
#include "texture.h"
#define MAX_STAGE_TOTAL_MODEL_TEX (10)
#define MAX_STAGE_TOTAL_MODEL_VTX (8)						//���f���̒��_��

//------------------------------------------------------------------------------
//�N���X�̒�`
//------------------------------------------------------------------------------
class CStage_Total_Model
{
public:
	typedef struct
	{
		D3DXVECTOR3 vtx, rot;
		D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	}ModelVtx;//���f���̊e���_�̕ۑ��p�\����

	CStage_Total_Model();
	~CStage_Total_Model();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadX(const char *sModelFailName);
private:

	LPD3DXMESH				m_pMesh;						//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;						//�}�e���A���i�ގ����j�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture[MAX_STAGE_TOTAL_MODEL_TEX];		//�e�N�X�`��
	DWORD					m_nNumMat;						//�}�e���A���̐�
	D3DXVECTOR3				m_pos, m_layerpos, m_scale;				//���f���̈ʒu�i�I�t�Z�b�g�j
	D3DXVECTOR3				m_rot, m_layerrot;				//����
	ModelVtx				m_vtx[MAX_STAGE_TOTAL_MODEL_VTX];			//�e���_�̏��i�[�\����
	D3DXVECTOR3				m_vtxMin, m_vtxMax;				//���f���̍ŏ��l�A�ő�l
	D3DXMATRIX				m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXMATERIAL			*m_pMat;						//�}�e���A���ւ̃|�C���^
	D3DXMATERIAL			*m_pSaveMat;					//�}�e���A���ւ̃|�C���^�̃Z�[�u
	DWORD					m_sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE					*m_pVtxBuff;					//���_�o�b�t�@�̃|�C���^
	int						m_nNumVtx;						//���_�̐�
	int						m_nNumParent;					//���݂̐e���f���̔ԍ�
	CStage_Total_Model					*m_pParent;						//�e���f���̃|�C���^
	char					m_sFailName[256];
	bool					m_bDraw;						//�`�悷�邩
};


#endif // !_STAGE_TOTAL_MODEL_H
