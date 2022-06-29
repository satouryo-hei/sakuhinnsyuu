//=============================================================================
//
// プレイヤーの処理 [player2.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"player.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"model.h"
#include"shadow.h"
#include"choose_game.h"
#include"bullet.h"
#include"camera.h"
#include"status_ui.h"
#include"bom.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CShadow* CPlayer::m_pShadow = NULL;
const char* CPlayer::m_pModelBom = "data/MODEL/bom.x";

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) :CScene(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(&m_pModel,NULL,sizeof(m_pModel));
	m_nNumKey = 0;
	m_nAttack = 0;
	m_nItem = 0;
}


//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// プレイヤーのポインター生成
	CPlayer* pPlayer = NULL;

	// 動的メモリの確保
	pPlayer = new CPlayer;

	// NULLチェック
	if (pPlayer != NULL)
	{
		// 初期化処理
		pPlayer->Init(pos);
		// 移動量の設定
		pPlayer->m_move = move;
	}
	return pPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// プレイヤーの読み込み処理
	LoadPlayer(PLAYER_TEXT);

	// 新しくゲームを始めたかどうかの取得処理
	bool bNewGame = CChoose_Game::GetNewGame();

	// 新しくゲームを始めて無かったら
	if (!bNewGame)
	{
		LoadStatas(STATUS_TEXT);
	}
	// 新しく始めていたら
	else
	{
		m_nAttack = 1;
	}
	// 影の生成処理
	m_pShadow = CShadow::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// ステータスの書き込み
	SaveStatas(STATUS_TEXT);

	// m_nModel分回す
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		// NULLチェック
		if (m_pModel[nCntParts] != NULL)
		{
			// 終了処理の呼び出し
			m_pModel[nCntParts]->Uninit();
			m_pModel[nCntParts] = NULL;
		}
	}

	// NULLチェック
	if (m_pShadow != NULL)
	{
		// 終了処理の呼び出し
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// 解放処理
	Release();

}// ポリゴンの終了処理終了


//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボードのポインターを生成
	CInputKeyboard *pInputKeyboard = NULL;

	// マネージャーからキーボードの情報を取得
	pInputKeyboard = CManager::GetInputKeyboard();

	// ステータスUIのポインターを生成、取得
	CStatus_UI * pStatus_UI = new CStatus_UI;

	// カメラの向きを取得
	D3DXVECTOR3 CameraRot = CManager::GetCamera()->GetRot();

	//任意で押されたかどうか
	if (pInputKeyboard->GetPress(DIK_A) == true)//左を押した
	{
		//任意で押されたかどうか
		if (pInputKeyboard->GetPress(DIK_W) == true)//左を押した
		{
			m_pos.z += m_move.z;
			m_pos.x -= m_move.x;
			m_rot.y = (D3DX_PI / 2) + (D3DX_PI / 4);

			//m_rot.y = CameraRot.y;
			//m_pos.x += sinf(m_rot.y)*m_move.x;
			//m_pos.z += cosf(m_rot.y)*m_move.z;
			//m_pos.x -= cosf(m_rot.y)*m_move.x;
			//m_pos.z += sinf(m_rot.y)*m_move.z;
		}
		//任意で押されたかどうか
		else if (pInputKeyboard->GetPress(DIK_S) == true)//左を押した
		{
			m_pos.z -= m_move.z;
			m_pos.x -= m_move.x;
			m_rot.y = (D3DX_PI / 4);
		}
		// プラスで何も押されなかったら
		else
		{
			m_pos.x -= m_move.x;
			m_rot.y = (D3DX_PI / 2);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)//左を押した
	{
		//任意で押されたかどうか
		if (pInputKeyboard->GetPress(DIK_W) == true)//左を押した
		{
			m_pos.z += m_move.z;
			m_pos.x += m_move.x;
			m_rot.y = -((D3DX_PI / 2) + (D3DX_PI / 4));
		}
		//任意で押されたかどうか
		else if (pInputKeyboard->GetPress(DIK_S) == true)//左を押した
		{
			m_pos.z -= m_move.z;
			m_pos.x += m_move.x;
			m_rot.y = -(D3DX_PI / 4);
		}
		// プラスで何も押されなかったら
		else
		{
			m_pos.x += m_move.x;
			m_rot.y = -(D3DX_PI / 2);
		}
	}
	//任意で押されたかどうか
	else if (pInputKeyboard->GetPress(DIK_W) == true)//左を押した
	{
		m_pos.z += m_move.z;
		m_rot.y = D3DX_PI;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)//左を押した
	{
		m_pos.z -= m_move.z;
		m_rot.y = 0;
	}

	//任意で押されたかどうか
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)//左を押した
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), D3DXVECTOR2(20, 20), 60);
	}

	// アイテム数が3つ以上だったら
	if (m_nItem >= 3)
	{
		if (pInputKeyboard->GetTrigger(DIK_B) == true)//左を押した
		{
			// ボムの生成
			CBom::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelBom);

			// 3つ消費する
			m_nItem -= 3;

			// もしも0よりも小さくなってしまったら
			if (m_nItem < 0)
			{
				m_nItem = 0;
			}
		}
	}
	// 影の現在の位置の更新
	m_pShadow->SetPosition(m_pos);

	// 今の攻撃力の更新
	pStatus_UI->SetStatusNumber(m_nAttack);

}// ポリゴンの更新処理終了



//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス
	//各パーツのワールドマトリックスの初期化gtryg
	D3DXMatrixIdentity(&m_mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
	//位置を反映
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//各パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//CModel::SetMtx(m_mtxWorld);
	//モデル生成
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		m_pModel[nCntParts]->Draw();
	}

}// ポリゴンの描画処理終了

//=============================================================================
// プレイヤーの読み込み処理
//=============================================================================
void CPlayer::LoadPlayer(const char *pFileName)
{
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	FILE *pFile = fopen(pFileName, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[128] = {};								// 読み込んだファイルのデータ変数
	char aFileName[10][128] = {};						// 読み込んだファイルのデータを一時的に保存用変数
	int nCntModelFile = 0;								// 読み込んだモデルのファイルを数える変数
	int nIndex = 0;										// 読み込んだモデルが何番目かを教える変数
	int nParent = 0;									// 親のモデルが何番目かを教える変数
	bool bChara = false;								// キャラクターの読み込みをさせるかどうか変数
	bool bPatu = false;									// パーツの読み込みをさせるかどうかの変数
	int nCntModel = 0;									// モデルの生成時に読み込んだファイルを順番に生成させていく変数
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0]);													// 1列を読み込み(2行目以降は上書きされる)

			if (strcmp(&aFile[0], "NUM_MODEL") == 0)										// NUM_MODELが見つかったら
			{
				fscanf(pFile, "%s%d", &aFile[0], &m_nModel);								// モデルの数を読み込む
			}

			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)									// MODEL_FILENAMEが見つかったら
			{
				fscanf(pFile, "%s%s", &aFile[0], &aFileName[nCntModelFile]);				// モデルファイル名を読み込む
				nCntModelFile++;
			}

			if (strcmp(&aFile[0], "CHARACTERSET") == 0)										// CHARACTERSETが見つかったら
			{
				bChara = true;
			}
			else if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)							// END_CHARACTERSETが見つかったら
			{
				bChara = false;
			}

			if (bChara)
			{
				if (strcmp(&aFile[0], "PARTSSET") == 0)										// PARTSSETが見つかったら
				{
					bPatu = true;
				}
				else if (strcmp(&aFile[0], "END_PARTSSET") == 0)							// END_PARTSSETが見つかったら
				{
					m_pModel[nIndex] = CModel::Create(pos, rot, &aFileName[nCntModel][0]);	// モデルの生成

					if (nParent != -1)														// 親のモデルがあったら
					{
						m_pModel[nIndex]->SetParent(m_pModel[nParent]);
					}
					else
					{
						m_pModel[nIndex]->SetParent(NULL);
					}
					nCntModel++;
					bPatu = false;
				}

				if (bPatu)
				{
					if (strcmp(&aFile[0], "INDEX") == 0)								//モデルファイル読み込みの時の、何番目のモデルを呼び出すか
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
					}
					else if (strcmp(&aFile[0], "PARENT") == 0)							//親モデル
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);
					}
					else if (strcmp(&aFile[0], "POS") == 0)								// POSが見つかったら
					{
						fscanf(pFile, "%s%f%f%f", &aFile[0], &pos.x, &pos.y, &pos.z);	// 現在の位置を読み込む
					}
					else if (strcmp(&aFile[0], "ROT") == 0)								// ROTが見つかったら
					{
						fscanf(pFile, "%s%f%f%f", &aFile[0], &rot.x, &rot.y, &rot.z);	// 現在の回転量を読み込む
					}
				}
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0)									// END_SCRIPTが見つかったら
			{
				break;																	// 無限ループを抜ける
			}
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);

}

//=============================================================================
// プレイヤーのステータスを書き込み処理
//=============================================================================
void CPlayer::SaveStatas(const char *pStatasFile)
{
	// 開け～ファイル！
	FILE *pFile = fopen(pStatasFile, "w");

	// ファイルがあったら
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# プレイヤーのステータス設定ファイル[Setui.txt]\n");
		fprintf(pFile, "# Author : 佐藤瞭平\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT\t\t# この行は絶対消さないこと！\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# プレイヤーのステータス情報\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SETSTATUS\n");
		fprintf(pFile, "\tATTACK = %d\n", m_nAttack);
		fprintf(pFile, "END_SETSTATUS\n\n");

		fprintf(pFile, "END_SCRIPT\t\t# この行は絶対消さないこと！\n");
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}
	// 閉じれ～ファイル！
	fclose(pFile);
}

//=============================================================================
// プレイヤーのステータスを読み込み処理
//=============================================================================
void CPlayer::LoadStatas(const char *pStatasFile)
{
	// 開け～ファイル！
	FILE *pFile = fopen(pStatasFile, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1列を読み込み(2行目以降は上書きされる)

			while (strcmp(&aFile[0][0], "SETSTATUS") == 0)							// SETSTATUSが見つかったら
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1列を読み込み(2行目以降は上書きされる)
				if (strcmp(&aFile[1][0], "ATTACK") == 0)							// ATTACKが見つかったら
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nAttack);	// 現在の位置を読み込む
				}
				else if (strcmp(&aFile[1][0], "END_SETSTATUS") == 0)					// END_SETUIが見つかったら
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