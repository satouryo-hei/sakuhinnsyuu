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
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化関数
	virtual void Uninit(void);								// 終了関数
	virtual void Update(void) = 0;							// 更新関数

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;							//入力デバイス(キーボード)へのポインタ
	static LPDIRECTINPUT8 m_pInput;							//Ditrect Inputオブジェクトのポインタ

};

//=============================================================================
// キーボードの入力クラス
//=============================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();										// コンストラクタ
	~CInputKeyboard();										// デストラクタ
	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			// 初期化関数
	void Uninit(void);										// 終了関数
	void Update(void);										// 更新関数
	bool GetPress(int nKey);								// キーボードの入力情報(プレス情報)の取得
	bool GetTrigger(int nKey);								// キーボードの入力情報(プレス情報)の取得
	bool GetRelease(int nKey);								// キーボードの入力情報(プレス情報)の取得

private:
	BYTE m_aKeyState[NUM_KEY_MAX];							// キーボードの入力情報(プレス情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];					// キーボードの入力情報(トリガー情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];					// キーボードの入力情報(リリース情報)
};

#endif// _INPUT_H_//ifndefとセット（必ず一番下
