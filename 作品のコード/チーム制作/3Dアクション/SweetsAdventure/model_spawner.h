//----------------------------------
//���f����z�u���邽�߂̏���
//----------------------------------
#ifndef _MODEL_SPAWNER_H
#define _MODEL_SPAWNER_H
#include "main.h"
#include "scene.h"
#include "texture.h"
class CModel;

//------------------------------------------------------------------------------
//�N���X�̒�`
//------------------------------------------------------------------------------
class CModel_Spawner : public CScene
{
public:
	CModel_Spawner(OBJTYPE nPriority = OBJTYPE_MODEL);
	~CModel_Spawner();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel_Spawner *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char *pFileName);//rot�͊p�x������
	CModel *GetModel(void) { return m_pModel; }			//���f�����̎擾
	void SetRot(float fRot) {m_rot.y = fRot;}
	void SetSRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSPos(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetBoolRot(bool bRot) { m_MoveRot = bRot; }
private:
	float m_fRot;
	bool m_MoveRot;//��]���郂�f���ɂȂ邩�̔���
	D3DXVECTOR3				m_pos;					//���f���̈ʒu�i�I�t�Z�b�g�j
	D3DXVECTOR3				m_rot;					//����
	D3DXMATRIX				m_mtxWorld;				//���[���h�}�g���b�N�X
	D3DXMATERIAL			*m_pMat;						//�}�e���A���ւ̃|�C���^
	CModel					*m_pModel;
};


#endif // !_MODEL_SPAWNER_H
