#ifndef _BARRIER_BLOCK_H_
#define _BARRIER_BLOCK_H_
#include "scene.h"
#include "model.h"
#include "motion.h"
#define MAX_BLOCKLIFE (1)
class CModel_Spawner;

class CBarrier_Block : public CScene
{
public:
	CBarrier_Block(OBJTYPE nPriority = CScene::OBJTYPE_BLOCK);
	~CBarrier_Block();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	//�ÓI�����o�[�֐�
	static CBarrier_Block *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	CModel_Spawner *GetModel(void) { return m_pModel; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetUninit(bool Uninit) { m_bUninit = Uninit; }
private:
	CModel_Spawner *m_pModel;

	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_lotPos;//�O��̈ʒu;
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_Lotrot; //�O��̌���
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	int		m_nLife;
	bool m_bUninit;
};


#endif // !_PLAYER_H_

