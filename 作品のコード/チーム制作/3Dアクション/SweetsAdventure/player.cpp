#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "model.h"
#include "motion.h"
#include "layer_structure.h"
#include "score.h"
#include "keyboard.h"
#include "game.h"
#include "collision.h"
#include "camera.h"
#include "goal.h"
#include "billboard.h"
#include "fade.h"
#include "camera.h"
#include "stage.h"
#include "field.h"
#include "model_spawner.h"
#include "Enemy.h"
#include "enemy_baum.h"
#include "shadow.h"
#include "XInput.h"
#include "effect_sa.h"
#include "explosion_effect.h"
#include "circle_effect.h"
#include "smoke_effect.h"
#include "barrier_block.h"
#include "barrier_wood.h"
#include "gauge.h"
#include "fair_effect.h"
#include "sound.h"

CPlayer::CPlayer(OBJTYPE nPriority) : CScene(nPriority)
{
	memset(m_pMotion, NULL, sizeof(m_pMotion));
	memset(m_pModel, NULL, sizeof(m_pModel));

}

CPlayer::~CPlayer()
{

}

CPlayer *CPlayer::Create()
{
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init();
	return pPlayer;
}

HRESULT CPlayer::Init()
{
	//�t�@�C���ǂݍ���
	//�K�w�\���̐ݒ�
	m_pLayer = new CLayer_Structure;
	m_pLayer->SetLayer_Structure("data/TEXT/PlayerParts000.txt", &m_pModel[0]);
	//����̓ǂݍ���
	FILE *pFile = fopen("data/TEXT/WeaponSet000.txt", "r");
	char sFileName[3][64];
	char string[6][255];
	D3DXVECTOR3 PartsPos, PartsRot;	//�e�p�[�c�̈ʒu�ƌ���
	int nCntModel=0;
	int nNumModel = 0;
	int nCntWeapon = 0;
	int nCntCollision = 0;
	int nParent = 0;
	if (pFile != NULL)
	{
		while (true)
		{
			//��P���ǂݍ���
			fscanf(pFile, "%s", &string[0]);

			//���f����
			if (strcmp(string[0], "NUM_MODEL") == 0)
			{
				fscanf(pFile, "%s", &string[1]);
				fscanf(pFile, "%d", &nNumModel);
			}

			//���f���̃t�@�C���̂Ȃ܂�
			if (strcmp(string[0], "MODEL_FILENAME") == 0)
			{
				fscanf(pFile, "%s", &string[1]);
				fscanf(pFile, "%s", &sFileName[nCntModel]);
				nCntModel++;
			}
			//����̓ǂݍ���
			while (strcmp(string[0], "PARTSSET") == 0)
			{
				fscanf(pFile, "%s", &string[1]);

				//�e���f���ԍ�
				if (strcmp(string[1], "PARENT") == 0)
				{
					fscanf(pFile, "%s", &string[2]);
					fscanf(pFile, "%d", &nParent);
					
				}
				//�ʒu
				if (strcmp(string[1], "POS") == 0)
				{
					fscanf(pFile, "%s", &string[2]);
					fscanf(pFile, "%f %f %f", &PartsPos.x,&PartsPos.y,&PartsPos.z);
				}
				//�ʒu
				if (strcmp(string[1], "ROT") == 0)
				{
					fscanf(pFile, "%s", &string[2]);
					fscanf(pFile, "%f %f %f", &PartsRot.x, &PartsRot.y, &PartsRot.z);
				}
				//�ʒu
				if (strcmp(string[1], "END_PARTSSET") == 0)
				{
					m_pWeapon[nCntWeapon] = CModel::Create(PartsPos, PartsRot, sFileName[nCntWeapon]);
					m_pWeapon[nCntWeapon]->SetParent(m_pModel[nParent]);
					nCntWeapon++;
					break;
				}
			}

			while (strcmp(string[0], "COLLISIONSET") == 0)
			{
				fscanf(pFile, "%s", &string[1]);

				//�e���f���ԍ�
				if (strcmp(string[1], "PARENT") == 0)
				{
					fscanf(pFile, "%s", &string[2]);
					fscanf(pFile, "%d", &nParent);

				}
				//�ʒu
				if (strcmp(string[1], "POS") == 0)
				{
					fscanf(pFile, "%s", &string[2]);
					fscanf(pFile, "%f %f %f", &PartsPos.x, &PartsPos.y, &PartsPos.z);
				}
				//�ʒu
				if (strcmp(string[1], "ROT") == 0)
				{
					fscanf(pFile, "%s", &string[2]);
					fscanf(pFile, "%f %f %f", &PartsRot.x, &PartsRot.y, &PartsRot.z);
				}
				//�ʒu
				if (strcmp(string[1], "END_COLLISIONSET") == 0)
				{
					m_pCollision[nCntCollision] = CModel::Create(PartsPos, PartsRot, sFileName[2]);
					m_pCollision[nCntCollision]->SetParent(m_pWeapon[nParent]);
					m_pCollision[nCntCollision]->SetDraw(true);
					nCntCollision++;
					break;
				}
			}

			if (strcmp(string[0], "END_SCRIPTS") == 0)
			{
				break;
			}

		}
	}
	//���[�V�����f�[�^�̓ǂݍ���
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pMotion[nCnt] == NULL)
		{
			m_pMotion[nCnt] = new CMotion;
			m_nMotionType[nCnt] = 0;

		}
	}

	m_pMotion[TYPE_SWORD]->MotionLoad("data/TEXT/Player_Sword000.txt");
	m_pMotion[TYPE_HAMMER]->MotionLoad("data/TEXT/Player_Hummer000.txt");
	m_nCntJump = MAX_PLAYER_JUMP;
	m_bJumpLock = false;
	m_pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);
	m_move = -2.0f;
	m_fGravitySpeed = 0.5f;
	m_fSoundInterval = 1.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fGravity = 0.0f;//�d�͓x
	m_bland = true;
	m_nWeaponType = 0;
	m_bMotionStop = false;
	m_bAttack = false;
	m_bMove = false;
	pShadow = CShadow::Create(m_pos, PLAYER_SIZE, CTexture::SHADOW);
	return S_OK;
}

void CPlayer::Uninit()
{
	for (int nCntParts = 0; nCntParts < m_pLayer->GetMaxParts(); nCntParts++)
	{
		if (m_pModel[nCntParts] != NULL)
		{
			m_pModel[nCntParts]->Uninit();
			m_pModel[nCntParts] = NULL;
		}

	}
	Release();
}

void CPlayer::Update()
{
	CXInput *pGamePad = CManager::GetXInput();
	CStage *pStage = CManager::GetGame()->GetStage();
	CGauge *pGauge = CManager::GetGame()->GetGauge();

	//�O��̈ʒu���̕ۑ�
	m_lastpos = m_pos;

	//�v���C���[�̈ړ�����
	if (m_bAttack == false && m_bMotionStop==false)
	{
		Move(4);
	}


	CManager::GetCamera()->SetPlayerCamera(this);

	//����̐؂�ւ�
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)
	{
		m_nWeaponType = TYPE_SWORD;
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_CHANGE_WEAPON);
	}
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER) == true)
	{
		m_nWeaponType = TYPE_HAMMER;
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_CHANGE_WEAPON);
	}

	if (m_bJumpLock == false)
	{
		//�U��
		Attack();
	}

	//�W�����v�̈ړ��ʂɉ��Z
	if (pGamePad->GetGamepadPress(XINPUT_GAMEPAD_A) == true && m_bJumpLock == false)	//���؁[��
	{
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_JUMP);

		switch (m_nWeaponType)
		{
		case TYPE_SWORD:
			m_nMotionType[TYPE_SWORD] = S_JUMP;

			break;
		case TYPE_HAMMER:
			m_nMotionType[TYPE_HAMMER] = H_JUMP;
			break;
		}
		m_fGravity = 13.0f;
		//�W�����v�̉񐔌��Z
		m_nCntJump--;
		//�W�����v�񐔂�0�ɂȂ�����W�����v�ł��Ȃ��悤�ɂ���
		if (m_nCntJump <= 0)
		{
			m_bJumpLock = true;
		}
	}

	////�d�͉��Z
	if (m_fGravitySpeed > 0.0f)
	{
		m_fGravity -= m_fGravitySpeed;
		m_pos.y += m_fGravity;
	}
	//���������ǂ���
	if (m_pos.y <= PLAYER_FALL)
	{
		//�Q�[�W�𑝂₷
		pGauge->SetGauge(20.0f);
		m_pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z);
		m_fGravity = 0.0f;
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WATER_FALL);
	}
	pShadow->SetPos(m_pos.x, m_pos.z, D3DXVECTOR3(PLAYER_SIZE, 0.0f, PLAYER_SIZE));

	//�ݒu���Ƃ̓����蔻��
	CCollision *pCollision = new CCollision;
	float ModelPosY = 0.0f;
	float fShadowY = 0.0f;
	for (int nCnt = 0; nCnt < pStage->GetMaxModel(); nCnt++)
	{
		CModel_Spawner *pModel = pStage->GetModel(nCnt);
		if (pModel != NULL)
		{
			if (pCollision->CollisionObjectModelShadow(pModel, &m_pos, 20.0f, fShadowY) == CCollision::COLLISION_UP)
			{
				pShadow->SetPosY((fShadowY)/2.0f + SHADOWGRAVITY);
				pShadow->SetGravi(0.0f);
				pShadow->SetGraviSp(0.0f);
			}
			else
			{
				pShadow->SetGraviSp(SHADOWGRAVITY);
			}

			//�n�ʂɂ����痎���Ȃ�
			if (pCollision->CollisionObjectModel(pStage->GetModel(nCnt), &m_pos, &m_lastpos, 20.0f, ModelPosY) == CCollision::COLLISION_UP)
			{
				m_fGravity = 0;
				m_fGravitySpeed = 0;
				m_pos.y = ModelPosY + 0.1f;
				//�W�����v�񐔕���
				m_nCntJump = MAX_PLAYER_JUMP;
				m_bJumpLock = false;
			}
			else if (pCollision->CollisionObjectModel(pStage->GetModel(nCnt), &m_pos, &m_lastpos, 20.0f, ModelPosY) == CCollision::COLLISION_DOWN)
			{
				if (m_pos.y + m_pModel[1]->GetMaxPos().y >= ModelPosY)
				{
					m_pos.y = ModelPosY - m_pModel[1]->GetMaxPos().y;
					m_fGravity = 0;
				}
			}
			else
			{
				m_fGravitySpeed = 0.5f;
			}
		}
	}

	//�G�Ƃ̓����蔻��
	//����ƓG�̓����蔻��
	for (int nCnt = 0; nCnt < pStage->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = pStage->GetEnemy(nCnt);
		if (pEnemy != NULL)
		{
			if (m_bAttack == true)
			{
				//���킪�G�͈̔͂ɓ�������
				if (pCollision->CollisionWeapon(pEnemy, m_pCollision[m_nWeaponType]->GetPos() + m_pWeapon[m_nWeaponType]->GetPos() + m_pos, 60.0f) == true)
				{
					//�̗͂����炷
					if (pEnemy->GetbDamage() == false)
					{
						//Cfair_Effect::Create(pEnemy->GetEnemyPos(), CTexture::Effect);

						pEnemy->AddLife(-1);
						pEnemy->SetbDamage(true);
					}
					D3DXVECTOR3 pos = pEnemy->GetEnemyPos();

					pos.y += 50;
					if (pEnemy->GetLife() <= 0)
					{
						CExplosion_Effect::Create(pos, MAX_LIFE, MIN_LIFE, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(5.0f, 5.0f, 5.0f), D3DXCOLOR(Set_COL_R, Set_COL_G, Set_COL_B, Set_COL_A), CTexture::Effect, 100, D3DXVECTOR3(0.05f, 0.05f, 0.05f));

						//�G���|���
						pEnemy->SetUninit(true);

						CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENEMY_DEATH4);
					}

					switch (m_nWeaponType)
					{
					case TYPE_SWORD:
						CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SWORD_HIT);

						break;

					case TYPE_HAMMER:
						CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_AXE_HIT);
						break;
					}
				}

			}
			pCollision->CollisionObjectEnemy(pEnemy, &m_pos, &m_lastpos, 50.0f);
		}
	}

	for (int nCnt = 0; nCnt < pStage->GetMaxEnemyBaum(); nCnt++)
	{
		CEnemy_Baum *pEnemyBaum = pStage->GetEnemyBaum(nCnt);
		if (pEnemyBaum != NULL)
		{
			if (m_bAttack == true)
			{
				//���킪�G�͈̔͂ɓ�������
				if (pCollision->CollisionWeapon(pEnemyBaum, m_pCollision[m_nWeaponType]->GetPos() + m_pWeapon[m_nWeaponType]->GetPos() + m_pos, 60.0f) == true)
				{
					//�̗͂����炷
					if (pEnemyBaum->GetbDamage() == false)
					{
						//Cfair_Effect::Create(pEnemyBaum->GetEnemyPos(), CTexture::Effect);

						pEnemyBaum->AddLife(-1);
						pEnemyBaum->SetbDamage(true);
					}

					if (pEnemyBaum->GetLife() <= 0)
					{
						CExplosion_Effect::Create(pEnemyBaum->GetEnemyPos(), MAX_LIFE, MIN_LIFE, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(5.0f, 5.0f, 5.0f), D3DXCOLOR(Set_COL_R, Set_COL_G, Set_COL_B, Set_COL_A), CTexture::Effect, 100, D3DXVECTOR3(0.05f, 0.05f, 0.05f));

						//�G���|���
						pEnemyBaum->SetUninit(true);

						CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENEMY_DEATH);

					}

					switch (m_nWeaponType)
					{
					case TYPE_SWORD:
						CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SWORD_HIT);

						break;

					case TYPE_HAMMER:
						CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_AXE_HIT);
						break;
					}
				}
			}
			pCollision->CollisionObjectEnemy(pEnemyBaum, &m_pos, &m_lastpos, 50.0f);

		}
	}

	for (int nCnt = 0; nCnt < pStage->GetMaxField(); nCnt++)
	{
		//���̓����蔻��
		if (pCollision->CollisionField(pStage->GetField(nCnt), &m_pos, &m_lastpos, m_pModel[0]->GetMaxPos().x, ModelPosY) == true)
		{
			m_fGravity = 0;
			m_fGravitySpeed = 0;
			m_pos.y = ModelPosY + 0.1f;
			//�W�����v�񐔕���
			m_nCntJump = MAX_PLAYER_JUMP;
			m_bJumpLock = false;
		}

		if (pCollision->CollisionFieldShadow(pStage->GetField(nCnt), &m_pos, 20.0f, fShadowY))
		{
			pShadow->SetPosY((fShadowY) / 2.0f);
			pShadow->SetGravi(0.0f);
			pShadow->SetGraviSp(0.0f);

		}
	}
	//�E�G�n�[�X�̕ǂ̓����蔻��
	CScene *pSceneBlock = CScene::GetScene(OBJTYPE_BLOCK);
	while (pSceneBlock!=NULL)
	{
		CBarrier_Block *pBlock = (CBarrier_Block*)pSceneBlock;
		CScene *pSceneBlockNext = CScene::GetSceneNext(pSceneBlock);
		//�����蔻��
		if (pBlock->GetModel() != NULL)
		{
			pCollision->CollisionObjectModel(pBlock->GetModel(), &m_pos, &m_lastpos, 20.0f, ModelPosY);
			//����Ƃ̓����蔻��
			if (m_bAttack == true && m_nWeaponType == TYPE_HAMMER)
			{
				if (pCollision->CollisionWeaponBarrier(pBlock->GetModel(), m_pCollision[m_nWeaponType]->GetPos() + m_pWeapon[m_nWeaponType]->GetPos() + m_pos, 60.0f) == true)
				{
					//�Q�[�W������
					pGauge->SetGauge(-10.0f);
					//�ǂ�������
					pBlock->SetUninit(true);

					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_AXE_HIT_WALL);
					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_BREAK_WALL);
				}

			}

			else if (m_bAttack == true && m_nWeaponType == TYPE_SWORD)
			{
				if (pCollision->CollisionWeaponBarrier(pBlock->GetModel(), m_pCollision[m_nWeaponType]->GetPos() + m_pWeapon[m_nWeaponType]->GetPos() + m_pos, 60.0f) == true)
				{
					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SWORD_HIT_WALL);
				}

			}
		}

		//���̃I�u�W�F�N�g������
		pSceneBlock = pSceneBlockNext;
	}
	//�؂̓����蔻��
	CScene *pSceneWood = CScene::GetScene(OBJTYPE_WOOD);
	while (pSceneWood != NULL)
	{
		CBarrier_wood *pWood = (CBarrier_wood*)pSceneWood;
		CScene *pSceneWoodNext = CScene::GetSceneNext(pSceneWood);
		if (pWood->GetModel() != NULL)
		{
			//�����蔻��
			pCollision->CollisionObjectModel(pWood->GetModel(), &m_pos, &m_lastpos, 20.0f, ModelPosY);

			//����Ƃ̓����蔻��
			if (m_bAttack == true && m_nWeaponType == TYPE_SWORD)
			{
				if (pCollision->CollisionWeaponBarrier(pWood->GetModel(), m_pCollision[m_nWeaponType]->GetPos() + m_pWeapon[m_nWeaponType]->GetPos() + m_pos, 80.0f) == true)
				{
					//�Q�[�W������
					pGauge->SetGauge(-10.0f);
					//�؂�������
					pWood->SetUninit(true);

					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SWORD_HIT_TREE);
					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_BREAK_TREE);
				}

			}

			else if (m_bAttack == true && m_nWeaponType == TYPE_HAMMER)
			{
				if (pCollision->CollisionWeaponBarrier(pWood->GetModel(), m_pCollision[m_nWeaponType]->GetPos() + m_pWeapon[m_nWeaponType]->GetPos() + m_pos, 80.0f) == true)
				{
					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_AXE_HIT_TREE);
				}
			}

		}
		//���̃I�u�W�F�N�g������
		pSceneWood = pSceneWoodNext;
	}
	CScene *pScene = CScene::GetScene(OBJTYPE_ITEM);
	while (pScene!=NULL)
	{
		CScene *pSceneNext = CScene::GetSceneNext(pScene);

		if (pScene != NULL)
		{
			//�S�[���Ƃ̓����蔻��
			if (pCollision->SetCollision(this, pScene) == true)
			{
				CManager::SetClear(true);
				CManager::GetGame()->GetGoal()->Uninit();
				CManager::GetFade()->SetFade(CManager::MODE_RESULT);

				CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_GOAL);
				CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_GOAL2);
				CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);
				CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_WARNING);
			}
		}
		pScene = pSceneNext;

	}
	//���[�V�����̍Đ�
	m_pMotion[m_nWeaponType]->PlayMotion(MAX_PLAYER_PARTS,&m_pModel[0], m_nMotionType[m_nWeaponType], m_nMotionLastType[m_nWeaponType], m_bMotionStop, m_bAttack, m_bNeutral);

}

void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
	//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����gtryg
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	//�����𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���f������
	for (int nCntParts = 0; nCntParts < m_pLayer->GetMaxParts(); nCntParts++)
	{
		m_pModel[nCntParts]->Draw();
	}
	switch (m_nWeaponType)
	{
	case TYPE_SWORD:
		m_pWeapon[TYPE_SWORD]->Draw();
		m_pCollision[TYPE_SWORD]->Draw();
		break;
	case TYPE_HAMMER:
		m_pWeapon[TYPE_HAMMER]->Draw();
		m_pCollision[TYPE_HAMMER]->Draw();
		break;
	}
}
//-----------------------------------------------------------------
//�U���̏���
//-----------------------------------------------------------------
void CPlayer::Attack(void)
{

	CXInput *pGamePad = CManager::GetXInput();

	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
	{
		//�R���{���Ă��Ȃ��Ƃ��̏���
		if (m_nAttackType[m_nWeaponType] == 0)
		{
			//�R���{���𑝂₷
			m_nAttackType[m_nWeaponType]++;

			m_bAttack = true;
		}

		//�R���{���Ă���Ƃ�
		if (m_nAttackType[m_nWeaponType] != 0&&
			m_bAttack==false && m_bMotionStop==true)
		{
			//�R���{���𑝂₷
			m_nAttackType[m_nWeaponType]++;
			if (m_nAttackType[TYPE_SWORD] >= 4)
			{
				m_nAttackType[TYPE_SWORD] = 1;
			}
			if (m_nAttackType[TYPE_HAMMER] >= 3)
			{
				m_nAttackType[TYPE_HAMMER] = 1;
			}
			m_bAttack = true;

		}

		if (m_bAttack == true)
		{
			//���̕���
			switch (m_nWeaponType)
			{
			case TYPE_SWORD:
				//���݂̃R���{�������ă��[�V������ς���
				switch (m_nAttackType[TYPE_SWORD])
				{
				case COMBO_1:
					m_nMotionType[TYPE_SWORD] = S_ATTACK_1;
					break;
				case COMBO_2:
					m_nMotionType[TYPE_SWORD] = S_ATTACK_2;
					break;
				case COMBO_3:
					m_nMotionType[TYPE_SWORD] = S_ATTACK_3;
					break;
				}

				if (m_nTimer <= 0 && m_bMotionStop == false)
				{
					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SWORD_ATTACK);
				}

				break;

			case TYPE_HAMMER:
				//���݂̃R���{�������ă��[�V������ς���
				switch (m_nAttackType[TYPE_HAMMER])
				{
				case COMBO_1:
					m_nMotionType[TYPE_HAMMER] = H_ATTACK_1;
					break;
				case COMBO_2:
					m_nMotionType[TYPE_HAMMER] = H_ATTACK_2;
					break;
				}

				if (m_nTimer <= 0 && m_bMotionStop == false)
				{
					CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_AXE_ATTACK);
				}

				break;
			}

		}
	}
	if (m_bMotionStop == false&& m_bAttack == false)
	{
		m_nAttackType[m_nWeaponType] = 0;
	}
	//�U���̃��[�V������������
	else if (m_bMotionStop == true)
	{
		m_nTimer++;

		if (m_nTimer >= MAX_LIMIT)
		{
			m_nTimer = 0;
			m_bMotionStop = false;
		}
	}
}
//-----------------------------------------------------------------
//�ړ�����
//-----------------------------------------------------------------
void CPlayer::Move(float fMoveSpeed)
{
	CXInput *pXInput = CManager::GetXInput();

	CCamera *pCamera = CManager::GetCamera();
	float rot_y = pCamera->GetRot().y;

	//�ړ�(8����)
	if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)		//������
	{
		m_nEffectTimer++;
		if (m_nEffectTimer >= MAX_SMOKE_CNT&&m_bJumpLock==false)
		{
			m_nEffectTimer = 0;
			// �������Ƃ��Ƃ��̓y��
			CSmoke_Effect::Create(m_pos, 0.5f, D3DXVECTOR3(MAX_SMOKE_MOVE_X, MAX_SMOKE_MOVE_Y, MAX_SMOKE_MOVE_Z), D3DXVECTOR3(MAX_SMOKE_SIZE, MAX_SMOKE_SIZE, 3.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CTexture::Effect, D3DXVECTOR3(0.1f, 0.1f, 0.1f), MAX_SMOKE_NUMALL, 5, 15);

		}

		if (m_bJumpLock == false)
		{
			switch (m_nWeaponType)
			{
			case TYPE_SWORD:
				m_nMotionType[TYPE_SWORD] = S_MOVE;
				break;
			case TYPE_HAMMER:
				m_nMotionType[TYPE_HAMMER] = H_MOVE;
				break;
			}

		}

		if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)	//�������
		{

			m_rot.y = rot_y + D3DX_PI / -0.78f;

			m_pos.x = m_pos.x + sinf(rot_y) *fMoveSpeed;
			m_pos.z = m_pos.z + cosf(rot_y) *fMoveSpeed;
			m_pos.x = m_pos.x - cosf(rot_y) *fMoveSpeed;
			m_pos.z = m_pos.z + sinf(rot_y) *fMoveSpeed;

		}
		else if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)	//��������
		{
			m_rot.y = rot_y + D3DX_PI / 3.78f;

			m_pos.x = m_pos.x - sinf(rot_y) *fMoveSpeed;
			m_pos.z = m_pos.z - cosf(rot_y) *fMoveSpeed;
			m_pos.x = m_pos.x - cosf(rot_y) *fMoveSpeed;
			m_pos.z = m_pos.z + sinf(rot_y) *fMoveSpeed;
		}
		else
		{
			m_rot.y = rot_y + D3DX_PI / 2;
			m_pos.x = m_pos.x - cosf(rot_y)* fMoveSpeed;
			m_pos.z = m_pos.z + sinf(rot_y)* fMoveSpeed;

		}
		m_bMove = true;
		m_fSoundInterval -= 0.1f;

	}

	else if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)		//�E����
	{
		m_nEffectTimer++;

		if (m_nEffectTimer >= MAX_SMOKE_CNT&&m_bJumpLock == false)
		{
			m_nEffectTimer = 0;
			// �������Ƃ��Ƃ��̓y��
			CSmoke_Effect::Create(m_pos, 0.5f, D3DXVECTOR3(MAX_SMOKE_MOVE_X, MAX_SMOKE_MOVE_Y, MAX_SMOKE_MOVE_Z), D3DXVECTOR3(MAX_SMOKE_SIZE, MAX_SMOKE_SIZE, 3.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CTexture::Effect, D3DXVECTOR3(0.1f, 0.1f, 0.1f), MAX_SMOKE_NUMALL, 5, 15);
		}

		if (m_bJumpLock == false)
		{
			switch (m_nWeaponType)
			{
			case TYPE_SWORD:
				m_nMotionType[TYPE_SWORD] = S_MOVE;
				break;
			case TYPE_HAMMER:
				m_nMotionType[TYPE_HAMMER] = H_MOVE;
				break;
			}

		}
		if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)		//�E�����
		{
			m_rot.y = rot_y + D3DX_PI / 0.78f;

			m_pos.x = m_pos.x + sinf(rot_y)*fMoveSpeed;
			m_pos.z = m_pos.z + cosf(rot_y)*fMoveSpeed;
			m_pos.x = m_pos.x + cosf(rot_y)*fMoveSpeed;
			m_pos.z = m_pos.z - sinf(rot_y)*fMoveSpeed;


		}
		else if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)	//�E������
		{
			m_rot.y = rot_y + D3DX_PI / -3.78f;

			m_pos.x = m_pos.x - sinf(rot_y)* fMoveSpeed;
			m_pos.z = m_pos.z - cosf(rot_y)* fMoveSpeed;
			m_pos.x = m_pos.x + cosf(rot_y)* fMoveSpeed;
			m_pos.z = m_pos.z - sinf(rot_y)* fMoveSpeed;


		}
		else
		{
			m_rot.y = rot_y + -D3DX_PI / 2;
			m_pos.x = m_pos.x + cosf(rot_y)* fMoveSpeed;
			m_pos.z = m_pos.z - sinf(rot_y)* fMoveSpeed;

		}

		m_bMove = true;
		m_fSoundInterval -= 0.1f;
	}

	else if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)		//�����
	{

		m_nEffectTimer++;

		if (m_nEffectTimer >= MAX_SMOKE_CNT&&m_bJumpLock == false)
		{
			m_nEffectTimer = 0;
			// �������Ƃ��Ƃ��̓y��
			CSmoke_Effect::Create(m_pos, 0.5f, D3DXVECTOR3(MAX_SMOKE_MOVE_X, MAX_SMOKE_MOVE_Y, MAX_SMOKE_MOVE_Z), D3DXVECTOR3(MAX_SMOKE_SIZE, MAX_SMOKE_SIZE, 3.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CTexture::Effect, D3DXVECTOR3(0.1f, 0.1f, 0.1f), MAX_SMOKE_NUMALL, 5, 15);

		}

		if (m_bJumpLock == false)
		{
			switch (m_nWeaponType)
			{
			case TYPE_SWORD:
				m_nMotionType[TYPE_SWORD] = S_MOVE;
				break;
			case TYPE_HAMMER:
				m_nMotionType[TYPE_HAMMER] = H_MOVE;
				break;
			}

		}
		m_rot.y = rot_y + D3DX_PI;

		m_pos.x = m_pos.x + sinf(rot_y) * fMoveSpeed;
		m_pos.z = m_pos.z + cosf(rot_y) * fMoveSpeed;

		m_bMove = true;
		m_fSoundInterval -= 0.1f;
	}

	else if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)		//������
	{
		m_nEffectTimer++;

		if (m_nEffectTimer >= MAX_SMOKE_CNT&&m_bJumpLock == false)
		{
			m_nEffectTimer = 0;
			// �������Ƃ��Ƃ��̓y��
			CSmoke_Effect::Create(m_pos, 0.5f, D3DXVECTOR3(MAX_SMOKE_MOVE_X, MAX_SMOKE_MOVE_Y, MAX_SMOKE_MOVE_Z), D3DXVECTOR3(MAX_SMOKE_SIZE, MAX_SMOKE_SIZE, 3.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CTexture::Effect, D3DXVECTOR3(0.1f, 0.1f, 0.1f), MAX_SMOKE_NUMALL, 5, 15);

		}

		if (m_bJumpLock == false)
		{
			switch (m_nWeaponType)
			{
			case TYPE_SWORD:
				m_nMotionType[TYPE_SWORD] = S_MOVE;
				break;
			case TYPE_HAMMER:
				m_nMotionType[TYPE_HAMMER] = H_MOVE;
				break;
			}

		}
		m_rot.y = rot_y + 0.0f;

		m_pos.x = m_pos.x - sinf(rot_y)*fMoveSpeed;
		m_pos.z = m_pos.z - cosf(rot_y)*fMoveSpeed;

		m_bMove = true;
		m_fSoundInterval -= 0.1f;
	}

	else if (pXInput->GetGamePad()->m_state.Gamepad.sThumbLX >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		pXInput->GetGamePad()->m_state.Gamepad.sThumbLX <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		pXInput->GetGamePad()->m_state.Gamepad.sThumbLY <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		pXInput->GetGamePad()->m_state.Gamepad.sThumbLY >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		if (m_bJumpLock == false && m_bMotionStop == false&& m_bNeutral==false)
		{
			m_nEffectTimer = 0;
			switch (m_nWeaponType)
			{
			case TYPE_SWORD:
				m_nMotionType[TYPE_SWORD] = 0;
				break;
			case TYPE_HAMMER:
				m_nMotionType[TYPE_HAMMER] = 0;
				break;
			}

		}

		m_bMove = false;

	}

	if (m_bMove == true && m_fSoundInterval <= 0.0f && m_bJumpLock == false)
	{
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WALK);
		m_fSoundInterval = 2.0f;
	}

	SetPos(m_pos);
	SetScale(D3DXVECTOR3(20.0f, 20.0f, 20.0f));
}


bool  CPlayer::bColision()
{
	return 0;
}
