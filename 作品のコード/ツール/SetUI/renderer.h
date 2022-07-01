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

	//-----------------------------------------------------------------------------
	//色の種類
	//-----------------------------------------------------------------------------
	typedef enum
	{
		FontCol_WHITE = 0,			// 白
		FontCol_RED,				// 赤
		FontCol_GREEN,				// 緑
		FontCol_BLUE,				// 青
		FontCol_YELLOW,				// 黄色
		FontCol_PURPLE,				// 紫
		FontCol_LIGHT_BLUE,			// 水色
		FontCol_NONE,				// なし
		FontCol_MAX					// 最大数
	} FontCol;

	void DrawFPS(void);													// FPSの描画関数
	void DrawUiInfo(void);												// UIの情報描画関数
	void DrawUiControl(void);											// UIの操作方法描画関数	
	void ColorFont(void);												// 操作方法を表示させるかどうか関数

	// メンバ変数
	LPDIRECT3D9	m_pD3D;													// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;										// Deviceオブジェクト(描画に必要)
	LPD3DXFONT m_pFont;													// フォントへのポインタ
	LPD3DXFONT m_pUiFont;												// フォントへのポインタ	
	bool m_bUIControl;													// 操作方法を表示するかどうか
	D3DXCOLOR m_FontCol;												// フォントのカラー
	int m_FontColType;													// フォントのカラーの種類
	bool m_bColorTrigger;												// 押し続けて変更されるかどうか

};
#endif
