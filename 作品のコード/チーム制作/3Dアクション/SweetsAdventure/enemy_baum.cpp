#include "main.h"
#include "enemy_baum.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "layer_structure.h"
#include "game.h"
#include "player.h"
#include "collision.h"
#include "stage.h"
#include "Enemy.h"
#include "gauge.h"
#include "fair_Effect.h"
#include "sound.h"

CEnemy_Baum::CEnemy_Baum(OBJTYPE nPriority) : CScene(nPriority)
{

}

CEnemy_Baum::~CEnemy_Baum()
{

}

CEnemy_Baum *CEnemy_Baum::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy_Baum *pEnemy_Baum = NULL;
	pEnemy_Baum = new CEnemy_Baum(OBJTYPE_ENEMY_BAUM);
	pEnemy_Baum->m_pos = pos;
	pEnemy_Baum->m_rot = rot;
	pEnemy_Baum->Init();
	return pEnemy_Baum;
}

HRESULT CEnemy_Baum::Init()
{
	m_fSoundInterval = 0.0f;
	m_fWalkSoundInterval = 0.0f;
	m_nLife = BAUM_LIFE;
	//ファイル読み込み
	CLayer_Structure *pLayer = NULL;
	pLayer = new CLayer_Structure;
	pLayer->SetLayer_Structure("data/TEXT/EnemyParts001.txt", &m_pModel[0]);
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
		m_MotionType = 0;
		m_pMotion->MotionLoad("data/TEXT/Baumkuchen_motion.txt");

	}

	return S_OK;
}

void CEnemy_Baum::Uninit()
{
	CGauge *pGauge = CManager::GetGame()->GetGauge();
	if (pGauge != NULL)
	{
		pGauge->SetGauge(-10.0f);
	}
	for (int nCntParts = 0; nCntParts < MAX_ENEMY_BAUM_PARTS; nCntParts++)
		if (m_pModel[nCntParts] != NULL)
		{
			m_pModel[nCntParts]->Uninit();
			m_pModel[nCntParts] = NULL;
		}
	Release();

}

void CEnemy_Baum::Update()
{
	m_lastPos = m_pos;
	D3DXVECTOR3	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pos = CManager::GetGame()->GetPlayer()->GetPos();				//位置
	D3DXVECTOR3 BulletVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BulletVec = pos - m_pos;			//敵と弾のベクトル
	float fLength = 0.0f;
	float fLengthX = 0.0f;
	fLength = sqrtf((BulletVec.z*BulletVec.z) + (BulletVec.x*BulletVec.x));
	m_fAng = atan2(BulletVec.x, BulletVec.z);//敵の向き
	//敵の出現
	if (fLength < MAX_BAUM_DRAWRADIUS)
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
		m_rot.y = m_fAng + (D3DX_PI);
		//発射する方向を求める
		m_MoveSpeed.x = sinf(m_fAng)*MAX_BAUM_SPEED;
		m_MoveSpeed.z = cosf(m_fAng)*MAX_BAUM_SPEED;

		m_fWalkSoundInterval -= 0.1f;

		if (m_fWalkSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WALK2);
			m_fWalkSoundInterval = 2.0f;
		}

	}
	else
	{
		m_MoveSpeed.x = 0.0f;
		m_MoveSpeed.y = 0.0f;
		m_MoveSpeed.z = 0.0f;
	}
	if (fLength < MAX_TEMPTATION_RADIUS)
	{
		//誘惑ゲージを増やす
		CGauge *pGauge = CManager::GetGame()->GetGauge();
		pGauge->SetGauge(BAUM_ADD_SPEED);

		m_fSoundInterval -= 0.1f;

		if (m_fSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DAMAGE);

			m_fSoundInterval = 6.0f;
		}

	}
	//位置に移動量を足す
	m_pos += m_MoveSpeed;
	//敵の行動パターン実装予定
	//if (m_bUninit == true)
	//{
	//	Uninit();
	//}
	if (m_bDraw == true)
	{
		CCollision *pCollision = new CCollision;
		//ダメージを受けたら無敵状態にする
		if (m_bDamage == true)
		{
			if (m_bEffect == false)
			{
				m_bEffect = true;
				Cfair_Effect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.x), CTexture::Effect);
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

		CScene *pEnemy = CScene::GetScene(OBJTYPE_ENEMY);
		while (pEnemy!=NULL)
		{
			if (pEnemy != NULL)
			{
				pCollision->CollisionObjectEnemy((CEnemy*)pEnemy, &m_pos, &m_lastPos, 50.0f);
			}
			pEnemy = pEnemy->GetSceneNext(pEnemy);
		}

		CScene *pEnemyBaum = CScene::GetScene(OBJTYPE_ENEMY_BAUM);
		while (pEnemyBaum!=NULL)
		{
			if (pEnemyBaum != NULL&&pEnemyBaum == this)
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

		//敵の行動パターン実装予定
		//if (m_bUninit == true)
		//{
		//	Uninit();
		//}
		//モーション再生
		if (m_pMotion != NULL)
		{
			m_pMotion->PlayMotion(MAX_ENEMY_BAUM_PARTS, &m_pModel[0], m_MotionType, m_MotionLastType, m_bMotionStop, m_bAttack, m_bNeutral);
		}

		delete pCollision;

	}
}

void CEnemy_Baum::Draw()
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
		for (int nCntParts = 0; nCntParts < MAX_ENEMY_BAUM_PARTS; nCntParts++)
		{
			m_pModel[nCntParts]->Draw();
		}

	}
}
//----------------------------------------------------------
//体力の増減
//----------------------------------------------------------
void CEnemy_Baum::AddLife(int nLife)
{
	m_nLife += nLife;
}
bool  CEnemy_Baum::bColision()
{
	return 0;
}