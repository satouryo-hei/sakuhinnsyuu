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
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice; //入力デバイス(キーボード)へのポインタ
	static LPDIRECTINPUT8 m_pInput; //Ditrect Inputオブジェクトのポインタ

};

//=============================================================================
// キーボードのクラス
//=============================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			//キーボードの入力情報(プレス情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//キーボードの入力情報(トリガ情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//キーボードの入力情報(リリース情報)
};

#endif// _INPUT_H_//ifndefとセット（必ず一番下
