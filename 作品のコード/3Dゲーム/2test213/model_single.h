//=============================================================================
//
// 単体のモデル処理 [model_single.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MODEL_SINGLE_H_//endifとセット（必ず一番上
#define _MODEL_SINGLE_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
// 単体のモデルクラス
//*****************************************************************************
class CModel_Single : public CScene
{
public:																							// 誰でもアクセス可能
	CModel_Single(PRIORITY Priority = PRIORITY_MODEL);											// コンストラクタ
	~CModel_Single();																			// デストラクタ
	// メンバ関数
	static CModel_Single *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata);		// 単体のモデルの生成
	HRESULT Init(D3DXVECTOR3 pos);																// 単体のモデルのデフォルト初期化関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata);				// 単体のモデルの初期化関数
	virtual void Uninit(void);																	// 単体のモデルの終了関数
	virtual void Update(void);																	// 単体のモデルの更新関数
	virtual void Draw(void);																	// 単体のモデルの描画関数
	void ReleaseSingle(void);																	// 単体のモデルの解放処理
	void SetPos(D3DXVECTOR3 pos);																// 単体のモデルの位置の設定処理
	void SetRot(D3DXVECTOR3 rot);																// 単体のモデルの向きの設定処理

private:																						// 自分だけがアクセス可能
	D3DXMATRIX m_mtxWorld;																		// ワールドマトリックス
	D3DXVECTOR3 m_Pos;																			// 単体のモデルの移動量
	D3DXVECTOR3 m_Size;																			// 単体のモデルの移動量
	D3DXVECTOR3 m_rot;																			// 向き
	CModel * m_pModel;																			// モデルのポインター生成
};
#endif // _POLYGON_H_//ifndefとセット（必ず一番下