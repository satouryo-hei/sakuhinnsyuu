//----------------------------------
//�I�u�W�F�N�g�̏���
//----------------------------------
#ifndef _SCENE_H
#define _SCENE_H
#include "main.h"

class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,
		OBJTYPE_FIELD,				//��
		OBJTYPE_MODEL,				//���f��
		OBJTYPE_BLOCK,				//���f��
		OBJTYPE_WOOD,				//���f��
		OBJTYPE_PLAYER,				//�v���C���[
		OBJTYPE_ENEMY,				//�G
		OBJTYPE_ENEMY_BAUM,				//�G
		OBJTYPE_EFFECT,				//�G�t�F�N�g
		OBJTYPE_ITEM,					//UI
		OBJTYPE_POLYGON,
		OBJTYPE_UI,					//UI
		OBJTYPE_PAUSE,				//PAUSE
		OBJTYPE_FADE,				//�t�F�[�h
		OBJTYPE_MAX
	}OBJTYPE;
	CScene();
	CScene(OBJTYPE nPriority);
	virtual~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	void SetObjType(OBJTYPE objType) { m_ObjType = objType; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetDamage(bool bDamage) { m_bDamage = bDamage; }
	void LifeSub(int nPow);
	int GetLife(void) { return m_nLife; }
	void SetPoint(int nPoint) { m_nPoint = nPoint; }
	int GetPoint(void) { return m_nPoint; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetScale(void) { return m_Scale; }
	CScene::OBJTYPE GetObjType(void) { return m_ObjType; }
	bool GetDamage(void) { return m_bDamage; }
	static CScene *GetScene(const int nPriority) { return m_pTop[nPriority]; }
	static CScene *GetSceneNext(CScene *pTop) { return pTop->m_pNext; }

	static void Delete(void);		//�S�ẴC���X�^���X�̔j������
	static void UpdateAll(void);	//�S�ẴI�u�W�F�̍X�V	
	static void DrawAll(void);		//�S�ẴI�u�W�F�̕`��
	
private:
	D3DXVECTOR3				m_pos,m_oldpos;							//��̈ʒu
	D3DXVECTOR3				m_Scale;				//�傫��
	OBJTYPE					m_ObjType;				//�I�u�W�F�N�g�^�C�v�̎��
	static int				m_nNumAll[OBJTYPE_MAX];
	int						m_nID;						//�i�[��̔ԍ�
	int						m_nLife;
	int						m_nPoint;			//�G�̓_��
	int						m_nPriority;//�D�揇��
	bool					m_bDamage;					//�_���[�W����
	static CScene *m_pTop[OBJTYPE_MAX];						//�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[OBJTYPE_MAX];						//���݁i��Ԍ��j�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev;							//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;							//���̃I�u�W�F�N�g�ւ̃|�C���^
	bool					m_bDath;
protected:
	void Release(void);//�I�u�W�F�N�g�P�̂̃C���X�^���X�j��

};


#endif // !_SCENE_H
