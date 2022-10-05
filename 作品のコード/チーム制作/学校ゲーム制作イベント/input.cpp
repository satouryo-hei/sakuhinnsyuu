//=============================================================================
//
// 入力の処理 [input.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "input.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// 入力クラスのコンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL; //入力デバイス(キーボード)へのポインタの初期化
}

//=============================================================================
// 入力クラスのデストラクタ
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// 入力クラスの初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	//Ditrect InputオブジェクトのポインタがNULLだったら
	if (m_pInput == NULL)
	{
		// 入力デバイスを入力されたか判断する
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return hr;	
}

//=============================================================================
// 入力クラスの終了処理
//=============================================================================
void CInput::Uninit(void)
{
	// 入力デバイス(キーボードの開放)
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();

		m_pDevice->Release();

		m_pDevice = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{	
		m_pInput->Release();
		
		m_pInput = NULL;
	}
}

//=============================================================================
// キーボード入力クラスのコンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));					//0クリア
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));		//0クリア
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));		//0クリア
}

//=============================================================================
// キーボード入力クラスのデストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// キーボード入力クラスの初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//メガデバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}


//=============================================================================
// キーボード入力クラスの終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// 入力クラスの終了処理の呼び出し
	CInput::Uninit();
}


//=============================================================================
// キーボード入力クラスの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	// キーボードの入力情報
	BYTE aKeyState[NUM_KEY_MAX];

	// カウント用の変数
	int nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			/*
			AND(1&1=1それ以外は0)
			XOR(キャロット(^)1^1または0^0なら0,
			1^0または0^1なら1)
			トリガー情報(0か1)= (プレス情報(0か1)^入力情報(0か1))&入力情報(0か1)
			*/
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			/*
			AND(1&1=1それ以外は0)
			XOR(キャロット(^)1^1または0^0なら0,
			1^0または0^1なら1)
			リリース情報(0か1)= (プレス情報(0か1)^入力情報(0か1))&プレス情報(0か1)
			*/
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];

			m_aKeyState[nCntKey] = aKeyState[nCntKey];// キーボードの入力情報保存
		}
	}
	else
	{
		m_pDevice->Acquire();// キーボードへのアクセス権を獲得
	}
}


//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	/* 
	m_aKeyState[nKey] &(AND(1&1=1それ以外は0)) 128(0b1000 0000)
	a?b:c aが真ならb, aが偽ならcが返される
	(...)?true:falseは真(1)ならtrue, 偽(0)ならfalse*/
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}


//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	/* m_aKeyStateTrigger[nKey] &(AND(1&1=1それ以外は0)) 128(0b1000 0000)
	a?b:c aが真ならb, aが偽ならcが返される
	(...)?true:falseは真(1)ならtrue, 偽(0)ならfalse*/
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}


//=============================================================================
// キーボードの入力情報(リリース情報)を取得
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	/* m_aKeyStateRelease[nKey] &(AND(1&1=1それ以外は0)) 128(0b1000 0000)
	a?b:c aが真ならb, aが偽ならcが返される
	(...)?true:falseは真(1)ならtrue, 偽(0)ならfalse*/
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}