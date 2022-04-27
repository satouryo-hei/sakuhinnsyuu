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
	//静的メンバー関数
	static CBarrier_Block *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	CModel_Spawner *GetModel(void) { return m_pModel; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetUninit(bool Uninit) { m_bUninit = Uninit; }
private:
	CModel_Spawner *m_pModel;

	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_lotPos;//前回の位置;
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_Lotrot; //前回の向き
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	int		m_nLife;
	bool m_bUninit;
};


#endif // !_PLAYER_H_

