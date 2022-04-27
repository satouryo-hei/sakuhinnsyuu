//=============================================================================
//
// メイン処理 [renderer.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include"main.h"

//*****************************************************************************
// メイン処理のクラス
//*****************************************************************************
class CRenderer
{
public:																	// 誰でもアクセス可能
	CRenderer();														// コンストラクタ
	~CRenderer();														// デストラクタ
	// メンバ関数
	HRESULT Init(HWND hWnd, bool bWindow);								// 初期化関数
	void Uninit(void);													// 終了関数
	void Update(void);													// 更新関数
	void Draw(void);													// 描画関数
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }			// デバイスの取得関数
private:																// 自分だけがアクセス可能
	void DrawFPS(void);													// FPSの描画関数

	LPDIRECT3D9	m_pD3D;													// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;										// Deviceオブジェクト(描画に必要)
	LPD3DXFONT m_pFont;													// フォントへのポインタ
};
#endif
