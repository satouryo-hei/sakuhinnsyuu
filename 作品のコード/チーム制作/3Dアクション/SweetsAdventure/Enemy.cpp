#include "main.h"
#include "Enemy.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "layer_structure.h"
#include "game.h"
#include "player.h"
#include "collision.h"
#include "stage.h"
#include "gauge.h"
#include "fair_Effect.h"
#include "sound.h"

CEnemy::CEnemy(OBJTYPE nPriority) : CScene(nPriority)
{

}

CEnemy::~CEnemy()
{

}

CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pPlayer = NULL;
	pPlayer = new CEnemy;
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->Init();
	return pPlayer;
}

HRESULT CEnemy::Init()
{
	m_fWalkSoundInterval = 0.0f;
	m_fSoundInterval = 0.0f;
	m_nLife = ENEMY_LIFE;
	m_bDamage = false;
	//ファイル読み込み
	CLayer_Structure *pLayer = NULL;
	pLayer = new CLayer_Structure;
	pLayer->SetLayer_Structure("data/TEXT/EnemyParts000.txt", &m_pModel[0]);
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
		m_MotionType = 0;
		m_pMotion->MotionLoad("data/TEXT/cookie_motion.txt");

	}


	return S_OK;
}

void CEnemy::Uninit()
{
	CGauge *pGauge = CManager::GetGame()->GetGauge();
	
	// ゲージ減らす
	if (pGauge != NULL)
	{
		pGauge->SetGauge(-10.0f);
	}

	// モデル破棄
	for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
	{
		if (m_pModel[nCntParts] != NULL)
		{
			m_pModel[nCntParts]->Uninit();
			m_pModel[nCntParts] = NULL;
		}
	}

	Release();
}

void CEnemy::Update()
{

	m_lastPos = m_pos;
	D3DXVECTOR3	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pos = CManager::GetGame()->GetPlayer()->GetPos();				//位置
	D3DXVECTOR3 BulletVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BulletVec = pos - m_pos;			//敵と弾のベクトル
	float fLength = 0.0f;
	float fLengthX = 0.0f;
	fLength = sqrtf((BulletVec.z*BulletVec.z)+ (BulletVec.x*BulletVec.x));
	m_fAng = atan2(BulletVec.x, BulletVec.z);//敵の向き
	//敵の出現
	if (fLength < MAX_DRAWRADIUS)
	{
		m_bDraw = true;
	}
	else
	{
		m_bDraw = false;
	}
	//敵の追従
	if (fLength < MAX_COLRADIUS)
	{
		m_rot.y = m_fAng+ (D3DX_PI);
		//発射する方向を求める
		m_MoveSpeed.x = sinf(m_fAng)*MAX_SPEED;
		m_MoveSpeed.z = cosf(m_fAng)*MAX_SPEED;
		m_MotionType = MOVE;

		m_fWalkSoundInterval -= 0.1f;

		if (m_fWalkSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WALK2);
			m_fWalkSoundInterval = 2.0f;
		}
	}
	//範囲外の時
	else
	{
		m_MotionType = NEUTRAL;
		m_MoveSpeed.x = 0.0f;
		m_MoveSpeed.y = 0.0f;
		m_MoveSpeed.z = 0.0f;
	}
	//敵の誘惑
	if (fLength < MAX_TEMPTATION_RADIUS)
	{
		CGauge *pGauge = CManager::GetGame()->GetGauge();

		//誘惑ゲージを増やす
		pGauge->SetGauge(ENEMY_ADD_SPEED);

		m_fSoundInterval -= 0.1f;

		if (m_fSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DAMAGE);

			m_fSoundInterval = 6.0f;
		}
	}

	m_pos += m_MoveSpeed;

	//敵の行動パターン実装予定
	//if (m_bUninit == true)
	//{
	//	Uninit();
	//}
	if (m_bDraw == true)
	{
		CCollision *pCollision = new CCollision;

		CScene *pEnemy = CScene::GetScene(OBJTYPE_ENEMY);

		//ダメージを受けたら無敵状態にする
		if (m_bDamage == true)
		{
			if (m_bEffect == false)
			{
				m_bEffect = true;
			}

			//カウンターを増やす
			m_nTimer++;
			//カウンターが特定の時間に行ったら
			if (m_nTimer >= INVINCIBLE_TIME)
			{
				//通常状態に戻す
				m_bDamage = false;
				m_bEffect = false;
			}
		}

		while (pEnemy!=NULL)
		{
			if (pEnemy != NULL && pEnemy == this)
			{
				pCollision->CollisionObjectEnemy((CEnemy*)pEnemy, &m_pos, &m_lastPos, 50.0f);
			}
			pEnemy = pEnemy->GetSceneNext(pEnemy);
		}

		CScene *pEnemyBaum = CScene::GetScene(OBJTYPE_ENEMY_BAUM);
		while (pEnemyBaum!=NULL)
		{
			if (pEnemyBaum != NULL)
			{
				pCollision->CollisionObjectEnemy((CEnemy_Baum*)pEnemyBaum, &m_pos, &m_lastPos, 50.0f);
			}
			pEnemyBaum = pEnemyBaum->GetSceneNext(pEnemyBaum);
		}

		CPlayer *pPlayer = CManager::GetGame()->GetPlayer();
		if (pPlayer != NULL)
		{
			pCollision->CollisionObjectPlayer(pPlayer, &m_pos, &m_lastPos, 50.0f);
		}
		//モーション再生
		if (m_pMotion != NULL)
		{
			m_pMotion->PlayMotion(MAX_ENEMY_PARTS, &m_pModel[0], m_MotionType, m_MotionLastType, m_bMotionStop, m_bAttack, m_bNeutral);
		}
		delete pCollision;
	}
}

void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス
										  //各パーツのワールドマトリックスの初期化gtryg
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	//向きを反映
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
	//位置を反映
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//各パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_bDraw == true)
	{
		//モデル描画
		for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
		{
			m_pModel[nCntParts]->Draw();
		}

	}
}
//----------------------------------------------------------
//体力の増減
//----------------------------------------------------------
void CEnemy::AddLife(int nLife)
{
	m_nLife += nLife;
}

bool  CEnemy::bColision()
{
	return 0;
}