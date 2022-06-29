//=============================================================================
//
// ゲームの選択の処理 [choose_game.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"choose_game.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"polygon.h"
#include"fade.h"
#include"effect.h"
#include"explanation.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CChoose_Game::m_bNewGame = false;
CPolygon * CChoose_Game::m_pPolygon[CHOOSE_MAX] = {};
CExplanation * CChoose_Game::m_pExplanation = {};
CEffect * CChoose_Game::m_pEffect = NULL;
const char * CChoose_Game::m_pChooseUiFile = "data/TEXT/ChooseUi.txt";
bool CChoose_Game::m_bGame = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CChoose_Game::CChoose_Game(PRIORITY Priority) :CScene(PRIORITY_UI), ResetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f))
{
	m_bFade = true;
	m_nSituation = CHOOSE_NEWGAME;
	m_Size = D3DXVECTOR2(100, 50);
	m_bEffectUse = true;
	m_nRamNum = 0;
}


//=============================================================================
// デストラクタ
//=============================================================================
CChoose_Game::~CChoose_Game()
{

}

//=============================================================================
// ゲームの選択の生成処理
//=============================================================================
CChoose_Game *CChoose_Game::Create(D3DXVECTOR3 pos)
{
	// ゲームの選択のポインター生成
	CChoose_Game* pChoose_Game = NULL;

	// 動的メモリの確保
	pChoose_Game = new CChoose_Game;

	// NULLチェック
	if (pChoose_Game != NULL)
	{
		// ゲームの選択の初期化の呼び出し
		pChoose_Game->Init(pos);
	}
	return pChoose_Game;
}

//=============================================================================
// ゲームの選択の初期化処理
//=============================================================================
HRESULT CChoose_Game::Init(D3DXVECTOR3 pos)
{
	// ゲームの選択のUIの読み込みの呼び出し
	LodeChooseUI();

	// エフェクトの生成処理の呼び出し
	m_pEffect = CEffect::Create(m_LodePos[m_nSituation]);

	// CHOOSE_MAX分回す
	for (int nCnt = 0; nCnt < CHOOSE_MAX; nCnt++)
	{	
		// エフェクトの生成処理の呼び出し
		m_pPolygon[nCnt] = CPolygon::Create(m_LodePos[nCnt], m_LodeSize[nCnt], nCnt + 6);

		// エフェクトの生成処理の呼び出し
		m_pExplanation = CExplanation::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 18);		
	}

	// ランダムで番号を決める
	m_nRamNum = rand() % 4;

	// エフェクトポリゴンの色設定処理
	SetPolygonColor();

	return S_OK;
}	// ゲームの選択の初期化処理の終了



//=============================================================================
// ゲームの選択の終了処理
//=============================================================================
void CChoose_Game::Uninit(void)
{
	// CHOOSE_MAX分回す
	for (int nCnt = 0; nCnt < CHOOSE_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->SetUse(false);
			m_pPolygon[nCnt] = NULL;
		}
	}
	
	// ゲームの選択の解放
	Release();

}// ゲームの選択の終了処理の終了


//=============================================================================
// ゲームの選択の更新処理
//=============================================================================
void CChoose_Game::Update(void)
{
	// 左キーを押されて時
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_LEFT) == true)
	{
		m_nSituation--;
		if (m_nSituation < CHOOSE_NEWGAME)
		{
			m_nSituation = CHOOSE_MAX - 1;
		}		
	}
	// 右キーを押されて時
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_RIGHT) == true)
	{
		m_nSituation++;
		if (m_nSituation > CHOOSE_MAX - 1)
		{
			m_nSituation = CHOOSE_NEWGAME;
		}		
	}
	// 色を初期化する
	Resetcol();
	
	// 選択されているものの色を鮮明にする
	m_pPolygon[m_nSituation]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pEffect->Setpos(m_LodePos[m_nSituation]);
	m_pExplanation->SetSize(D3DXVECTOR2(250, 200), 0);
	m_pExplanation->SetSize(D3DXVECTOR2(200, 50), m_nSituation + 1);
	m_pExplanation->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_nSituation+1);

	// 選択された時の処理
	switch (m_nSituation)
	{
	// 新しくゲームを始めたとき
	case CHOOSE_NEWGAME:				
		m_pEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// 新しい状態でゲームを始めさせる
			m_bNewGame = true;
			// ゲーム画面に遷移
			CFade::SetFade(CManager::MODE_GAME);
			// 連続でフェード遷移をさせないようにする
			m_bFade = false;
			// ゲームに遷移したよって教える
			m_bGame = true;
		}
		break;

	// 続きからゲームを始めたとき
	case CHOOSE_CONTINUE:
		//m_pExplanation[CHOOSE_CONTINUE]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// つづかせる状態でゲームを始めさせる
			m_bNewGame = false;
			// ゲーム画面に遷移
			CFade::SetFade(CManager::MODE_GAME);
			// 連続でフェード遷移をさせないようにする
			m_bFade = false;
			// ゲームに遷移したよって教える
			m_bGame = true;
		}
		break;

	// チュートリアルに行くとき
	case CHOOSE_TUTORIAL:	
		//m_pExplanation[CHOOSE_TUTORIAL]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{	
			// チュートリアル画面に遷移
			CFade::SetFade(CManager::MODE_TUTORIAL);
			// 連続でフェード遷移をさせないようにする
			m_bFade = false;
			// ゲームに遷移してないって教える
			m_bGame = false;
		}
		break;

	// リザルトに行くとき
	case CHOOSE_RESULT:		
		//m_pExplanation[CHOOSE_RESULT]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// リザルト画面に遷移
			CFade::SetFade(CManager::MODE_RESULT);
			// 連続でフェード遷移をさせないようにする
			m_bFade = false;
			// ゲームに遷移してないって教える
			m_bGame = false;
		}
		break;

	// それ以外のとき
	default:
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// タイトル画面に遷移
			CFade::SetFade(CManager::MODE_TITLE);
			// 連続でフェード遷移をさせないようにする
			m_bFade = false;
		}
		break;
	}

}// ゲームの選択の更新処理終了



//=============================================================================
// ゲームの選択の描画処理
//=============================================================================
void CChoose_Game::Draw(void)
{	

}	// ゲームの選択の描画処理終了

//=============================================================================
// ゲームの選択の色を初期化処理
//=============================================================================
void CChoose_Game::Resetcol(void)
{
	for (int nCnt = 0; nCnt < CHOOSE_MAX; nCnt++)
	{
		// ポリゴンの色を設定
		m_pPolygon[nCnt]->SetColor(ResetCol);			

		// エフェクトの生成処理の呼び出し
		m_pExplanation->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), nCnt+1);
	}
}

//=============================================================================
// ゲームの選択のUIの読み込み処理
//=============================================================================
void CChoose_Game::LodeChooseUI(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(m_pChooseUiFile, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1列を読み込み(2行目以降は上書きされる)

			if (strcmp(&aFile[0][0], "NUM_UI") == 0)								// NUM_UIが見つかったら
			{
				fscanf(pFile, "%s%d", &aName[0], &m_nLodeUI);						// UIの数を読み込む
			}

			while (strcmp(&aFile[0][0], "SETUI") == 0)								// SETUIが見つかったら
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1列を読み込み(2行目以降は上書きされる)
				if (strcmp(&aFile[1][0], "POS") == 0)								// POSが見つかったら
				{
					fscanf(pFile, "%s%f%f%f", &aName[0], &pos.x, &pos.y, &pos.z);	// 現在の位置を読み込む
				}
				else if (strcmp(&aFile[1][0], "SIZE") == 0)							// SIZEが見つかったら
				{
					fscanf(pFile, "%s%f%f", &aName[0], &size.x, &size.y);			// 現在の大きさを読み込む
				}
				else if (strcmp(&aFile[1][0], "END_SETUI") == 0)					// END_SETUIが見つかったら
				{
					m_LodePos[nSetCnt] = pos;										// 読み込んだ位置情報をメンバのSetPosに移す
					m_LodeSize[nSetCnt] = size;										// 読み込んだ大きさ情報をメンバのSetSizeに移す
					nSetCnt++;														// 次の方
					break;															// 無限ループを抜ける
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)							// END_SCRIPTが見つかったら
			{
				break;																// 無限ループを抜ける
			}
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	// 閉じれ～ファイル！
	fclose(pFile);
}

//=============================================================================
// エフェクトポリゴンの色設定処理
//=============================================================================
void CChoose_Game::SetPolygonColor(void)
{
	for (int nCnt = 0; nCnt < VTXBUFFER_MAX; nCnt++)
	{
		// マックス値まで行ったら0に戻す
		if (m_nRamNum >= VTXBUFFER_MAX)
		{
			m_nRamNum = VTXBUFFER_ZERO;
		}
		// 0まで行ったらマックス値に戻す
		else if (m_nRamNum < VTXBUFFER_ZERO)
		{
			m_nRamNum = VTXBUFFER_THRD;
		}

		// 選択された時の処理
		switch (m_nRamNum)
		{
		// 頂点が0だった時
		case VTXBUFFER_ZERO:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// 頂点が1だった時
		case VTXBUFFER_FAST:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// 頂点が2だった時
		case VTXBUFFER_SECOND:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// 頂点が3だった時
		case VTXBUFFER_THRD:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// それ以外のとき
		default:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;
		}
		m_nRamNum++;
	}
}