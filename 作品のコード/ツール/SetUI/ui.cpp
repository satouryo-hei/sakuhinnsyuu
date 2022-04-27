//=============================================================================
//
// UIの処理 [ui.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "ui.h"
#include"input.h"
#include"manager.h"

/*
できればimgui(いむぐい)化したい
*/

//=============================================================================
// UIのコンストラクタ
//=============================================================================
CUi::CUi() : MaxSpeed(50.0f), MinSpeed(1.0f)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Speed = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_col = D3DXCOLOR(255, 255, 255, 255);
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
	CUi *pUi = NULL;
	pUi = new CUi;

	// NULLチェック
	if (pUi != NULL)
	{
		pUi->Init(pos, move, Size, nType);
	}
	return pUi;
}

//=============================================================================
// UIの初期化処理
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nType)
{
	CScene2D::Init(pos, move, Size);
	CScene2D::BindTextuer(nType);
	m_Pos = pos;
	m_Move = move;
	m_Size = Size;
	m_pInputKeyboard = CManager::GetInputKeyboard();
	LodeAnim();
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

		// 速さを変更させるかどうか
		ChangeSpeedUI();

		// 速さを変更させるかどうか
		ChangeAnimeUI();

		// Xを押したら
		if (m_pInputKeyboard->GetTrigger(DIK_X) == true)
		{
			m_Move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		}

		// SPACEを押したら
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			m_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			m_Size = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
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
				m_Pos.x += sinf(D3DX_PI*-0.75f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*-0.75f)*(m_Move.y*0.7f);
			}
			//AとSを押したら
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//左下に移動
				m_Pos.x += sinf(D3DX_PI*-0.25f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*-0.25f)*(m_Move.y*0.7f);
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
				m_Pos.x += sinf(D3DX_PI*0.75f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*0.75f)*(m_Move.y*0.7f);
			}
			//DとWを押したら
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//右下に移動
				m_Pos.x += sinf(D3DX_PI*0.25f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*0.25f)*(m_Move.y*0.7f);
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
// UIの移動量の制御処理
//=============================================================================
void CUi::ChangeSpeedUI(void)
{
	// 速さを変更させるかどうか
	if (m_bSpeed)
	{
		//===============================
		// 移動量の変更
		//===============================
		// Fを押したら
		if (m_pInputKeyboard->GetPress(DIK_F) == true)
		{
			m_Move.x += m_Speed.x;
		}
		// Hを押したら
		else if (m_pInputKeyboard->GetPress(DIK_H) == true)
		{
			m_Move.x -= m_Speed.x;
		}
		// Tを押したら
		if (m_pInputKeyboard->GetPress(DIK_T) == true)
		{
			m_Move.y += m_Speed.y;
		}
		// Gを押したら
		else if (m_pInputKeyboard->GetPress(DIK_G) == true)
		{
			m_Move.y -= m_Speed.y;
		}

		//===============================
		// 移動量の計算値の変更
		//===============================
		// Rを押したら
		if (m_pInputKeyboard->GetTrigger(DIK_R) == true)
		{
			m_Speed.x = 0.1f;
		}
		// Yを押したら
		else if (m_pInputKeyboard->GetTrigger(DIK_Y) == true)
		{
			m_Speed.y = 0.1f;
		}
		// Vを押したら
		if (m_pInputKeyboard->GetTrigger(DIK_V) == true)
		{
			m_Speed.x = 1.0f;
		}
		// Nを押したら
		else if (m_pInputKeyboard->GetTrigger(DIK_N) == true)
		{
			m_Speed.y = 1.0f;
		}

		//===============================
		// 速さの最小値の設定
		//===============================
		// 横の速さが最小値より小さくになったら
		if (m_Move.x < MinSpeed)
		{
			m_Move.x = MinSpeed;
		}
		// 縦の速さが最小値より小さくになったら
		else if (m_Move.y < MinSpeed)
		{
			m_Move.y = MinSpeed;
		}
		//===============================
		// 速さの最大値の設定
		//===============================
		// 横の速さが最大値より大きくになったら
		if (m_Move.x > MaxSpeed)
		{
			m_Move.x = MaxSpeed;
		}
		// 縦の速さが最大値より大きくになったら
		else if (m_Move.y > MaxSpeed)
		{
			m_Move.y = MaxSpeed;
		}
	}
}

//=============================================================================
// UIのテクスチャアニメーション処理
//=============================================================================
void CUi::ChangeAnimeUI(void)
{
	if (m_bAnim)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % m_nAnimeSpeed == 0)
		{
			m_nPatternAnim++;

			CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeAnimU, m_fMinSizeV, m_fMaxSizeV);

			if (m_nPatternAnim >= m_nMaxPatternAnim)
			{
				return;
			}
		}
	}
}

//=============================================================================
// UIのテクスチャアニメーション読み込み処理
//=============================================================================
void CUi::LodeAnim(void)
{
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	// 開け～ファイル！
	FILE *pFile = fopen("data/TEXT/AnimUI.txt", "r");

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1列を読み込み(2行目以降は上書きされる)

			while (strcmp(&aFile[0][0], "SETANIME") == 0)								// SETUIが見つかったら
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1列を読み込み(2行目以降は上書きされる)
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
				else if (strcmp(&aFile[1][0], "ANIMEMINSIZEV") == 0)							// ANIMEMINSIZEVが見つかったら
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMinSizeV);
				}
				else if (strcmp(&aFile[1][0], "ANIMEMAXSIZEV") == 0)							// ANIMEMAXSIZEVが見つかったら
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMaxSizeV);
				}
				else if (strcmp(&aFile[1][0], "END_SETANIME") == 0)					// END_SETUIが見つかったら
				{
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