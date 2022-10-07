//=============================================================================
//
// UIの処理 [ui.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "ui.h"
#include"input.h"
#include"manager.h"

//=============================================================================
// UIのコンストラクタ
//=============================================================================
CUi::CUi() : m_fMaxSpeed(50.0f), m_fMinSpeed(1.0f), m_fDiagonalSpeed(0.7f),m_fUpAngle(0.75f), m_fDownAngle(0.25f), m_ResetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)), m_ResetSize(D3DXVECTOR3(100.0f, 50.0f, 0.0f)), m_ResetMove(D3DXVECTOR3(10.0f, 10.0f, 0.0f)), m_nMaxSetTexNum(LIMITUI -1)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_col = D3DXCOLOR(255, 255, 255, 255);
	m_nTextureType = 0;
	m_pInputKeyboard = NULL;
	m_bUse = true;
	m_bMove = true;
	m_bSize = true;
	m_bSpeed = false;
}

//=============================================================================
// UIのデストラクタ
//=============================================================================
CUi::~CUi()
{

}

//=============================================================================
// UIの生成処理
//=============================================================================
CUi *CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nType)
{
	// UIのポインターを生成
	CUi *pUi = NULL;

	// 動的メモリの確保
	pUi = new CUi;

	// NULLチェック
	if (pUi != NULL)
	{
		// UIの初期化処理の呼び出し
		pUi->Init(pos, move, Size, nType);
	}
	return pUi;
}

//=============================================================================
// UIの初期化処理
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nType)
{
	// オブジェクト2D初期化処理の呼び出し
	CScene2D::Init(pos, move, Size);
	SetTex(nType);
	m_Pos = pos;
	m_Move = move;
	m_Size = Size;
	LodeAnim();
	m_pInputKeyboard = CManager::GetInputKeyboard();
	return S_OK;
}

//=============================================================================
// UIの終了処理
//=============================================================================
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// UIの更新処理
//=============================================================================
void CUi::Update(void)
{	
	if (m_bUse == true)
	{
		// 移動するかどうか
		ChangeMoveUI();		

		// 大きさの変更させるかどうか
		ChangeSizeUI();

		//===============================
		// 画面端との当たり判定
		//===============================
		if (m_Pos.x + m_Size.x >= SCREEN_WIDTH)
		{
			m_Pos.x = SCREEN_WIDTH - m_Size.x;
		}
		else if (m_Pos.x - m_Size.x <= 0)
		{
			m_Pos.x = m_Size.x;
		}
		if (m_Pos.y + m_Size.y >= SCREEN_HEIGHT)
		{
			m_Pos.y = SCREEN_HEIGHT - m_Size.y;
		}
		else if (m_Pos.y - m_Size.y <= 0)
		{
			m_Pos.y = m_Size.y;
		}
		// アニメーションにさせるかどうか
		ChangeAnimeUI();

		// Xを押したら
		if (m_pInputKeyboard->GetTrigger(DIK_X) == true)
		{
			m_Move = m_ResetMove;
		}

		// SPACEを押したら
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			m_Pos = m_ResetPos;
			m_Size = m_ResetSize;
		}

		CScene2D::SetPosition(m_Pos);
		CScene2D::SetSize(m_Size);
		CScene2D::SetColor(m_col);
		CScene2D::Update();
	}
}

//=============================================================================
// UIの描画処理
//=============================================================================
void CUi::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// UIの移動処理
//=============================================================================
void CUi::ChangeMoveUI(void)
{
	// 移動するかどうか
	if (m_bMove)// 移動するなら
	{
		//任意で押されたかどうか
		if (m_pInputKeyboard->GetPress(DIK_A) == true)//Aを押した
		{
			//AとWを押したら
			if (m_pInputKeyboard->GetPress(DIK_W) == true)
			{
				//左上に移動
				m_Pos.x += sinf(D3DX_PI*-m_fUpAngle)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*-m_fUpAngle)*(m_Move.y*m_fDiagonalSpeed);
			}
			//AとSを押したら
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//左下に移動
				m_Pos.x += sinf(D3DX_PI*-0.25f)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*-0.25f)*(m_Move.y*m_fDiagonalSpeed);
			}
			else //Aを押したら
			{
				//左に移動
				m_Pos.x -= m_Move.x;
			}						  
		}
		else if (m_pInputKeyboard->GetPress(DIK_D) == true)//Dを押した
		{
			//DとWを押したら
			if (m_pInputKeyboard->GetPress(DIK_W) == true)
			{
				//右上に移動
				m_Pos.x += sinf(D3DX_PI*m_fUpAngle)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*m_fUpAngle)*(m_Move.y*m_fDiagonalSpeed);
			}
			//DとWを押したら
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//右下に移動
				m_Pos.x += sinf(D3DX_PI*m_fDownAngle)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*m_fDownAngle)*(m_Move.y*m_fDiagonalSpeed);
			}
			else //Dを押したら
			{
				//右に移動
				m_Pos.x += m_Move.x;
			}
		}

		//Wを押したら
		if (m_pInputKeyboard->GetPress(DIK_W) == true)
		{
			//上に移動
			m_Pos.y -= m_Move.y;
		}
		//Sを押したら
		if (m_pInputKeyboard->GetPress(DIK_S) == true)
		{
			//下に移動
			m_Pos.y += m_Move.y;
		}
	}
	//===============================
	// 速さの最小値の設定
	//===============================
	// 横の速さが最小値より小さくになったら
	if (m_Move.x <= m_fMinSpeed)
	{
		m_Move.x = m_fMinSpeed;
	}
	// 縦の速さが最小値より小さくになったら
	else if (m_Move.y <= m_fMinSpeed)
	{
		m_Move.y = m_fMinSpeed;
	}
	//===============================
	// 速さの最大値の設定
	//===============================
	// 横の速さが最大値より大きくになったら
	if (m_Move.x >= m_fMaxSpeed)
	{
		m_Move.x = m_fMaxSpeed;
	}
	// 縦の速さが最大値より大きくになったら
	else if (m_Move.y >= m_fMaxSpeed)
	{
		m_Move.y = m_fMaxSpeed;
	}
}

//=============================================================================
// UIの大きさの変更処理
//=============================================================================
void CUi::ChangeSizeUI(void)
{
	// 大きさの変更させるかどうか
	if (m_bSize)
	{
		// 横の大きさを変更
		if (m_pInputKeyboard->GetPress(DIK_Q) == true)
		{
			// 横に大きくする
			m_Size.x++;
		}
		else if (m_pInputKeyboard->GetPress(DIK_E) == true)
		{
			// 横に小さくする
			m_Size.x--;
		}
		// 縦の大きさを変更			
		if (m_pInputKeyboard->GetPress(DIK_Z) == true)
		{
			// 縦に大きくする
			m_Size.y++;
		}
		else if (m_pInputKeyboard->GetPress(DIK_C) == true)
		{
			// 縦に小さくする
			m_Size.y--;
		}

		//===============================
		// 大きさの最小値の設定
		//===============================
		// 横の大きさが0以下になったら
		if (m_Size.x <= 0)
		{
			m_Size.x = 0;
		}
		// 縦の大きさが0以下になったら
		else if (m_Size.y <= 0)
		{
			m_Size.y = 0;
		}
		//===============================
		// 大きさの最大値の設定
		//===============================
		// 横の大きさが最大値になったら
		if (m_Size.x > SCREEN_WIDTH / 2)
		{
			m_Size.x = (SCREEN_WIDTH / 2);
		}
		// 縦の大きさが最大値になったら
		else if (m_Size.y > SCREEN_HEIGHT / 2)
		{
			m_Size.y = (SCREEN_HEIGHT / 2);
		}
	}
}

//=============================================================================
// UIのテクスチャアニメーション処理
//=============================================================================
void CUi::ChangeAnimeUI(void)
{
	// アニメーションさせるなら
	if (m_bAnim)
	{		
		// アニメーションのカウントを進める
		m_nCounterAnim++;

		// アニメーションのカウントがアニメーションの速さで割って余ったのが0だった時(割り切れた時)
		if (m_nCounterAnim % m_nAnimeSpeed == 0)
		{
			// アニメーションのパターン数を進める
			m_nPatternAnim++;

			// アニメーションのテクスチャ設定
			CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeAnimU, m_fMinSizeV, m_fMaxSizeV);

			// アニメーションのパターン数がパターンの最大数を超えたら
			if (m_nPatternAnim >= m_nMaxPatternAnim)
			{
				// アニメーションのパターン数の初期化
				m_nPatternAnim = 0;
				return;
			}
		}
	}
	else
	{
		// アニメーション後のテクスチャの割り当てを初期化する
		CScene2D::SetTex(0,1);
		m_nCounterAnim = 0;
		m_nPatternAnim = 0;
	}
}

//=============================================================================
// UIのテクスチャの設定処理
//=============================================================================
void CUi::SetTex(int nTex)
{
	// テクスチャタイプの数が最大値を超えたら
	if (nTex > m_nMaxSetTexNum)
	{
		// テクスチャタイプの数に最小値に代入
		nTex = 0;
	}
	// テクスチャタイプの数が最小値より下だったら
	else if (nTex < 0)
	{
		// テクスチャタイプの数に最大値に代入
		nTex = m_nMaxSetTexNum;
	}

	// テクスチャの設定処理
	BindTextuer(nTex);

	// 設定された数を格納
	m_nTextureType = nTex;
}

//=============================================================================
// UIのテクスチャアニメーション読み込み処理
//=============================================================================
void CUi::LodeAnim(void)
{
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[2][128] = {};
	char aName[128] = {};
	// 開け～ファイル！
	FILE *pFile = fopen("data/TEXT/AnimUI.txt", "r");

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);												// 1列を読み込み(2行目以降は上書きされる)

			while (strcmp(&aFile[0][0], "SETANIME") == 0)									// SETANIMEが見つかったら
			{
				fscanf(pFile, "%s", &aFile[1]);												// 1列を読み込み(2行目以降は上書きされる)
				if (strcmp(&aFile[1][0], "ANIMESPEED") == 0)								// ANIMESPEEDが見つかったら
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nAnimeSpeed);
				}
				else if (strcmp(&aFile[1][0], "ANIMEPATTERN") == 0)							// ANIMEPATTERNが見つかったら
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nMaxPatternAnim);
				}
				else if (strcmp(&aFile[1][0], "ANIMESIZEU") == 0)							// ANIMESIZEUが見つかったら
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fSizeAnimU);
				}
				else if (strcmp(&aFile[1][0], "ANIMEMINSIZEV") == 0)						// ANIMEMINSIZEVが見つかったら
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMinSizeV);
				}
				else if (strcmp(&aFile[1][0], "ANIMEMAXSIZEV") == 0)						// ANIMEMAXSIZEVが見つかったら
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMaxSizeV);
				}
				else if (strcmp(&aFile[1][0], "END_SETANIME") == 0)							// END_SETUIが見つかったら
				{
					break;																	// 無限ループを抜ける
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)									// END_SCRIPTが見つかったら
			{
				break;																		// 無限ループを抜ける
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

