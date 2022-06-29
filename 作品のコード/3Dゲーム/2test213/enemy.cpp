//=============================================================================
//
// 敵の処理 [player2.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"enemy.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"model.h"
#include"shadow.h"
#include"title.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CShadow* CEnemy::m_pShadow = NULL;
CModel *CEnemy::m_pModel[20] = {};						// モデルのポインターの生成

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority) :CScene(PRIORITY_ENEMY)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumKey = 0;
}


//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 敵の生成処理
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos,const char *pFileName)
{
	// 敵のポインター生成
	CEnemy* pEnemy = NULL;

	// 動的メモリの確保
	pEnemy = new CEnemy;

	//　NULLチェック
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, pFileName);
	}
	return pEnemy;
}

//=============================================================================
// 敵のデフォルト初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	return S_OK;
}	// ポリゴンの初期化処理終了

//=============================================================================
// 敵のオーバーロードした初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, const char *pFileName)
{
	// 敵のデフォルト初期化処理の呼び出し
	Init(pos);

	// 敵のモデル読み込み処理の呼び出し
	LoadEnemy(pFileName);
	return S_OK;
}

//=============================================================================
// 敵の終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// m_nModel分回す
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		// NULLチェック
		if (m_pModel[nCntParts] != NULL)
		{
			// テクスチャの以外を破棄させる
			m_pModel[nCntParts]->ReleaseModel();
			m_pModel[nCntParts] = NULL;
		}
	}

	// NULLチェック
	if (m_pShadow != NULL)
	{
		// 影の終了処理の呼び出し
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// 解放処理
	Release();

}// 敵の終了処理終了


 //=============================================================================
 // 敵の更新処理
 //=============================================================================
void CEnemy::Update(void)
{
}// 敵の更新処理終了



 //=============================================================================
 // 敵の描画処理
 //=============================================================================
void CEnemy::Draw(void)
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
		
	//モデル生成
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		// NULLチェック
		if (m_pModel[nCntParts] != NULL)
		{
			// 描画処理の呼び出し
			m_pModel[nCntParts]->Draw();
		}
	}
	

}// ポリゴンの描画処理終了

 //=============================================================================
 // 敵のモデル読み込み処理
 //=============================================================================
void CEnemy::LoadEnemy(const char *pFileName)
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
// 敵のモデル読み込み処理
//=============================================================================
D3DXVECTOR3 CEnemy::GetSize(void)
{
	m_Size = m_pModel[0]->GetSize();

	return m_Size;
}
