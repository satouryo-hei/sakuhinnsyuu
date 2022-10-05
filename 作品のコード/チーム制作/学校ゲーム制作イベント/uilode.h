//=============================================================================
//
// UIの読み込みの処理 [uilode.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _UILODE_H_
#define _UILODE_H_

#define MAX_UI (12)
#include"main.h"

//*****************************************************************************
// UIの読み込みクラス
//*****************************************************************************
class CUilode
{
public:																			// 誰でもアクセス可能
	CUilode(const char * pFileNeme);											// コンストラクタ
	~CUilode();																	// デストラクタ

	D3DXVECTOR3 GetUIPos(int nNum) { return m_LodePos[nNum]; }					// 読み込んだ位置を返す
	D3DXVECTOR2 GetUISize(int nNum) { return m_LodeSize[nNum]; }				// 読み込んだ大きさを返す

private:																		// 自分だけがアクセス可能
	inline void Lode(const char * pFileNeme);	
	static int m_nMaxUI;														// テクスチャの最大数	
	D3DXVECTOR3 m_LodePos[MAX_UI];												// uiの位置の読み込み
	D3DXVECTOR2 m_LodeSize[MAX_UI];												// uiの大きさの読み込み
};
#endif