#ifndef _BARRIER_WOOD_H_
#define _BARRIER_WOOD_H_
#include "scene.h"
#include "model.h"
#include "motion.h"
#define MAX_BARRIER_WOOD_PARTS (2)	//�ő�p�[�c��
#define MAX_WOOD_LIFE (1)
class CModel_Spawner;
class CBarrier_wood : public CScene
{
public:
	CBarrier_wood(OBJTYPE nPriority = CScene::OBJTYPE_WOOD);
	~CBarrier_wood();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	//�ÓI�����o�[�֐�
	static CBarrier_wood *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	CModel_Spawner *GetModel(void) { return m_pWood; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetUninit(bool Uninit) { m_bUninit = Uninit; }
private:
	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_lotPos;//�O��̈ʒu;
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_Lotrot; //�O��̌���
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	CModel *m_pModel[MAX_BARRIER_WOOD_PARTS];
	CModel_Spawner *m_pWood;

	int		m_nLife;
	bool m_bUninit;
};
#endif // !_PLAYER_H_

