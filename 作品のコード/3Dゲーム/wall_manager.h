//=============================================================================
//
// 壁の管理の処理 [wall_manager.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _WALL_MANAGER_H_
#define _WALL_MANAGER_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_WALL (4)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CWall;

//*****************************************************************************
// 壁の管理のクラス
//*****************************************************************************
class CWall_Manager : public CScene
{
public:
	CWall_Manager(int nPriority = PRIORITY_NOMAL);										// コンストラクタ
	~CWall_Manager();																	// デストラクタ

	// メンバ関数
	static CWall_Manager *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);	// 壁の管理の生成
	HRESULT Init(D3DXVECTOR3 pos);												// 壁の管理の初期化関数
	void Uninit(void);															// 壁の管理の終了関数　
	void Update(void);															// 壁の管理の更新関数
	void Draw(void);															// 壁の管理の描画関数


private:																		// 自分だけがアクセス可能
	void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);			// 壁の設定
	// メンバ変数
	static CWall * m_pWall[MAX_WALL];											// 壁のポインター
	D3DXVECTOR3 m_pos;															// 位置
	D3DXVECTOR3 m_size;															// 大きさ
	D3DXVECTOR3 m_rot;															// 向き
};

//乗算処理
template<class T, class P> T Multiplication(T data0, P data1)
{
	T answer;
	answer = data0 * data1;
	return answer;
}
#endif