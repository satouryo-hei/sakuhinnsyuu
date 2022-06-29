//=============================================================================
//
// テクスチャの処理 [texture.h]
// Author : 佐藤瞭平
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
int CTexture::m_nMaxTex = 0;
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[MAX_TEXTURE] = {};
const char * CTexture::m_pTexFileName = "data/TEXT/TextureFile.txt";

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの初期化処理
//=============================================================================
HRESULT CTexture::Init(void)
{
	Lode();
	return S_OK;
}

//=============================================================================
// テクスチャの終了処理
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nMaxTex; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
void CTexture::Lode(void)
{
	// マネージャークラスのポインターを生成
//	CManager * pManager = NULL;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	char aFile[256] = {};
	int nCnt = 0;

	FILE *pFile = fopen(m_pTexFileName, "r");

	if (pFile != NULL)//一度ファイルを読み込んで必要な情報を抜く
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTUREの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxTex);
			}

			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAMEの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				// テクスチャの設定
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_pTexture[nCnt]);				
				nCnt++;
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPTの文字列を見つけたら
			{
				break;
			}
		}
	}
	fclose(pFile);
}