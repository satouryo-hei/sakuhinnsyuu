//=============================================================================
//
// 入力処理 [input.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _INPUT_H_//endifとセット（必ず一番上

#define _INPUT_H_

#include "main.h"

//マクロ定義
#define D3DX_PI    ((FLOAT)  3.141592654f) //πのこと
#define NUM_KEY_MAX (256)//キーの最大数

//=============================================================================
// 入力クラス
//=============================================================================
class CInput
{
public:
	CInput();												// コンストラクタ
	virtual ~CInput();										// デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 入力の初期化処理
	virtual void Uninit(void);								// 入力の終了処理
	virtual void Update(void) = 0;							// 入力の更新処理

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice; //入力デバイス(キーボード)へのポインタ
	static LPDIRECTINPUT8 m_pInput; //Ditrect Inputオブジェクトのポインタ

};

//=============================================================================
// キーボードの入力クラス
//=============================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// コンストラクタ
	~CInputKeyboard();								// デストラクタ
	
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// キーボードの入力の初期化処理
	void Uninit(void);								// キーボードの入力の終了処理
	void Update(void);								// キーボードの入力の更新
	bool GetPress(int nKey);						// 押しているキー情報の取得
	bool GetTrigger(int nKey);						// 押されていたキー情報の取得
	bool GetRelease(int nKey);						// 離したキー情報の取得

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報(押されている情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードの入力情報(押されていた情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードの入力情報(リリース情報)
};

#endif// _INPUT_H_//ifndefとセット（必ず一番下
