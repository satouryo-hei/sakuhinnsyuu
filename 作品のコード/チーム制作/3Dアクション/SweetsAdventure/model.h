//----------------------------------
//モデルの処理
//作成者：林　海斗
//----------------------------------
#ifndef _MODEL_H
#define _MODEL_H
#include "main.h"
#include "scene.h"
#include "texture.h"
#define MAX_MODEL_TEX (10)
#define MAX_MODEL_VTX (8)						//モデルの頂点数

//------------------------------------------------------------------------------
//クラスの定義
//------------------------------------------------------------------------------
class CModel
{
public:
	typedef struct
	{
		D3DXVECTOR3 vtx, rot;
		D3DXMATRIX mtxWorld;							//ワールドマトリックス
	}ModelVtx;//モデルの各頂点の保存用構造体

	CModel();
	~CModel();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char *sModelFailName, D3DXVECTOR3 scale= D3DXVECTOR3(1.0f,1.0f,1.0f));//ファイルネームはファイルのパスを入れる
	void SetParent(CModel *pModel) {m_pParent = pModel;}//親のモデルを代入
	D3DXMATRIX GetMatrix(void) {return m_mtxWorld;}//ワールドマトリックスの取得
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetLayerPos(D3DXVECTOR3 pos) { m_layerpos = pos; }
	void SetLayerRot(D3DXVECTOR3 rot) { m_layerrot = rot; }
	D3DXVECTOR3 GetLayerPos(void) { return m_layerpos; }
	D3DXVECTOR3 GetLayerRot(void) { return m_layerrot; }
	void SetDiffuse(float DiffuseA);
	D3DXMATERIAL *GetMat(void) { return m_pSaveMat; }
	void SetNumParent(int Parent) { m_nNumParent = Parent; }
	int GetNumParent(void) { return m_nNumParent; }
	ModelVtx GetVtx(int nNumVtx) { return m_vtx[nNumVtx]; }//各モデルの頂点情報の取得
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }//ワールドマトリックスの取得
	D3DXVECTOR3 GetMaxPos(void) { return m_vtxMin; }
	D3DXVECTOR3 GetMinPos(void) { return m_vtxMax; }
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }
private:

	LPD3DXMESH				m_pMesh;						//メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;						//マテリアル（材質情報）へのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture[MAX_MODEL_TEX];		//テクスチャ
	DWORD					m_nNumMat;						//マテリアルの数
	D3DXVECTOR3				m_pos,m_layerpos,m_scale;				//モデルの位置（オフセット）
	D3DXVECTOR3				m_rot, m_layerrot;				//向き
	ModelVtx				m_vtx[MAX_MODEL_VTX];			//各頂点の情報格納構造体
	D3DXVECTOR3				m_vtxMin, m_vtxMax;				//モデルの最小値、最大値
	D3DXMATRIX				m_mtxWorld;						//ワールドマトリックス
	D3DXMATERIAL			*m_pMat;						//マテリアルへのポインタ
	D3DXMATERIAL			*m_pSaveMat;					//マテリアルへのポインタのセーブ
	DWORD					m_sizeFVF;						//頂点フォーマットのサイズ
	BYTE					*m_pVtxBuff;					//頂点バッファのポインタ
	int						m_nNumVtx;						//頂点の数
	int						m_nNumParent;					//現在の親モデルの番号
	CModel					*m_pParent;						//親モデルのポインタ
	char					m_sFailName[256];
	bool					m_bDraw;						//描画するか
};


#endif // !_MODEL_H
