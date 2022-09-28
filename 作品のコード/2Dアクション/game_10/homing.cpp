//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"homing.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"effect.h"

/*やりたいこと*/
/*弾の回転　←いるのか？
チャージショット
チャージショットで弾の拡大*/

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CHoming::m_pTexture = NULL;

//=============================================================================
// 弾のコンストラクタ
//=============================================================================
CHoming::CHoming(int nPriority) : CScene2D(PRIORITY_H_BULLET)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_bUse = false;
	memset(&m_Homing, 0, sizeof(m_Homing));
	m_nPriority = nPriority;

	m_nLife = 0;
}


//=============================================================================
// 弾のデストラクタ
//=============================================================================
CHoming::~CHoming()
{

}


//=============================================================================
// 弾の生成処理
//=============================================================================
CHoming *CHoming::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, D3DXVECTOR2 lastPoint, int nAttack)
{
	CHoming* pHoming = NULL;

	pHoming = new CHoming;

	if (pHoming != NULL)
	{
		pHoming->Init(pos, Size);
		pHoming->m_Move = move;
		pHoming->Bindtexture(6);
		pHoming->m_bUse = false;
		pHoming->m_Homing.dPoint3[0] = (int)lastPoint.x;
		pHoming->m_Homing.dPoint3[1] = (int)lastPoint.y;
	}

	return pHoming;
}

//=============================================================================
// 弾の初期化処理
//=============================================================================
HRESULT CHoming::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);

	m_nLife = 30;
	int nItem = CPlayer::GetItem();
	m_nLife += nItem;
	m_Pos = pos;
	m_Size = Size;	

	m_Homing.nCounter = 0;		
	m_Homing.nDivNum = 50;
	m_Homing.dPoint0[0] = m_Pos.x;
	m_Homing.dPoint0[1] = m_Pos.y;
	m_Homing.dPoint1[0] = rand() % 1280;
	m_Homing.dPoint1[1] = 640;
	m_Homing.dPoint2[0] = rand() % 640;
	m_Homing.dPoint2[1] = 120;
	
	return S_OK;
}	// ポリゴンの初期化処理終了



	//=============================================================================
	// 弾の終了処理
	//=============================================================================
void CHoming::Uninit(void)
{
	//CScene2D::Uninit();

	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // 弾の更新処理
 //=============================================================================
void CHoming::Update(void)
{

	if (m_bUse)
	{
		Uninit();
		return;
	}
	// 画面外処理
	if (m_Pos.x >= SCREEN_WIDTH - (m_Size.x / 2))
	{
		m_bUse = true;
	}
	else if (m_Pos.x <= (m_Size.x / 2))
	{
		m_bUse = true;
	}
	if (m_Pos.y >= SCREEN_HEIGHT - (m_Size.y / 2))
	{
		m_bUse = true;
	}
	else if (m_Pos.y <= (m_Size.y / 2))
	{
		m_bUse = true;
	}

	m_Pos = SetCurve();

	m_Homing.nCounter++;

	// もしカウンターが分割数に達していたら０に戻す
	if (m_Homing.nCounter == m_Homing.nDivNum)
	{
		m_Homing.nCounter = 0;
		m_bUse = true;
	}
	SetPosition(m_Pos);
	if (m_Homing.nCounter >= 2)
	{
		CEffect::Create(m_Pos, m_Size, D3DXVECTOR2(0.1f, 0.1f), D3DXCOLOR(10, 15, 40, 10),1);
	}


	CScene2D::Update();

}// ポリゴンの更新処理終了



 //=============================================================================
 // 弾の描画処理
 //=============================================================================
void CHoming::Draw(void)
{
	CScene2D::Draw();

}	// ポリゴンの描画処理終了


//=============================================================================
// 弾のベジェ曲線の計算処理
//=============================================================================
D3DXVECTOR3 CHoming::SetCurve(void)
{
	/*始点を入れくことで終点を返してポスに代入させる
 */
	double dNum = 0;

	// ベジェ曲線用の変数5つ
	double dPoint[2] = {};
	D3DXVECTOR2 Point0, Point1, Point2;

	// 中点用の変数を3つ
	double dPoint02[2], dPoint03[2], dPoint04[2];	

	// (1/分割数)/カウント数
	dNum = (1.0 / m_Homing.nDivNum) * m_Homing.nCounter;

	// 角ばってるところが2つあるから
	// 角ばってるところがあるから点を2点打つ

	// 2次元のベジェ曲線(制御点が1個)
	// dPoint10(角ばっているところの一か所目の点の１つ目(x座標)) = (1-分割数) * 始点(x座標) + 分割数 * 中点(x座標)
	dPoint[0] = (1.0 - dNum) * m_Homing.dPoint0[0] + dNum * m_Homing.dPoint1[0];
	// dPoint11(角ばっているところの一か所目の点の2つ目(y座標)) = (1-分割数) * 始点(y座標) + 分割数 * 中点(y座標)
	dPoint[1] = (1.0 - dNum) * m_Homing.dPoint0[1] + dNum * m_Homing.dPoint1[1];

	Point0 = D3DXVECTOR2(dPoint[0], dPoint[1]);

	// dPoint12(角ばっているところの二か所目の点の1つ目(x座標)) = (1-分割数) * 中点(x座標) + 分割数 * 終点(x座標)or中間点（3次元）
	dPoint[0] = (1.0 - dNum) * m_Homing.dPoint1[0] + dNum * m_Homing.dPoint2[0];
	// dPoint13(角ばっているところの二か所目の点の2つ目(y座標)) = (1-分割数) * 中点(y座標) + 分割数 * 終点(y座標)or中間点（3次元）
	dPoint[1] = (1.0 - dNum) * m_Homing.dPoint1[1] + dNum * m_Homing.dPoint2[1];

	Point1 = D3DXVECTOR2(dPoint[0], dPoint[1]);

	// 3次元のベジェ曲線(制御点が2個)
	// dPoint14(角ばっているところの二か所目の点の1つ目(x座標)) = (1-分割数) * 始点(x座標) + 分割数 * 終点(y座標)
	dPoint[0] = (1.0 - dNum) * m_Homing.dPoint2[0] + dNum * m_Homing.dPoint3[0];

	// dPoint15(角ばっているところの二か所目の点の2つ目(z座標)) = (1-分割数) * 始点(y座標) + 分割数 * 終点(y座標)
	dPoint[1] = (1.0 - dNum) * m_Homing.dPoint2[1] + dNum * m_Homing.dPoint3[1];

	Point2 = D3DXVECTOR2(dPoint[0], dPoint[1]);

	// dPoint02(2点取った直線の真ん中)　= (1- 分割数) * dPoint10 + 分割数 ＊dPoint12
	dPoint02[0] = (1.0 - dNum) * Point0.x + dNum * Point1.x;
	// dPoint02(2点取った直線の真ん中)　= (1- 分割数) * dPoint11 + 分割数 ＊dPoint13
	dPoint02[1] = (1.0 - dNum) * Point0.y + dNum* Point1.y;

	// dPoint03(2点取った直線の真ん中)　= (1- 分割数) * dPoint10 + 分割数 ＊dPoint12
	dPoint03[0] = (1.0 - dNum) * Point1.x + dNum * Point2.x;
	// dPoint03(2点取った直線の真ん中)　= (1- 分割数) * dPoint10 + 分割数 ＊dPoint12
	dPoint03[1] = (1.0 - dNum) * Point1.y + dNum * Point2.y;

	// dPoint04(2点取った直線の真ん中)　= (1- 分割数) * dPoint02 + 分割数 ＊dPoint03
	dPoint04[0] = (1.0 - dNum) * dPoint02[0] + dNum * dPoint03[0];
	// dPoint04(2点取った直線の真ん中)　= (1- 分割数) * dPoint02 + 分割数 ＊dPoint03
	dPoint04[1] = (1.0 - dNum) * dPoint02[1] + dNum* dPoint03[1];

	return D3DXVECTOR3(dPoint04[0], dPoint04[1],0);
}