//=============================================================================
//
// UIの処理 [ui.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include"scene2D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInputKeyboard;

//*****************************************************************************
// UIのクラス
//*****************************************************************************
class CUi : public CScene2D
{
public:																					// 誰でもアクセス可能
	CUi();																				// コンストラクタ
	~CUi();																				// デストラクタ
	// 静的メンバ関数
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int ntype);	// UIの生成
																						// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int ntype);		// UIの初期化関数
	void Uninit(void);																	// UIの終了関数
	void Update(void);																	// UIの更新関数
	void Draw(void);																	// UIの描画関数
	void ChangeMoveUI(void);															// UIの移動処理
	void ChangeSizeUI(void);															// UIの大きさ変更処理
	void ChangeSpeedUI(void);															// UIの移動量の制御処理
	void ChangeAnimeUI(void);															// UIのアニメーション処理
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }										// 位置の設定関数
	void SetSize(D3DXVECTOR3 size) { m_Size = size; }									// 大きさの設定関数
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }									// 移動量の設定関数
	void SetSpeed(D3DXVECTOR3 speed) { m_Speed = speed; }								// 速さの設定関数
	void SetCol(D3DXCOLOR col) { m_col = col; }											// 速さの設定関数
	D3DXVECTOR3 GetPos(void) { return m_Pos; }											// 位置の取得関数
	D3DXVECTOR3 GetSize(void) { return m_Size; }										// 大きさの取得関数
	D3DXVECTOR3 GetMove(void) { return m_Move; }										// 移動量の取得関数
	D3DXVECTOR3 GetSpeed(void) { return m_Speed; }										// 速さの取得関数
	D3DXCOLOR GetColor(void) { return m_col; }											// 色の取得関数
	
	void SetBoolUse(bool bUse) { m_bUse = bUse; }										// UIの使っているか関数
	void SetBoolMove(bool bMove) { m_bMove =bMove; }									// UIの移動するか関数
	void SetBoolSize(bool bSize) { m_bSize = bSize; }									// UIの大きさ変更するか取得関数
	void SetBoolSpeed(bool bSpeed) { m_bSpeed = bSpeed; }								// UIの速さ変更をするか取得関数
	void SetBoolAnim(bool bAnime) { m_bAnim = bAnime; }								// UIの速さ変更をするか取得関数
	bool GetBoolUse(void) { return m_bUse; }											// UIの使っているか取得関数
	bool GetBoolMove(void) { return m_bMove; }											// UIの移動するか取得関数
	bool GetBoolSize(void) { return m_bSize; }											// UIの大きさ変更するか取得関数
	bool GetBoolSpeed(void) { return m_bSpeed; }										// UIの速さ変更をするか取得関数
	bool GetBoolAnim(void) { return m_bAnim; }										// UIの速さ変更をするか取得関数

private:																				// 自分だけがアクセス可能
	inline void LodeAnim(void);

	// 静的メンバ変数
	const float MaxSpeed;																// 速さの最大値
	const float MinSpeed;																// 速さの最小値

	// メンバ変数
	D3DXVECTOR3 m_Pos;																	// 位置
	D3DXVECTOR3 m_Size;																	// 大きさ
	D3DXVECTOR3 m_Move;																	// 移動量
	D3DXVECTOR3 m_Speed;																// 速さ
	D3DXCOLOR m_col;																	// 色
	CInputKeyboard *m_pInputKeyboard;													// キーボード入力
	int m_nCounterAnim;																	// アニメーションのカウンター
	int m_nAnimeSpeed;																	// アニメーションのV座標の最大サイズ
	int m_nMaxPatternAnim;																// アニメーションのパターンの最大数
	int m_nPatternAnim;																	// アニメーションのパターン数
	float m_fSizeAnimU;																	// アニメーションのU座標
	float m_fMinSizeV;																	// アニメーションのV座標の最小サイズ
	float m_fMaxSizeV;																	// アニメーションのV座標の最大サイズ
	bool m_bUse;																		// 使用してるか
	bool m_bMove;																		// 移動するかどうか
	bool m_bSize;																		// 大きさを変更するかどうか
	bool m_bSpeed;																		// 速さを変更するかどうか
	bool m_bAnim;																		// アニメーションにするかどうか
};
#endif