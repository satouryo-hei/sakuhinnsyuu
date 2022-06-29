//=============================================================================
//
// 壁の管理の処理 [wall_manager.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "wall_manager.h"
#include "wall.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CWall* CWall_Manager::m_pWall[MAX_WALL] = {};

//=============================================================================
// 壁の管理のコンストラクタ
//=============================================================================
CWall_Manager::CWall_Manager(int nPriority) : CScene(PRIORITY_SECOND)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// 壁の管理のデストラクタ
//=============================================================================
CWall_Manager::~CWall_Manager()
{

}

//=============================================================================
// 壁の管理の生成処理
//=============================================================================
CWall_Manager *CWall_Manager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// CWall_Managerクラスのポインターの生成(NULL状態)
	CWall_Manager* pWall_Manager = NULL;
	// 動的メモリの確保
	pWall_Manager = new CWall_Manager;
	// NULLチェック
	if (pWall_Manager != NULL)
	{
		// 壁の設定処理の呼び出し
		pWall_Manager->SetWall(pos,size,rot);
		pWall_Manager->Init(pos);
	}
	return pWall_Manager;
}

//=============================================================================
// 壁の管理の初期化処理
//=============================================================================
HRESULT CWall_Manager::Init(D3DXVECTOR3 pos)
{

	m_pWall[0] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f),	 m_size, D3DXVECTOR3(0.0f, 0, 0.0f));
	m_pWall[1] = CWall::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f),	 m_size, D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	m_pWall[2] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -100.0f), m_size, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_pWall[3] = CWall::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), m_size, D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
	
	return S_OK;
}

//=============================================================================
// 壁の管理の終了処理
//=============================================================================
void CWall_Manager::Uninit(void)
{
	// 壁分回す
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (m_pWall[nCnt] != NULL)
		{
			m_pWall[nCnt]->Uninit();
			m_pWall[nCnt] = NULL;
		}		
	}

	CScene::Release();

}

//=============================================================================
// 壁の管理の更新処理
//=============================================================================
void CWall_Manager::Update(void)
{

}

//=============================================================================
// 壁の管理の描画処理
//=============================================================================
void CWall_Manager::Draw(void)
{

}

//=============================================================================
// 壁の管理の設定処理
//=============================================================================
void CWall_Manager::SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_size = size;
	m_rot = rot;
}