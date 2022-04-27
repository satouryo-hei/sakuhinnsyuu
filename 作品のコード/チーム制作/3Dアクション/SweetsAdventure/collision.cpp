//---------------------------------------------------
//�w�i�̏���
//---------------------------------------------------
#include "collision.h"
#include "manager.h"
#include "Renderer.h"
#include "scene2D.h"
#include "model.h"
#include "model_spawner.h"
#include <math.h>
#include "field.h"
#include "Enemy.h"
#include "enemy_baum.h"
#include "player.h"
#include "barrier_block.h"
#include "barrier_wood.h"
//--------------------------
//�R���X�g���N�g
//----------------------------
CCollision::CCollision(OBJTYPE nPriority) :CScene(nPriority)
{
}

//--------------------------
//�f�X�g���N�g
//----------------------------
CCollision::~CCollision()
{

}

//--------------------------
//������
//----------------------------
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//--------------------------
//�I��
//----------------------------
void CCollision::Uninit(void)
{
	Release();
}

//--------------------------
//�X�V
//----------------------------
void CCollision::Update(void)
{
}

//--------------------------
//�`��
//----------------------------
void CCollision::Draw(void)
{

}

//---------------------------------------------------------------
//�����蔻��̐ݒ�i�����������鑤�Ƃ��Ďg���j
//---------------------------------------------------------------
bool CCollision::SetCollision(CScene *pHit_Side, CScene *pAttack_Side)
{
	if (pAttack_Side != NULL)
	{
		D3DXVECTOR3	HitScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����鑤�̑傫��
		D3DXVECTOR3	HitPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����鑤�̈ʒu
		D3DXVECTOR3	AttackScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���Ă鑤�̑傫��
		D3DXVECTOR3	AttackPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���Ă鑤�̈ʒu

		HitScale = pHit_Side->GetScale();			//�傫��
		HitPos = pHit_Side->GetPos();				//�ʒu
		AttackScale = pAttack_Side->GetScale();			//�傫��
		AttackPos = pAttack_Side->GetPos();				//�ʒu

		D3DXVECTOR3 vec = AttackPos - HitPos;

		float fLength = 0.0f;
		float fLength2 = 0.0f;

		//�v���C���[�ƓG�̋��������߂�
		fLength = sqrtf((vec.z*vec.z));
		fLength2 = sqrtf((vec.x*vec.x));


		//�����蔻��̏���
		if (fLength <= HitScale.z&&
			fLength2 <= HitScale.x)
		{
			//���������Ƃ��������Ԃ�
			return true;
		}

	}
	
	return false;
}
//=============================================================================
// ����f���̓����蔻��
//=============================================================================
void CCollision::CollisionObjectPlayer(CPlayer *Model, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius)
{
	CModel *pModel = Model->GetParts(0);
	CModel::ModelVtx Vtx[8];
	for (int nCntmodel = 0; nCntmodel < 8; nCntmodel++)
	{
		if (pModel != NULL)
		{
			Vtx[nCntmodel] = pModel->GetVtx(nCntmodel);

		}
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;
	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 NorAsk;
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 LongNorVec;
	D3DXVECTOR3 VecNorX;									//�����̒��_����
	D3DXVECTOR3 VecNorY;
	float fVecX[4];									//�����̒��_����
	float fVecY[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouY[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouY[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	NorAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LongNorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (pModel != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;
		Vtx[0].vtx.y -= fRadius;
		Vtx[1].vtx.y -= fRadius;
		Vtx[2].vtx.y -= fRadius;
		Vtx[3].vtx.y -= fRadius;
		//��
		Vtx[4].vtx.x -= fRadius;
		Vtx[4].vtx.z += fRadius;
		Vtx[5].vtx.x += fRadius;
		Vtx[5].vtx.z += fRadius;
		Vtx[6].vtx.x -= fRadius;
		Vtx[6].vtx.z -= fRadius;
		Vtx[7].vtx.x += fRadius;
		Vtx[7].vtx.z -= fRadius;
		Vtx[0].vtx.y += fRadius;
		Vtx[1].vtx.y += fRadius;
		Vtx[2].vtx.y += fRadius;
		Vtx[3].vtx.y += fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_MODEL_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
								 //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);
			mtxParent = pModel->GetMtxWorld();
			//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld,
				&Vtx[nNumVtx].mtxWorld,
				&mtxParent);
			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);
		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pPos->x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pPos->z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pPos->x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pPos->z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pPos->x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pPos->z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pPos->x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pPos->z - Vtx[2].mtxWorld._43;

		fVecYouY[0] = pPos->y - Vtx[0].mtxWorld._42;
		fVecYouY[1] = pPos->y - Vtx[1].mtxWorld._42;
		fVecYouY[2] = pPos->y - Vtx[3].mtxWorld._42;
		fVecYouY[3] = pPos->y - Vtx[2].mtxWorld._42;
		//�O�񂢂��n�_�̑���̈ʒu����x�N�g�������߂�
		fVecOldYouX[0] = pLastpos->x - Vtx[0].mtxWorld._41;
		fVecOldYouZ[0] = pLastpos->z - Vtx[0].mtxWorld._43;
		fVecOldYouX[1] = pLastpos->x - Vtx[1].mtxWorld._41;
		fVecOldYouZ[1] = pLastpos->z - Vtx[1].mtxWorld._43;
		fVecOldYouX[2] = pLastpos->x - Vtx[3].mtxWorld._41;
		fVecOldYouZ[2] = pLastpos->z - Vtx[3].mtxWorld._43;
		fVecOldYouX[3] = pLastpos->x - Vtx[2].mtxWorld._41;
		fVecOldYouZ[3] = pLastpos->z - Vtx[2].mtxWorld._43;

		fVecOldYouY[0] = pLastpos->y - Vtx[0].mtxWorld._42;
		fVecOldYouY[1] = pLastpos->y - Vtx[1].mtxWorld._42;
		fVecOldYouY[2] = pLastpos->y - Vtx[3].mtxWorld._42;
		fVecOldYouY[3] = pLastpos->y - Vtx[2].mtxWorld._42;

		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		fVecY[0] = Vtx[1].mtxWorld._42 - Vtx[0].mtxWorld._42;
		fVecY[1] = Vtx[3].mtxWorld._42 - Vtx[1].mtxWorld._42;
		fVecY[2] = Vtx[2].mtxWorld._42 - Vtx[3].mtxWorld._42;
		fVecY[3] = Vtx[0].mtxWorld._42 - Vtx[2].mtxWorld._42;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		//�@���x�N�g�������߂邽�߂̃x�N�g�������߂�
		if (fVecAsk[0] < 0.0f &&fVecOldAsk[0] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[4].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[4].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[4].mtxWorld._43 - Vtx[5].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[1].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[1].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[1].mtxWorld._43 - Vtx[5].mtxWorld._43);
		}
		else if (fVecAsk[1] < 0.0f &&fVecOldAsk[1] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[5].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[5].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[5].mtxWorld._43 - Vtx[7].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[3].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[3].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[3].mtxWorld._43 - Vtx[7].mtxWorld._43);
		}
		else if (fVecAsk[2] < 0.0f&&fVecOldAsk[2] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[7].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[7].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[7].mtxWorld._43 - Vtx[6].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[2].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[2].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[2].mtxWorld._43 - Vtx[6].mtxWorld._43);
		}
		else if (fVecAsk[3] < 0.0f && fVecOldAsk[3] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[6].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[6].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[6].mtxWorld._43 - Vtx[4].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[0].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[0].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[0].mtxWorld._43 - Vtx[4].mtxWorld._43);

		}
		//�@���x�N�g���̊O�ς̌v�Z
		D3DXVec3Cross(&NorAsk, &VecNorX, &VecNorY);
		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&NorAsk, &NorAsk);
		//�����Ă̌��݂̃|�X����ߋ��̃|�X�����߂�
		MoveVec = (*pPos) - (*pLastpos);
		//���ς����߂�
		NorMoveVecAsk = (-MoveVec.x*NorAsk.x) + (-MoveVec.y*NorAsk.y) + (-MoveVec.z*NorAsk.z);
		//�@����L�΂�
		LongNorVec = D3DXVECTOR3(NorAsk.x*NorMoveVecAsk, NorAsk.y*NorMoveVecAsk, NorAsk.z*NorMoveVecAsk);


		if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f) &&
			(fVecOldAsk[0] >= 0.0f || fVecOldAsk[1] >= 0.0f || fVecOldAsk[2] >= 0.0f || fVecOldAsk[3] >= 0.0f))
		{
			posVec = D3DXVECTOR3(LongNorVec.x + MoveVec.x, LongNorVec.y + MoveVec.y, LongNorVec.z + MoveVec.z);
			pPos->x = pLastpos->x;
			pPos->z = pLastpos->z;
			pPos->x += posVec.x;
			pPos->z += posVec.z;
		}

		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;
		Vtx[4].vtx.x += fRadius;
		Vtx[4].vtx.z -= fRadius;
		Vtx[5].vtx.x -= fRadius;
		Vtx[5].vtx.z -= fRadius;
		Vtx[6].vtx.x += fRadius;
		Vtx[6].vtx.z += fRadius;
		Vtx[7].vtx.x -= fRadius;
		Vtx[7].vtx.z += fRadius;

	}

}

//=============================================================================
// ����f���̓����蔻��
//=============================================================================
void CCollision::CollisionObjectEnemy(CEnemy *Model, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius)
{
	CModel *pModel = Model->GetModel(0);
	CModel::ModelVtx Vtx[8];
	for (int nCntmodel = 0; nCntmodel < 8; nCntmodel++)
	{
		if (pModel != NULL)
		{
			Vtx[nCntmodel] = pModel->GetVtx(nCntmodel);

		}
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;
	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 NorAsk;
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 LongNorVec;
	D3DXVECTOR3 VecNorX;									//�����̒��_����
	D3DXVECTOR3 VecNorY;
	float fVecX[4];									//�����̒��_����
	float fVecY[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouY[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouY[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	NorAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LongNorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (pModel != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;
		Vtx[0].vtx.y -= fRadius;
		Vtx[1].vtx.y -= fRadius;
		Vtx[2].vtx.y -= fRadius;
		Vtx[3].vtx.y -= fRadius;
		//��
		Vtx[4].vtx.x -= fRadius;
		Vtx[4].vtx.z += fRadius;
		Vtx[5].vtx.x += fRadius;
		Vtx[5].vtx.z += fRadius;
		Vtx[6].vtx.x -= fRadius;
		Vtx[6].vtx.z -= fRadius;
		Vtx[7].vtx.x += fRadius;
		Vtx[7].vtx.z -= fRadius;
		Vtx[0].vtx.y += fRadius;
		Vtx[1].vtx.y += fRadius;
		Vtx[2].vtx.y += fRadius;
		Vtx[3].vtx.y += fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_MODEL_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
								 //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);
			mtxParent = pModel->GetMtxWorld();
			//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld,
				&Vtx[nNumVtx].mtxWorld,
				&mtxParent);
			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);
		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pPos->x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pPos->z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pPos->x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pPos->z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pPos->x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pPos->z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pPos->x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pPos->z - Vtx[2].mtxWorld._43;

		fVecYouY[0] = pPos->y - Vtx[0].mtxWorld._42;
		fVecYouY[1] = pPos->y - Vtx[1].mtxWorld._42;
		fVecYouY[2] = pPos->y - Vtx[3].mtxWorld._42;
		fVecYouY[3] = pPos->y - Vtx[2].mtxWorld._42;
		//�O�񂢂��n�_�̑���̈ʒu����x�N�g�������߂�
		fVecOldYouX[0] = pLastpos->x - Vtx[0].mtxWorld._41;
		fVecOldYouZ[0] = pLastpos->z - Vtx[0].mtxWorld._43;
		fVecOldYouX[1] = pLastpos->x - Vtx[1].mtxWorld._41;
		fVecOldYouZ[1] = pLastpos->z - Vtx[1].mtxWorld._43;
		fVecOldYouX[2] = pLastpos->x - Vtx[3].mtxWorld._41;
		fVecOldYouZ[2] = pLastpos->z - Vtx[3].mtxWorld._43;
		fVecOldYouX[3] = pLastpos->x - Vtx[2].mtxWorld._41;
		fVecOldYouZ[3] = pLastpos->z - Vtx[2].mtxWorld._43;

		fVecOldYouY[0] = pLastpos->y - Vtx[0].mtxWorld._42;
		fVecOldYouY[1] = pLastpos->y - Vtx[1].mtxWorld._42;
		fVecOldYouY[2] = pLastpos->y - Vtx[3].mtxWorld._42;
		fVecOldYouY[3] = pLastpos->y - Vtx[2].mtxWorld._42;

		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		fVecY[0] = Vtx[1].mtxWorld._42 - Vtx[0].mtxWorld._42;
		fVecY[1] = Vtx[3].mtxWorld._42 - Vtx[1].mtxWorld._42;
		fVecY[2] = Vtx[2].mtxWorld._42 - Vtx[3].mtxWorld._42;
		fVecY[3] = Vtx[0].mtxWorld._42 - Vtx[2].mtxWorld._42;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		//�@���x�N�g�������߂邽�߂̃x�N�g�������߂�
		if (fVecAsk[0] < 0.0f &&fVecOldAsk[0] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[4].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[4].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[4].mtxWorld._43 - Vtx[5].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[1].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[1].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[1].mtxWorld._43 - Vtx[5].mtxWorld._43);
		}
		else if (fVecAsk[1] < 0.0f &&fVecOldAsk[1] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[5].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[5].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[5].mtxWorld._43 - Vtx[7].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[3].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[3].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[3].mtxWorld._43 - Vtx[7].mtxWorld._43);
		}
		else if (fVecAsk[2] < 0.0f&&fVecOldAsk[2] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[7].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[7].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[7].mtxWorld._43 - Vtx[6].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[2].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[2].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[2].mtxWorld._43 - Vtx[6].mtxWorld._43);
		}
		else if (fVecAsk[3] < 0.0f && fVecOldAsk[3] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[6].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[6].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[6].mtxWorld._43 - Vtx[4].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[0].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[0].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[0].mtxWorld._43 - Vtx[4].mtxWorld._43);

		}
		//�@���x�N�g���̊O�ς̌v�Z
		D3DXVec3Cross(&NorAsk, &VecNorX, &VecNorY);
		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&NorAsk, &NorAsk);
		//�����Ă̌��݂̃|�X����ߋ��̃|�X�����߂�
		MoveVec = (*pPos) - (*pLastpos);
		//���ς����߂�
		NorMoveVecAsk = (-MoveVec.x*NorAsk.x) + (-MoveVec.y*NorAsk.y) + (-MoveVec.z*NorAsk.z);
		//�@����L�΂�
		LongNorVec = D3DXVECTOR3(NorAsk.x*NorMoveVecAsk, NorAsk.y*NorMoveVecAsk, NorAsk.z*NorMoveVecAsk);


		if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f) &&
			(fVecOldAsk[0] >= 0.0f || fVecOldAsk[1] >= 0.0f || fVecOldAsk[2] >= 0.0f || fVecOldAsk[3] >= 0.0f))
		{
			posVec = D3DXVECTOR3(LongNorVec.x + MoveVec.x, LongNorVec.y + MoveVec.y, LongNorVec.z + MoveVec.z);
			pPos->x = pLastpos->x;
			pPos->z = pLastpos->z;
			pPos->x += posVec.x;
			pPos->z += posVec.z;
		}

		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;
		Vtx[4].vtx.x += fRadius;
		Vtx[4].vtx.z -= fRadius;
		Vtx[5].vtx.x -= fRadius;
		Vtx[5].vtx.z -= fRadius;
		Vtx[6].vtx.x += fRadius;
		Vtx[6].vtx.z += fRadius;
		Vtx[7].vtx.x -= fRadius;
		Vtx[7].vtx.z += fRadius;

	}

}
//=============================================================================
// ����f���̓����蔻��
//=============================================================================
void CCollision::CollisionObjectEnemy(CEnemy_Baum *Model, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius)
{
	CModel *pModel = Model->GetModel(0);
	CModel::ModelVtx Vtx[8];
	for (int nCntmodel = 0; nCntmodel < 8; nCntmodel++)
	{
		if (pModel != NULL)
		{
			Vtx[nCntmodel] = pModel->GetVtx(nCntmodel);

		}
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;
	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 NorAsk;
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 LongNorVec;
	D3DXVECTOR3 VecNorX;									//�����̒��_����
	D3DXVECTOR3 VecNorY;
	float fVecX[4];									//�����̒��_����
	float fVecY[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouY[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouY[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	NorAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LongNorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (pModel != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;
		Vtx[0].vtx.y -= fRadius;
		Vtx[1].vtx.y -= fRadius;
		Vtx[2].vtx.y -= fRadius;
		Vtx[3].vtx.y -= fRadius;
		//��
		Vtx[4].vtx.x -= fRadius;
		Vtx[4].vtx.z += fRadius;
		Vtx[5].vtx.x += fRadius;
		Vtx[5].vtx.z += fRadius;
		Vtx[6].vtx.x -= fRadius;
		Vtx[6].vtx.z -= fRadius;
		Vtx[7].vtx.x += fRadius;
		Vtx[7].vtx.z -= fRadius;
		Vtx[0].vtx.y += fRadius;
		Vtx[1].vtx.y += fRadius;
		Vtx[2].vtx.y += fRadius;
		Vtx[3].vtx.y += fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_MODEL_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
								 //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);
			mtxParent = pModel->GetMtxWorld();
			//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld,
				&Vtx[nNumVtx].mtxWorld,
				&mtxParent);
			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);
		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pPos->x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pPos->z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pPos->x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pPos->z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pPos->x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pPos->z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pPos->x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pPos->z - Vtx[2].mtxWorld._43;

		fVecYouY[0] = pPos->y - Vtx[0].mtxWorld._42;
		fVecYouY[1] = pPos->y - Vtx[1].mtxWorld._42;
		fVecYouY[2] = pPos->y - Vtx[3].mtxWorld._42;
		fVecYouY[3] = pPos->y - Vtx[2].mtxWorld._42;
		//�O�񂢂��n�_�̑���̈ʒu����x�N�g�������߂�
		fVecOldYouX[0] = pLastpos->x - Vtx[0].mtxWorld._41;
		fVecOldYouZ[0] = pLastpos->z - Vtx[0].mtxWorld._43;
		fVecOldYouX[1] = pLastpos->x - Vtx[1].mtxWorld._41;
		fVecOldYouZ[1] = pLastpos->z - Vtx[1].mtxWorld._43;
		fVecOldYouX[2] = pLastpos->x - Vtx[3].mtxWorld._41;
		fVecOldYouZ[2] = pLastpos->z - Vtx[3].mtxWorld._43;
		fVecOldYouX[3] = pLastpos->x - Vtx[2].mtxWorld._41;
		fVecOldYouZ[3] = pLastpos->z - Vtx[2].mtxWorld._43;

		fVecOldYouY[0] = pLastpos->y - Vtx[0].mtxWorld._42;
		fVecOldYouY[1] = pLastpos->y - Vtx[1].mtxWorld._42;
		fVecOldYouY[2] = pLastpos->y - Vtx[3].mtxWorld._42;
		fVecOldYouY[3] = pLastpos->y - Vtx[2].mtxWorld._42;

		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		fVecY[0] = Vtx[1].mtxWorld._42 - Vtx[0].mtxWorld._42;
		fVecY[1] = Vtx[3].mtxWorld._42 - Vtx[1].mtxWorld._42;
		fVecY[2] = Vtx[2].mtxWorld._42 - Vtx[3].mtxWorld._42;
		fVecY[3] = Vtx[0].mtxWorld._42 - Vtx[2].mtxWorld._42;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		//�@���x�N�g�������߂邽�߂̃x�N�g�������߂�
		if (fVecAsk[0] < 0.0f &&fVecOldAsk[0] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[4].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[4].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[4].mtxWorld._43 - Vtx[5].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[1].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[1].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[1].mtxWorld._43 - Vtx[5].mtxWorld._43);
		}
		else if (fVecAsk[1] < 0.0f &&fVecOldAsk[1] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[5].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[5].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[5].mtxWorld._43 - Vtx[7].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[3].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[3].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[3].mtxWorld._43 - Vtx[7].mtxWorld._43);
		}
		else if (fVecAsk[2] < 0.0f&&fVecOldAsk[2] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[7].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[7].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[7].mtxWorld._43 - Vtx[6].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[2].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[2].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[2].mtxWorld._43 - Vtx[6].mtxWorld._43);
		}
		else if (fVecAsk[3] < 0.0f && fVecOldAsk[3] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[6].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[6].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[6].mtxWorld._43 - Vtx[4].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[0].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[0].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[0].mtxWorld._43 - Vtx[4].mtxWorld._43);

		}
		//�@���x�N�g���̊O�ς̌v�Z
		D3DXVec3Cross(&NorAsk, &VecNorX, &VecNorY);
		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&NorAsk, &NorAsk);
		//�����Ă̌��݂̃|�X����ߋ��̃|�X�����߂�
		MoveVec = (*pPos) - (*pLastpos);
		//���ς����߂�
		NorMoveVecAsk = (-MoveVec.x*NorAsk.x) + (-MoveVec.y*NorAsk.y) + (-MoveVec.z*NorAsk.z);
		//�@����L�΂�
		LongNorVec = D3DXVECTOR3(NorAsk.x*NorMoveVecAsk, NorAsk.y*NorMoveVecAsk, NorAsk.z*NorMoveVecAsk);


		if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f) &&
			(fVecOldAsk[0] >= 0.0f || fVecOldAsk[1] >= 0.0f || fVecOldAsk[2] >= 0.0f || fVecOldAsk[3] >= 0.0f))
		{
			posVec = D3DXVECTOR3(LongNorVec.x + MoveVec.x, LongNorVec.y + MoveVec.y, LongNorVec.z + MoveVec.z);
			pPos->x = pLastpos->x;
			pPos->z = pLastpos->z;
			pPos->x += posVec.x;
			pPos->z += posVec.z;
		}

		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;
		Vtx[4].vtx.x += fRadius;
		Vtx[4].vtx.z -= fRadius;
		Vtx[5].vtx.x -= fRadius;
		Vtx[5].vtx.z -= fRadius;
		Vtx[6].vtx.x += fRadius;
		Vtx[6].vtx.z += fRadius;
		Vtx[7].vtx.x -= fRadius;
		Vtx[7].vtx.z += fRadius;

	}

}
//=============================================================================
// ����f���̓����蔻��
//=============================================================================
CCollision::COLLISION_TYPE CCollision::CollisionObjectModelShadow(CModel_Spawner *Model, D3DXVECTOR3 *pPos, float fRadius, float& fModelPos_Y)
{
	CModel *pModel = Model->GetModel();
	CModel::ModelVtx Vtx[8];
	for (int nCntmodel = 0; nCntmodel < 8; nCntmodel++)
	{
		if (pModel != NULL)
		{
			Vtx[nCntmodel] = pModel->GetVtx(nCntmodel);

		}
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;
	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 NorAsk;
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 LongNorVec;
	D3DXVECTOR3 VecNorX;									//�����̒��_����
	D3DXVECTOR3 VecNorY;
	float fVecX[4];									//�����̒��_����
	float fVecY[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouY[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouY[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	NorAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LongNorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (pModel != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;
		Vtx[0].vtx.y -= fRadius;
		Vtx[1].vtx.y -= fRadius;
		Vtx[2].vtx.y -= fRadius;
		Vtx[3].vtx.y -= fRadius;
		//��
		Vtx[4].vtx.x -= fRadius;
		Vtx[4].vtx.z += fRadius;
		Vtx[5].vtx.x += fRadius;
		Vtx[5].vtx.z += fRadius;
		Vtx[6].vtx.x -= fRadius;
		Vtx[6].vtx.z -= fRadius;
		Vtx[7].vtx.x += fRadius;
		Vtx[7].vtx.z -= fRadius;
		Vtx[0].vtx.y += fRadius;
		Vtx[1].vtx.y += fRadius;
		Vtx[2].vtx.y += fRadius;
		Vtx[3].vtx.y += fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_MODEL_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
								 //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);
			mtxParent = pModel->GetMtxWorld();
			//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld,
				&Vtx[nNumVtx].mtxWorld,
				&mtxParent);
			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);
		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pPos->x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pPos->z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pPos->x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pPos->z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pPos->x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pPos->z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pPos->x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pPos->z - Vtx[2].mtxWorld._43;

		fVecYouY[0] = pPos->y - Vtx[0].mtxWorld._42;
		fVecYouY[1] = pPos->y - Vtx[1].mtxWorld._42;
		fVecYouY[2] = pPos->y - Vtx[3].mtxWorld._42;
		fVecYouY[3] = pPos->y - Vtx[2].mtxWorld._42;

		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		fVecY[0] = Vtx[1].mtxWorld._42 - Vtx[0].mtxWorld._42;
		fVecY[1] = Vtx[3].mtxWorld._42 - Vtx[1].mtxWorld._42;
		fVecY[2] = Vtx[2].mtxWorld._42 - Vtx[3].mtxWorld._42;
		fVecY[3] = Vtx[0].mtxWorld._42 - Vtx[2].mtxWorld._42;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		//�@���x�N�g�������߂邽�߂̃x�N�g�������߂�
		if (fVecAsk[0] < 0.0f &&fVecOldAsk[0] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[4].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[4].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[4].mtxWorld._43 - Vtx[5].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[1].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[1].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[1].mtxWorld._43 - Vtx[5].mtxWorld._43);
		}
		else if (fVecAsk[1] < 0.0f &&fVecOldAsk[1] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[5].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[5].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[5].mtxWorld._43 - Vtx[7].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[3].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[3].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[3].mtxWorld._43 - Vtx[7].mtxWorld._43);
		}
		else if (fVecAsk[2] < 0.0f&&fVecOldAsk[2] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[7].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[7].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[7].mtxWorld._43 - Vtx[6].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[2].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[2].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[2].mtxWorld._43 - Vtx[6].mtxWorld._43);
		}
		else if (fVecAsk[3] < 0.0f && fVecOldAsk[3] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[6].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[6].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[6].mtxWorld._43 - Vtx[4].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[0].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[0].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[0].mtxWorld._43 - Vtx[4].mtxWorld._43);

		}
		//�@���x�N�g���̊O�ς̌v�Z
		D3DXVec3Cross(&NorAsk, &VecNorX, &VecNorY);
		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&NorAsk, &NorAsk);
		//���ς����߂�
		NorMoveVecAsk = (-MoveVec.x*NorAsk.x) + (-MoveVec.y*NorAsk.y) + (-MoveVec.z*NorAsk.z);
		//�@����L�΂�
		LongNorVec = D3DXVECTOR3(NorAsk.x*NorMoveVecAsk, NorAsk.y*NorMoveVecAsk, NorAsk.z*NorMoveVecAsk);

		//��̃|���S���ɓ������Ƃ�
		if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f))
		{
			fModelPos_Y = Vtx[0].mtxWorld._42;
			return COLLISION_UP;
		}


		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;
		Vtx[4].vtx.x += fRadius;
		Vtx[4].vtx.z -= fRadius;
		Vtx[5].vtx.x -= fRadius;
		Vtx[5].vtx.z -= fRadius;
		Vtx[6].vtx.x += fRadius;
		Vtx[6].vtx.z += fRadius;
		Vtx[7].vtx.x -= fRadius;
		Vtx[7].vtx.z += fRadius;

	}
	return COLLISION_NONE;
}
//=============================================================================
// ����f���̓����蔻��
//=============================================================================
bool CCollision::CollisionFieldShadow(CField *field, D3DXVECTOR3 *pPos, float fRadius, float& fModelPos_Y)
{
	CField::FieldVtx Vtx[4];
	for (int nCntmodel = 0; nCntmodel < 4; nCntmodel++)
	{
		Vtx[nCntmodel] = field->GetVtx(nCntmodel);
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;

	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 Fieldpos = field->GetPos();
	float fVecX[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (field != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_FIELD_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
												  //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x + Fieldpos.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z + Fieldpos.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);

			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);

		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pPos->x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pPos->z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pPos->x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pPos->z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pPos->x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pPos->z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pPos->x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pPos->z - Vtx[2].mtxWorld._43;


		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		if (pPos->y >= Fieldpos.y)
		{
			//��̃|���S���ɓ������Ƃ�
			if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f))
			{
				fModelPos_Y = Fieldpos.y;
				return true;
			}
		}

		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;

	}
	return false;
}

//=============================================================================
// ����f���̓����蔻��
//=============================================================================
CCollision::COLLISION_TYPE CCollision::CollisionObjectModel(CModel_Spawner *Model, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius, float& fModelPos_Y)
{
	CModel *pModel = Model->GetModel();
	CModel::ModelVtx Vtx[8];
	for (int nCntmodel = 0; nCntmodel < 8; nCntmodel++)
	{
		if (pModel != NULL)
		{
			Vtx[nCntmodel] = pModel->GetVtx(nCntmodel);

		}
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;
	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 NorAsk;
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 LongNorVec;
	D3DXVECTOR3 VecNorX;									//�����̒��_����
	D3DXVECTOR3 VecNorY;
	float fVecX[4];									//�����̒��_����
	float fVecY[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouY[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouY[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	NorAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LongNorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (pModel != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;
		Vtx[0].vtx.y -= fRadius;
		Vtx[1].vtx.y -= fRadius;
		Vtx[2].vtx.y -= fRadius;
		Vtx[3].vtx.y -= fRadius;
		//��
		Vtx[4].vtx.x -= fRadius;
		Vtx[4].vtx.z += fRadius;
		Vtx[5].vtx.x += fRadius;
		Vtx[5].vtx.z += fRadius;
		Vtx[6].vtx.x -= fRadius;
		Vtx[6].vtx.z -= fRadius;
		Vtx[7].vtx.x += fRadius;
		Vtx[7].vtx.z -= fRadius;
		Vtx[0].vtx.y += fRadius;
		Vtx[1].vtx.y += fRadius;
		Vtx[2].vtx.y += fRadius;
		Vtx[3].vtx.y += fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_MODEL_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
								 //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);
			mtxParent = pModel->GetMtxWorld();
			//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld,
				&Vtx[nNumVtx].mtxWorld,
				&mtxParent);
			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);
		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pPos->x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pPos->z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pPos->x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pPos->z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pPos->x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pPos->z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pPos->x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pPos->z - Vtx[2].mtxWorld._43;

		fVecYouY[0] = pPos->y - Vtx[0].mtxWorld._42;
		fVecYouY[1] = pPos->y - Vtx[1].mtxWorld._42;
		fVecYouY[2] = pPos->y - Vtx[3].mtxWorld._42;
		fVecYouY[3] = pPos->y - Vtx[2].mtxWorld._42;
		//�O�񂢂��n�_�̑���̈ʒu����x�N�g�������߂�
		fVecOldYouX[0] = pLastpos->x - Vtx[0].mtxWorld._41;
		fVecOldYouZ[0] = pLastpos->z - Vtx[0].mtxWorld._43;
		fVecOldYouX[1] = pLastpos->x - Vtx[1].mtxWorld._41;
		fVecOldYouZ[1] = pLastpos->z - Vtx[1].mtxWorld._43;
		fVecOldYouX[2] = pLastpos->x - Vtx[3].mtxWorld._41;
		fVecOldYouZ[2] = pLastpos->z - Vtx[3].mtxWorld._43;
		fVecOldYouX[3] = pLastpos->x - Vtx[2].mtxWorld._41;
		fVecOldYouZ[3] = pLastpos->z - Vtx[2].mtxWorld._43;

		fVecOldYouY[0] = pLastpos->y - Vtx[0].mtxWorld._42;
		fVecOldYouY[1] = pLastpos->y - Vtx[1].mtxWorld._42;
		fVecOldYouY[2] = pLastpos->y - Vtx[3].mtxWorld._42;
		fVecOldYouY[3] = pLastpos->y - Vtx[2].mtxWorld._42;

		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		fVecY[0] = Vtx[1].mtxWorld._42 - Vtx[0].mtxWorld._42;
		fVecY[1] = Vtx[3].mtxWorld._42 - Vtx[1].mtxWorld._42;
		fVecY[2] = Vtx[2].mtxWorld._42 - Vtx[3].mtxWorld._42;
		fVecY[3] = Vtx[0].mtxWorld._42 - Vtx[2].mtxWorld._42;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		//�@���x�N�g�������߂邽�߂̃x�N�g�������߂�
		if (fVecAsk[0] < 0.0f &&fVecOldAsk[0] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[4].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[4].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[4].mtxWorld._43 - Vtx[5].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[1].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[1].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[1].mtxWorld._43 - Vtx[5].mtxWorld._43);
		}
		else if (fVecAsk[1] < 0.0f &&fVecOldAsk[1] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[5].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[5].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[5].mtxWorld._43 - Vtx[7].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[3].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[3].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[3].mtxWorld._43 - Vtx[7].mtxWorld._43);
		}
		else if (fVecAsk[2] < 0.0f&&fVecOldAsk[2] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[7].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[7].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[7].mtxWorld._43 - Vtx[6].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[2].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[2].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[2].mtxWorld._43 - Vtx[6].mtxWorld._43);
		}
		else if (fVecAsk[3] < 0.0f && fVecOldAsk[3] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[6].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[6].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[6].mtxWorld._43 - Vtx[4].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[0].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[0].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[0].mtxWorld._43 - Vtx[4].mtxWorld._43);

		}
		//�@���x�N�g���̊O�ς̌v�Z
		D3DXVec3Cross(&NorAsk, &VecNorX, &VecNorY);
		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&NorAsk, &NorAsk);
		//�����Ă̌��݂̃|�X����ߋ��̃|�X�����߂�
		MoveVec = (*pPos) - (*pLastpos);
		//���ς����߂�
		NorMoveVecAsk = (-MoveVec.x*NorAsk.x) + (-MoveVec.y*NorAsk.y) + (-MoveVec.z*NorAsk.z);
		//�@����L�΂�
		LongNorVec = D3DXVECTOR3(NorAsk.x*NorMoveVecAsk, NorAsk.y*NorMoveVecAsk, NorAsk.z*NorMoveVecAsk);
		
		if (pPos->y <= Vtx[0].mtxWorld._42&&pLastpos->y>=Vtx[0].mtxWorld._42)
		{
			//��̃|���S���ɓ������Ƃ�
			if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f) && pLastpos->y>Vtx[0].mtxWorld._42)
			{
				pPos->y = Vtx[0].mtxWorld._42;
				fModelPos_Y = Vtx[0].mtxWorld._42;
				return COLLISION_UP;
			}
		}
		else if(pPos->y <= Vtx[0].mtxWorld._42&&pLastpos->y <= Vtx[0].mtxWorld._42)
		{
			if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f) &&
				(fVecOldAsk[0] >= 0.0f || fVecOldAsk[1] >= 0.0f || fVecOldAsk[2] >= 0.0f || fVecOldAsk[3] >= 0.0f))
			{
				posVec = D3DXVECTOR3(LongNorVec.x + MoveVec.x, LongNorVec.y + MoveVec.y, LongNorVec.z + MoveVec.z);
				pPos->x = pLastpos->x;
				pPos->z = pLastpos->z;
				pPos->x += posVec.x;
				pPos->z += posVec.z;
				return COLLISION_NONE;
			}
		}
		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;
		Vtx[4].vtx.x += fRadius;
		Vtx[4].vtx.z -= fRadius;
		Vtx[5].vtx.x -= fRadius;
		Vtx[5].vtx.z -= fRadius;
		Vtx[6].vtx.x += fRadius;
		Vtx[6].vtx.z += fRadius;
		Vtx[7].vtx.x -= fRadius;
		Vtx[7].vtx.z += fRadius;

	}
	return COLLISION_NONE;
}
//=============================================================================
// ����f���̓����蔻��
//=============================================================================
bool CCollision::CollisionWeapon(CEnemy_Baum *Model, D3DXVECTOR3 pos, float fRadius)
{
	D3DXVECTOR3	scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale.x = 40.0f;			//�傫��
	D3DXVECTOR3	r_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	r_pos = Model->GetEnemyPos();				//�ʒu
	D3DXVECTOR3 BulletVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BulletVec = r_pos - pos;			//�G�ƒe�̃x�N�g��
	float fLengthX = 0.0f;
	float fLengthZ = 0.0f;

	fLengthX = sqrtf((BulletVec.x*BulletVec.x));
	fLengthZ = sqrtf((BulletVec.z*BulletVec.z));




	//��̃|���S���ɓ������Ƃ�
	if (fLengthX <=(fRadius)&& fLengthZ<= fRadius)
	{
		return true;
	}
	return false;
}
//=============================================================================
// ����f���̓����蔻��
//=============================================================================
bool CCollision::CollisionWeapon(CEnemy *Model, D3DXVECTOR3 pos, float fRadius)
{
	D3DXVECTOR3	scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale.x = 30.0f;			//�傫��
	D3DXVECTOR3	r_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	r_pos = Model->GetEnemyPos();				//�ʒu
	D3DXVECTOR3 BulletVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BulletVec = r_pos - pos;			//�G�ƒe�̃x�N�g��
	float fLengthX = 0.0f;
	float fLengthZ = 0.0f;

	fLengthX = sqrtf((BulletVec.x*BulletVec.x));
	fLengthZ = sqrtf((BulletVec.z*BulletVec.z));




	//��̃|���S���ɓ������Ƃ�
	if (fLengthX <= (fRadius) && fLengthZ <= fRadius)
	{
		return true;
	}
	return false;
}
//=============================================================================
// ����f���̓����蔻��
//=============================================================================
bool CCollision::CollisionWeaponBarrier(CModel_Spawner *Model, D3DXVECTOR3 pos, float fRadius)
{
	CModel *pModel = Model->GetModel();
	CModel::ModelVtx Vtx[8];
	for (int nCntmodel = 0; nCntmodel < 8; nCntmodel++)
	{
		if (pModel != NULL)
		{
			Vtx[nCntmodel] = pModel->GetVtx(nCntmodel);

		}
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;
	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 NorAsk;
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 LongNorVec;
	D3DXVECTOR3 VecNorX;									//�����̒��_����
	D3DXVECTOR3 VecNorY;
	float fVecX[4];									//�����̒��_����
	float fVecY[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouY[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouY[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	NorAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LongNorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorX = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VecNorY = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (pModel != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;
		Vtx[0].vtx.y -= fRadius;
		Vtx[1].vtx.y -= fRadius;
		Vtx[2].vtx.y -= fRadius;
		Vtx[3].vtx.y -= fRadius;
		//��
		Vtx[4].vtx.x -= fRadius;
		Vtx[4].vtx.z += fRadius;
		Vtx[5].vtx.x += fRadius;
		Vtx[5].vtx.z += fRadius;
		Vtx[6].vtx.x -= fRadius;
		Vtx[6].vtx.z -= fRadius;
		Vtx[7].vtx.x += fRadius;
		Vtx[7].vtx.z -= fRadius;
		Vtx[0].vtx.y += fRadius;
		Vtx[1].vtx.y += fRadius;
		Vtx[2].vtx.y += fRadius;
		Vtx[3].vtx.y += fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_MODEL_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
								 //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);
			mtxParent = pModel->GetMtxWorld();
			//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld,
				&Vtx[nNumVtx].mtxWorld,
				&mtxParent);
			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);
		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pos.x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pos.z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pos.x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pos.z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pos.x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pos.z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pos.x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pos.z - Vtx[2].mtxWorld._43;

		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		fVecY[0] = Vtx[1].mtxWorld._42 - Vtx[0].mtxWorld._42;
		fVecY[1] = Vtx[3].mtxWorld._42 - Vtx[1].mtxWorld._42;
		fVecY[2] = Vtx[2].mtxWorld._42 - Vtx[3].mtxWorld._42;
		fVecY[3] = Vtx[0].mtxWorld._42 - Vtx[2].mtxWorld._42;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		//�@���x�N�g�������߂邽�߂̃x�N�g�������߂�
		if (fVecAsk[0] < 0.0f &&fVecOldAsk[0] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[4].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[4].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[4].mtxWorld._43 - Vtx[5].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[1].mtxWorld._41 - Vtx[5].mtxWorld._41,
				Vtx[1].mtxWorld._42 - Vtx[5].mtxWorld._42,
				Vtx[1].mtxWorld._43 - Vtx[5].mtxWorld._43);
		}
		else if (fVecAsk[1] < 0.0f &&fVecOldAsk[1] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[5].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[5].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[5].mtxWorld._43 - Vtx[7].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[3].mtxWorld._41 - Vtx[7].mtxWorld._41,
				Vtx[3].mtxWorld._42 - Vtx[7].mtxWorld._42,
				Vtx[3].mtxWorld._43 - Vtx[7].mtxWorld._43);
		}
		else if (fVecAsk[2] < 0.0f&&fVecOldAsk[2] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[7].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[7].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[7].mtxWorld._43 - Vtx[6].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[2].mtxWorld._41 - Vtx[6].mtxWorld._41,
				Vtx[2].mtxWorld._42 - Vtx[6].mtxWorld._42,
				Vtx[2].mtxWorld._43 - Vtx[6].mtxWorld._43);
		}
		else if (fVecAsk[3] < 0.0f && fVecOldAsk[3] >= 0.0f)
		{
			VecNorX = D3DXVECTOR3(Vtx[6].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[6].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[6].mtxWorld._43 - Vtx[4].mtxWorld._43);
			VecNorY = D3DXVECTOR3(Vtx[0].mtxWorld._41 - Vtx[4].mtxWorld._41,
				Vtx[0].mtxWorld._42 - Vtx[4].mtxWorld._42,
				Vtx[0].mtxWorld._43 - Vtx[4].mtxWorld._43);

		}
		//�@���x�N�g���̊O�ς̌v�Z
		D3DXVec3Cross(&NorAsk, &VecNorX, &VecNorY);
		//�x�N�g���𐳋K��
		D3DXVec3Normalize(&NorAsk, &NorAsk);
		//���ς����߂�
		NorMoveVecAsk = (-MoveVec.x*NorAsk.x) + (-MoveVec.y*NorAsk.y) + (-MoveVec.z*NorAsk.z);
		//�@����L�΂�
		LongNorVec = D3DXVECTOR3(NorAsk.x*NorMoveVecAsk, NorAsk.y*NorMoveVecAsk, NorAsk.z*NorMoveVecAsk);

		if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f))
		{
			return COLLISION_UP;
		}
		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;
		Vtx[4].vtx.x += fRadius;
		Vtx[4].vtx.z -= fRadius;
		Vtx[5].vtx.x -= fRadius;
		Vtx[5].vtx.z -= fRadius;
		Vtx[6].vtx.x += fRadius;
		Vtx[6].vtx.z += fRadius;
		Vtx[7].vtx.x -= fRadius;
		Vtx[7].vtx.z += fRadius;

	}
	return false;
}

//=============================================================================
// ����f���̓����蔻��
//=============================================================================
bool CCollision::CollisionField(CField *field, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius, float& fModelPos_Y)
{
	CField::FieldVtx Vtx[4];
	for (int nCntmodel = 0; nCntmodel < 4; nCntmodel++)
	{
		Vtx[nCntmodel] = field->GetVtx(nCntmodel);
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	D3DXVECTOR3 MoveVec;
	float NorMoveVecAsk;

	float fVecAsk[4];
	float fVecOldAsk[4];
	D3DXVECTOR3 posVec;
	D3DXVECTOR3 Fieldpos= field->GetPos();
	float fVecX[4];									//�����̒��_����
	float fVecZ[4];
	float fVecYouX[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecYouZ[4];								//���肩�玩���̒��_�̃x�N�g��
	float fVecOldYouX[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fVecOldYouZ[4];							//�ߋ��ɂ����n�_�̑��肩�玩���̒��_�̃x�N�g��
	float fOldVecX[8];
	float fOldVecZ[8];
	MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NorMoveVecAsk = 0.0f;
	//���[�J���ϐ��̏�����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fVecAsk[nCnt] = 0.0f;
		fVecOldAsk[nCnt] = 0.0f;
		fVecX[nCnt] = 0.0f;
		fVecZ[nCnt] = 0.0f;
		fVecYouX[nCnt] = 0.0f;
		fVecYouZ[nCnt] = 0.0f;
		fVecOldYouX[nCnt] = 0.0f;
		fVecOldYouZ[nCnt] = 0.0f;
	}
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		fOldVecX[nCnt] = 0.0f;
		fOldVecZ[nCnt] = 0.0f;
	}
	if (field != NULL)
	{

		//�q��pos�𑊎�̕������₷
		//��
		Vtx[0].vtx.x -= fRadius;
		Vtx[0].vtx.z += fRadius;
		Vtx[1].vtx.x += fRadius;
		Vtx[1].vtx.z += fRadius;
		Vtx[2].vtx.x -= fRadius;
		Vtx[2].vtx.z -= fRadius;
		Vtx[3].vtx.x += fRadius;
		Vtx[3].vtx.z -= fRadius;


		//���̂���}�g���b�N�X�ɔ��f������
		for (int nNumVtx = 0; nNumVtx < MAX_FIELD_VTX; nNumVtx++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
								 //�e���_�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Vtx[nNumVtx].mtxWorld);
			////�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, Vtx[nNumVtx].rot.y, Vtx[nNumVtx].rot.x, Vtx[nNumVtx].rot.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxRotModel);
			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTransModel, Vtx[nNumVtx].vtx.x+ Fieldpos.x, Vtx[nNumVtx].vtx.y, Vtx[nNumVtx].vtx.z+ Fieldpos.z);
			D3DXMatrixMultiply(&Vtx[nNumVtx].mtxWorld, &Vtx[nNumVtx].mtxWorld, &mtxTransModel);

			//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &Vtx[nNumVtx].mtxWorld);

		}

		//����̈ʒu����x�N�g�������߂�
		fVecYouX[0] = pPos->x - Vtx[0].mtxWorld._41;
		fVecYouZ[0] = pPos->z - Vtx[0].mtxWorld._43;
		fVecYouX[1] = pPos->x - Vtx[1].mtxWorld._41;
		fVecYouZ[1] = pPos->z - Vtx[1].mtxWorld._43;
		fVecYouX[2] = pPos->x - Vtx[3].mtxWorld._41;
		fVecYouZ[2] = pPos->z - Vtx[3].mtxWorld._43;
		fVecYouX[3] = pPos->x - Vtx[2].mtxWorld._41;
		fVecYouZ[3] = pPos->z - Vtx[2].mtxWorld._43;

		//�O�񂢂��n�_�̑���̈ʒu����x�N�g�������߂�
		fVecOldYouX[0] = pLastpos->x - Vtx[0].mtxWorld._41;
		fVecOldYouZ[0] = pLastpos->z - Vtx[0].mtxWorld._43;
		fVecOldYouX[1] = pLastpos->x - Vtx[1].mtxWorld._41;
		fVecOldYouZ[1] = pLastpos->z - Vtx[1].mtxWorld._43;
		fVecOldYouX[2] = pLastpos->x - Vtx[3].mtxWorld._41;
		fVecOldYouZ[2] = pLastpos->z - Vtx[3].mtxWorld._43;
		fVecOldYouX[3] = pLastpos->x - Vtx[2].mtxWorld._41;
		fVecOldYouZ[3] = pLastpos->z - Vtx[2].mtxWorld._43;

		//���_�ƒ��_�̊Ԃ̃x�N�g�����߂�
		fVecX[0] = Vtx[1].mtxWorld._41 - Vtx[0].mtxWorld._41;
		fVecX[1] = Vtx[3].mtxWorld._41 - Vtx[1].mtxWorld._41;
		fVecX[2] = Vtx[2].mtxWorld._41 - Vtx[3].mtxWorld._41;
		fVecX[3] = Vtx[0].mtxWorld._41 - Vtx[2].mtxWorld._41;
		fVecZ[0] = Vtx[1].mtxWorld._43 - Vtx[0].mtxWorld._43;
		fVecZ[1] = Vtx[3].mtxWorld._43 - Vtx[1].mtxWorld._43;
		fVecZ[2] = Vtx[2].mtxWorld._43 - Vtx[3].mtxWorld._43;
		fVecZ[3] = Vtx[0].mtxWorld._43 - Vtx[2].mtxWorld._43;

		//�O�ς̌v�Z
		fVecAsk[0] = (fVecX[0] * fVecYouZ[0]) - (fVecYouX[0] * fVecZ[0]);
		fVecAsk[1] = (fVecX[1] * fVecYouZ[1]) - (fVecYouX[1] * fVecZ[1]);
		fVecAsk[2] = (fVecX[2] * fVecYouZ[2]) - (fVecYouX[2] * fVecZ[2]);
		fVecAsk[3] = (fVecX[3] * fVecYouZ[3]) - (fVecYouX[3] * fVecZ[3]);

		fVecOldAsk[0] = (fVecX[0] * fVecOldYouZ[0]) - (fVecOldYouX[0] * fVecZ[0]);
		fVecOldAsk[1] = (fVecX[1] * fVecOldYouZ[1]) - (fVecOldYouX[1] * fVecZ[1]);
		fVecOldAsk[2] = (fVecX[2] * fVecOldYouZ[2]) - (fVecOldYouX[2] * fVecZ[2]);
		fVecOldAsk[3] = (fVecX[3] * fVecOldYouZ[3]) - (fVecOldYouX[3] * fVecZ[3]);

		if (pPos->y <= Fieldpos.y&&pLastpos->y >= Fieldpos.y)
		{
			//��̃|���S���ɓ������Ƃ�
			if ((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f))
			{
				pPos->y = Fieldpos.y;
				fModelPos_Y = Fieldpos.y;
				return true;
			}
		}

		//�q��pos�𑊎�̕������炷
		Vtx[0].vtx.x += fRadius;
		Vtx[0].vtx.z -= fRadius;
		Vtx[1].vtx.x -= fRadius;
		Vtx[1].vtx.z -= fRadius;
		Vtx[2].vtx.x += fRadius;
		Vtx[2].vtx.z += fRadius;
		Vtx[3].vtx.x -= fRadius;
		Vtx[3].vtx.z += fRadius;

	}
	return false;
}
