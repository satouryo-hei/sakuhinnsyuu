//=============================================================================
//
// エフェクトの管理型の処理 [effect_manager.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EFFECT_MANAGER_H_//endifとセット（必ず一番上
#define _EFFECT_MANAGER_H_

#include"billeffect.h"
#include "texture.h"

#define EFFECTTEXT "data/TEXT/3DEffect.txt"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CStraight_Effect;		// 真っすぐのエフェクト
class CCircle_Effect;		// 円形のエフェクト
class CExplosion_Effect;	// 爆発のエフェクト
class CDome_Effect;			// ドーム型のエフェクト
class CWater_Crest_Effect;	// 水紋みたいなのエフェクト
class CSmoke_Effect;		// 煙のエフェクト
class CLanding_Effect;		// 着地のエフェクト

//*****************************************************************************
// エフェクトの管理型クラス
//*****************************************************************************
class CEffect_Manager : public CBilleffect
{
public:										// 誰でもアクセス可能

	//-----------------------------------------------------------------------------
	// エフェクトの種類
	//-----------------------------------------------------------------------------
	typedef enum
	{
		EffectType_NOMAL = 0,			// なし
		EffectType_STRAIGHT,			// 真っすぐ
		EffectType_CIRCLE,				// 円形
		EffectType_EXPLOSIN,			// 爆発
		EffectType_DOME,				// ドーム型
		EffectType_WATER_CREST,			// 水紋のような
		EffectType_SMOKE,				// 煙
		EffectType_LANDING,				// 着地
		EffectType_MAX					// 最大数
	} EffectType;

	//-----------------------------------------------------------------------------
	//色の種類
	//-----------------------------------------------------------------------------
	typedef enum
	{
		ColorType_RED = 0,				// 赤
		ColorType_GREEN,				// 緑
		ColorType_BLUE,					// 青
		ColorType_ARUFA,				// 透明度
		ColorType_MAX					// 最大数
	} ColorType;

	//-----------------------------------------------------------------------------
	//ベクトル3の中身の種類(pos,sizeなど)
	//-----------------------------------------------------------------------------
	typedef enum
	{
		Vector_X = 0,					// X
		Vector_Y,						// Y
		Vector_Z,						// Z
		Vector_MAX						// 最大数
	} Vector3;


	CEffect_Manager(PRIORITY nPriority);									  // コンストラクタ
	~CEffect_Manager();														  // デストラクタ
																			  
	// プロトタイプ宣言
	static CEffect_Manager *Create(EffectType EffectType);					  // 生成
	HRESULT Init(EffectType EffectType);									  // 初期化
	void Uninit(void);														  // 終了
	void Update(void);														  // 更新
	void Draw(void);														  // 描画
	D3DXVECTOR3 GetPos(void) { return m_pos; }								  // 位置の取得
	D3DXVECTOR3 GetMove(void) { return m_move; }							  // 移動量の取得
	D3DXVECTOR3 GetAddMove(void) { return m_Addmove; }						  // 計算する移動量の取得
	D3DXVECTOR3 GetSize(void) { return m_size; }							  // 大きさの取得
	D3DXVECTOR3 GetAddSize(void) { return m_AddSize; }						  // 計算する大きさの取得
	D3DXCOLOR GetCol(void) { return m_col; }								  // 色の取得
	D3DXCOLOR GetAddCol(void) { return m_AddColor; }						  // 計算する色の取得
	int GetLife(void) { return m_nLife; }									  // 寿命の取得
	int GetDensity(void) { return m_nDensity; }								  // 密度の取得
	int GetRadius(void) { return m_nRadius; }								  // 半径の取得
	int GetEffectType(void) { return m_nEffectType; }						  // エフェクトの種類を取得
	int GetColorType(void) { return m_nColorType; }							  // 色の種類を取得
	int GetVectorType(void) { return m_nVecType; }							  // ベクトルの種類を取得

private:									// 自分だけがアクセス可能
	inline void Reset(void);
	inline void Save(void);
	inline void Lode(void);

	//メンバ変数
	D3DXVECTOR3 m_pos;						// 現在の位置
	D3DXVECTOR3 m_rot;						// 回転量
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_Addmove;					// 計算する移動量
	D3DXVECTOR3 m_size;						// 大きさ
	D3DXVECTOR3 m_AddSize;					// 計算する大きさ
	D3DXCOLOR m_col;						// 色
	D3DXCOLOR m_AddColor;					// 計算する色
	int m_nLife;							// 寿命
	int m_nDensity;							// 密度
	int m_nRadius;							// 半径
	int m_nEffectType;						// エフェクトの種類
	int m_nColorType;						// 色の種類
	int m_nVecType;							// 位置や大きさなどの種類
	bool m_bColorTrigger;					// 色の増減をトリガーにするかどうか
	bool m_bVecTrigger;						// 位置や大きさなどの増減をトリガーにするかどうか
	bool m_bEffectTrigger;
	const float m_fMaxSize;					// 大きさの最大値
	const float m_fMaxAddSize;				// 計算する大きさの最大値

	//-----------------------------------------------------------------------------
	// 静的メンバ変数
	//-----------------------------------------------------------------------------
	static CStraight_Effect		*	m_pStraight_Effect;
	static CCircle_Effect		*	m_pCircle_Effect;
	static CExplosion_Effect	*	m_pExplosion_Effect;
	static CDome_Effect			*	m_pDome_Effect;
	static CWater_Crest_Effect	*	m_pWater_Crest_Effect;
	static CSmoke_Effect		*	m_pSmoke_Effect;
	static CLanding_Effect		*	m_pLanding_Effect;

};
#endif // !_EFFECT_MANAGER_H_