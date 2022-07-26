//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _CAMERA_H_//endifとセット（必ず一番上
#define _CAMERA_H_

#include"main.h"

//*****************************************************************************
// カメラクラス
//*****************************************************************************
class CCamera
{
public:													// 誰でもアクセス可能
	CCamera();											// コンストラクタ
	~CCamera();											// デストラクタ

	HRESULT Init(void);									// 初期化関数
	void Uninit(void);									// 終了関数
	void Update(void);									// 更新関数
	void SetCamera(void);								// カメラの設定関数
	D3DXVECTOR3 GetPosV(void) { return m_posV; }		// 現在の視点の取得
	D3DXVECTOR3 GetPosR(void) { return m_posR; }		// 現在の注視点の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// 注視点までの距離の取得

private:												// 自分だけがアクセス可能
	D3DXMATRIX m_mtxProjection;							//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;								//ビューマトリックス
	D3DVIEWPORT9 m_viewport;							//ビューボート
	D3DXVECTOR3 m_posV;									//現在の視点
	D3DXVECTOR3 m_posVDest;								//目的の視点
	D3DXVECTOR3	m_posR;									//現在の注視点
	D3DXVECTOR3 m_posRDest;								//目的の注視点
	D3DXVECTOR3 m_vecU;									//上方向のベクトル
	D3DXVECTOR3 m_rot;									//カメラの向き
	float m_Range;										//注視点までの距離
};
#endif //_LIGHT_H_//ifndefとセット（必ず一番下