//----------------------------------
//ポリゴンの処理
//----------------------------------
#ifndef _CAMERA_H
#define _CAMERA_H
#include "main.h"
#include "scene.h"
#include "texture.h"
class CPlayer;
//------------------------------------------------------------------------------
//クラスの定義
//------------------------------------------------------------------------------
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCamera(void);
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetPlayerCamera(CPlayer *pPlayer);
private:
	D3DXVECTOR3 m_posV;//現在の視点
	D3DXVECTOR3 m_posR;//現在の注視点
	D3DXVECTOR3 m_vecU;//上方向ベクトル
	D3DXVECTOR3 m_rot;//カメラの向き
	float m_fLong;//長さ
	D3DXMATRIX m_mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;//ビューマトリックス
	POINT m_Cursol;

};


#endif // !_CAMERA_H
#pragma once
