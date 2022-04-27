//=============================================================================
//
// 入力処理 [input.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _INPUT_H_//endifとセット（必ず一番上

#define _INPUT_H_

#include "main.h"
#include<XInput.h>

//マクロ定義
#define D3DX_PI    ((FLOAT)  3.141592654f) //πのこと
#define NUM_KEY_MAX (256)//キーの最大数

//=============================================================================
// 入力クラス
//=============================================================================
class CInput
{
public:														// 誰でもアクセス可能
	CInput();												// コンストラクタ
	virtual ~CInput();										// デストラクタ
															// メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 入力の初期化関数
	virtual void Uninit(void);								// 入力の終了関数　
	virtual void Update(void) = 0;							// 入力の更新関数
															
protected:													
	// メンバ変数
	LPDIRECTINPUTDEVICE8 m_pDevice;							//入力デバイス(キーボード)へのポインタ
	static LPDIRECTINPUT8 m_pInput;							//Ditrect Inputオブジェクトのポインタ

};

//=============================================================================
// キーボードのクラス
//=============================================================================
class CInputKeyboard : public CInput
{
public:				
	CInputKeyboard();									// コンストラクタ
	~CInputKeyboard();									// デストラクタ

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// キーボードの初期化関数
	void Uninit(void);									// キーボードの終了関数　
	void Update(void);									// キーボードの更新関数
	bool GetPress(int nKey);							// キーボードを押し続けれる関数
	bool GetTrigger(int nKey);							// キーボードを1回のみ押される関数
	bool GetRelease(int nKey);							// キーボードを離したとき関数

private:
	BYTE m_aKeyState[NUM_KEY_MAX];						//キーボードの入力情報(プレス情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//キーボードの入力情報(トリガ情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];				//キーボードの入力情報(リリース情報)
};

#endif// _INPUT_H_//ifndefとセット（必ず一番下
