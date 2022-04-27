//----------------------------------
//���f���̏���
//�쐬�ҁF�с@�C�l
//----------------------------------
#ifndef _MODEL_H
#define _MODEL_H
#include "main.h"
#include "scene.h"
#include "texture.h"
#define MAX_MODEL_TEX (10)
#define MAX_MODEL_VTX (8)						//���f���̒��_��

//------------------------------------------------------------------------------
//�N���X�̒�`
//------------------------------------------------------------------------------
class CModel
{
public:
	typedef struct
	{
		D3DXVECTOR3 vtx, rot;
		D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	}ModelVtx;//���f���̊e���_�̕ۑ��p�\����

	CModel();
	~CModel();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char *sModelFailName, D3DXVECTOR3 scale= D3DXVECTOR3(1.0f,1.0f,1.0f));//�t�@�C���l�[���̓t�@�C���̃p�X������
	void SetParent(CModel *pModel) {m_pParent = pModel;}//�e�̃��f������
	D3DXMATRIX GetMatrix(void) {return m_mtxWorld;}//���[���h�}�g���b�N�X�̎擾
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetLayerPos(D3DXVECTOR3 pos) { m_layerpos = pos; }
	void SetLayerRot(D3DXVECTOR3 rot) { m_layerrot = rot; }
	D3DXVECTOR3 GetLayerPos(void) { return m_layerpos; }
	D3DXVECTOR3 GetLayerRot(void) { return m_layerrot; }
	void SetDiffuse(float DiffuseA);
	D3DXMATERIAL *GetMat(void) { return m_pSaveMat; }
	void SetNumParent(int Parent) { m_nNumParent = Parent; }
	int GetNumParent(void) { return m_nNumParent; }
	ModelVtx GetVtx(int nNumVtx) { return m_vtx[nNumVtx]; }//�e���f���̒��_���̎擾
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }//���[���h�}�g���b�N�X�̎擾
	D3DXVECTOR3 GetMaxPos(void) { return m_vtxMin; }
	D3DXVECTOR3 GetMinPos(void) { return m_vtxMax; }
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }
private:

	LPD3DXMESH				m_pMesh;						//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;						//�}�e���A���i�ގ����j�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture[MAX_MODEL_TEX];		//�e�N�X�`��
	DWORD					m_nNumMat;						//�}�e���A���̐�
	D3DXVECTOR3				m_pos,m_layerpos,m_scale;				//���f���̈ʒu�i�I�t�Z�b�g�j
	D3DXVECTOR3				m_rot, m_layerrot;				//����
	ModelVtx				m_vtx[MAX_MODEL_VTX];			//�e���_�̏��i�[�\����
	D3DXVECTOR3				m_vtxMin, m_vtxMax;				//���f���̍ŏ��l�A�ő�l
	D3DXMATRIX				m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXMATERIAL			*m_pMat;						//�}�e���A���ւ̃|�C���^
	D3DXMATERIAL			*m_pSaveMat;					//�}�e���A���ւ̃|�C���^�̃Z�[�u
	DWORD					m_sizeFVF;						//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE					*m_pVtxBuff;					//���_�o�b�t�@�̃|�C���^
	int						m_nNumVtx;						//���_�̐�
	int						m_nNumParent;					//���݂̐e���f���̔ԍ�
	CModel					*m_pParent;						//�e���f���̃|�C���^
	char					m_sFailName[256];
	bool					m_bDraw;						//�`�悷�邩
};


#endif // !_MODEL_H
