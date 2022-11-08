///=============================================================================
//
// ステージ処理 [bg.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"stage.h"
#include"block.h"
#include"moveblock.h"
#include"stage_top.h"
#include"stage_tutorial.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
CBlock* CStage::m_pBlock[256] = {};

//=============================================================================
// ステージのコンストラクタ
//=============================================================================
CStage::CStage(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_nNum = 0;
}

//=============================================================================
// ステージのデストラクタ
//=============================================================================
CStage::~CStage()
{

}

//=============================================================================
// ステージの生成処理
//=============================================================================																				
CStage *CStage::Create(STAGE stage, D3DXVECTOR3 pos, const char * pStageFileNamee)
{
	// ステージトップのポインター生成
	CStage* pStage = NULL;


	switch (stage)
	{
	case STAGE_TOP:
		pStage = new CStage_Top;
		break;

	case STAGE_TUTORIAL:
		pStage = new CStage_Tutorial;
		break;

	default:
		break;
	}
	pStage->LodeStage(pStageFileNamee);
	pStage->Init(pos);

	return pStage;
}

//=============================================================================
// ステージの初期化処理
//=============================================================================
HRESULT CStage::Init(D3DXVECTOR3 pos)
{
	for (int nCntY = 0; nCntY < m_nColumn; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_nLine; nCntX++)
		{
			if (m_aMap[nCntY][nCntX] == 1)
			{
				// 普通のブロックの生成
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(20, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_NOME, 0, 0, 0, false, 7);
				m_nNum++;
			}

			if (m_aMap[nCntY][nCntX] == 2)
			{
				// 壊れるのブロックの生成
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(20, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_NOME, 0, 0, 0, true, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 3)
			{
				// 横移動ブロックの生成
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(30 + 60 * nCntX, 0 + 60 * nCntY, 0), D3DXVECTOR2(30, 60), D3DXVECTOR3(1.0f, 1.0f, 0.0f),
					CBlock::BLOCKTYPE_MOVEING, CMoveBlock::MOVE_LEFT, 600, 800, false, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 4)
			{
				// 縦移動ブロックの生成
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(60, 30), D3DXVECTOR3(0.0f, 1.0f, 0.0f),
					CBlock::BLOCKTYPE_MOVEING, CMoveBlock::MOVE_UP, 100, 300, false, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 5)
			{
				// 押されるブロックの生成
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, 60 * nCntY, 0), D3DXVECTOR2(30, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_PUSH, 0, 600, 800, false, 7);
				m_nNum++;
			}
		}
	}

	return S_OK;
}


//=============================================================================
// ステージの終了処理
//=============================================================================
void CStage::Uninit(void)
{
	// 解放処理
	Release();
}

//=============================================================================
// ステージの更新処理
//=============================================================================
void CStage::Update(void)
{

}

//=============================================================================
// ステージの描画処理
//=============================================================================
void CStage::Draw(void)
{

}

//=============================================================================
// ステージの描画処理
//=============================================================================
void CStage::LodeStage(const char * pStageFileName)
{
	// 開け～ファイル！
	FILE *pFile = fopen(pStageFileName, "r");

	// ファイルがあったら
	if (pFile != NULL)
	{
		int nCntX = 0, nCntY = 0;
		char aLine[128];
		//char *fgets(char *s, int n, FILE *fp); nは最大数で(n-1)される-1の数値はNULL(\0)が含まれるため
		while (fgets(aLine, sizeof(aLine), pFile) != NULL)
		{
			nCntX = 0;
			// 特定のトークン[,.]などで区切る
			char *pKanma = strtok(aLine, ",");
			while (pKanma != NULL)
			{
				// 文字列をint型に変換
				int nNum = atoi(pKanma);

				// int型に変換したものをaMapDataに代入
				m_aMap[nCntY][nCntX] = nNum;

				// 特定のトークン[,.]などを見つけた所にNULLを入れる
				pKanma = strtok(NULL, ","); // [,]を見つけたらNULLを入れてください
				nCntX++;
			}
			m_nLine = nCntX;
			nCntY++;
		}
		m_nColumn = nCntY;
	}
	fclose(pFile);
}
