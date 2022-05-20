//=============================================================================
//
// Xモデル読み込み処理 [lode_x.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _LODE_X_H_
#define _LODE_X_H_

#define PLAYER_TEXT "data/TEXT/Player.txt"

#include"main.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CLode_X
{
public:															// 誰でもアクセス可能

	//// xファイルの種類
	//typedef enum 
	//{
	//	XTYPE_NOME = 0,
	//	XTYPE_NOME,
	//	XTYPE_NOME,
	//	XTYPE_MAX
	//} XTYPE;

	CLode_X();													// コンストラクタ
	~CLode_X();												// デストラクタ
																// メンバ関数
	HRESULT Init(void);											// テクスチャの初期化関数
	void Uninit(void);											// テクスチャの終了関数

private:														// 自分だけがアクセス可能
	inline void Lode(void);										// 
	static int m_nMaxTex;										// テクスチャの最大数
	LPD3DXBUFFER m_pBuffMat;																// マテリアル（材質情報）へのポインタ
	DWORD m_nNumMat;																		// マテリアルの数
	LPD3DXMESH m_pMesh;																		// メッシュ（頂点情報）へのポインタ
};
#endif