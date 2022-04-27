//=============================================================================
//
// マネージャー処理 [main.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;		
class CInputKeyboard;
class CCamera;
class CLight;
class CScene3D;
class CTexture;
class CEffect_Manager;

//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:
	CManager();											// コンストラクタ
	~CManager();										// デストラクタ
														// メンバ関数
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// ポリゴンの初期化関数
	void Uninit(void);									// ポリゴンの終了関数　
	void Update(void);									// ポリゴンの更新関数
	void Draw(void);									// ポリゴンの描画関数
	
	static CRenderer*GetRenderer(void){ return m_pRenderer; }
	static CInputKeyboard*GetInputKeyboard(void){ return m_pInputKeyboard; }
	static CScene3D*GetScene3D(void) { return m_pScene3D; }
	static CCamera*GetCamera(void) { return m_pCamera; }
	static CLight*GetLight(void) { return m_pLight[0]; }
	static CTexture*GetTexture(void) { return m_pTexture; }
	static CEffect_Manager*GetEffectManager(void) { return m_pEffect_Manager; }

private:												// 自分だけがアクセス可能
	static CRenderer*m_pRenderer;						//インスタンス生成
	static CInputKeyboard*m_pInputKeyboard;
	static CScene3D * m_pScene3D;
	static CCamera * m_pCamera;
	static CLight * m_pLight[3];
	static CTexture * m_pTexture;
	static CEffect_Manager * m_pEffect_Manager;
};
#endif
