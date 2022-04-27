//----------------------------------
//モデルの処理
//作成者：林　海斗
//----------------------------------
#ifndef _STAGE_TOTAL_MODEL_H
#define _STAGE_TOTAL_MODEL_H
#include "main.h"
#include "scene.h"
#include "texture.h"
#define MAX_STAGE_TOTAL_MODEL_TEX (10)
#define MAX_STAGE_TOTAL_MODEL_VTX (8)						//モデルの頂点数

//------------------------------------------------------------------------------
//クラスの定義
//------------------------------------------------------------------------------
class CStage_Total_Model
{
public:
	typedef struct
	{
		D3DXVECTOR3 vtx, rot;
		D3DXMATRIX mtxWorld;							//ワールドマトリックス
	}ModelVtx;//モデルの各頂点の保存用構造体

	CStage_Total_Model();
	~CStage_Total_Model();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadX(const char *sModelFailName);
private:

	LPD3DXMESH				m_pMesh;						//メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;						//マテリアル（材質情報）へのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture[MAX_STAGE_TOTAL_MODEL_TEX];		//テクスチャ
	DWORD					m_nNumMat;						//マテリアルの数
	D3DXVECTOR3				m_pos, m_layerpos, m_scale;				//モデルの位置（オフセット）
	D3DXVECTOR3				m_rot, m_layerrot;				//向き
	ModelVtx				m_vtx[MAX_STAGE_TOTAL_MODEL_VTX];			//各頂点の情報格納構造体
	D3DXVECTOR3				m_vtxMin, m_vtxMax;				//モデルの最小値、最大値
	D3DXMATRIX				m_mtxWorld;						//ワールドマトリックス
	D3DXMATERIAL			*m_pMat;						//マテリアルへのポインタ
	D3DXMATERIAL			*m_pSaveMat;					//マテリアルへのポインタのセーブ
	DWORD					m_sizeFVF;						//頂点フォーマットのサイズ
	BYTE					*m_pVtxBuff;					//頂点バッファのポインタ
	int						m_nNumVtx;						//頂点の数
	int						m_nNumParent;					//現在の親モデルの番号
	CStage_Total_Model					*m_pParent;						//親モデルのポインタ
	char					m_sFailName[256];
	bool					m_bDraw;						//描画するか
};


#endif // !_STAGE_TOTAL_MODEL_H
