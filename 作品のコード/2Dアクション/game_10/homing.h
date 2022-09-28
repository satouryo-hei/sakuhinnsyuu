//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _HOMING_H_
#define _HOMING_H_

#include"scene2D.h"

//*****************************************************************************
// 弾のクラス
//*****************************************************************************
class CHoming : public CScene2D
{
public:																															// 誰でもアクセス可能
	CHoming(int nPriority = PRIORITY_SECOND);																					// コンストラクタ
	~CHoming();																													// デストラクタ
																																// メンバ関数
	static CHoming *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, D3DXVECTOR2 lastPoint,int nAttack);				// 弾の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);																			// 弾の初期化関数
	void Uninit(void);																											// 弾の終了関数
	void Update(void);																											// 弾の更新関数
	void Draw(void);																											// 弾の描画関数
	bool GetUse(void) { return m_bUse; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	D3DXVECTOR3 SetCurve();//(BezierCurve)ベジェ曲線																			// 弾のベジェ曲線の計算関数
private:																														// 自分だけがアクセス可能	

	typedef struct
	{		
		int nCounter;//ベジェ曲線用	
		int nDivNum;//ベジェ曲線用
		double dPoint0[2];// 始点
		double dPoint1[2];// 制御点
		double dPoint2[2];// 制御点		
		double dPoint3[2];// 終点				
	}homing;

	homing m_Homing;

	static LPDIRECT3DTEXTURE9 m_pTexture;										// 共有するテスクチャのポインタ
	bool m_bUse;															// 使っているかどうか
	D3DXVECTOR3 m_Pos;															// 弾の現在地
	D3DXVECTOR3 m_Move;															// 弾の移動量
	D3DXVECTOR2 m_Size;															// 弾の大きさ
	int m_nPriority;															// 描画順
	int m_nLife;																// 弾の体力
	int m_nAttack;																// 弾の攻撃
};
#endif