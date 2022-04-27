//=============================================================================
//
// �G�t�F�N�g�̊Ǘ��^�̏��� [effect_manager.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EFFECT_MANAGER_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _EFFECT_MANAGER_H_

#include"billeffect.h"
#include "texture.h"

#define EFFECTTEXT "data/TEXT/3DEffect.txt"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CStraight_Effect;		// �^�������̃G�t�F�N�g
class CCircle_Effect;		// �~�`�̃G�t�F�N�g
class CExplosion_Effect;	// �����̃G�t�F�N�g
class CDome_Effect;			// �h�[���^�̃G�t�F�N�g
class CWater_Crest_Effect;	// ����݂����Ȃ̃G�t�F�N�g
class CSmoke_Effect;		// ���̃G�t�F�N�g
class CLanding_Effect;		// ���n�̃G�t�F�N�g

//*****************************************************************************
// �G�t�F�N�g�̊Ǘ��^�N���X
//*****************************************************************************
class CEffect_Manager : public CBilleffect
{
public:										// �N�ł��A�N�Z�X�\

	//-----------------------------------------------------------------------------
	// �G�t�F�N�g�̎��
	//-----------------------------------------------------------------------------
	typedef enum
	{
		EffectType_NOMAL = 0,			// �Ȃ�
		EffectType_STRAIGHT,			// �^������
		EffectType_CIRCLE,				// �~�`
		EffectType_EXPLOSIN,			// ����
		EffectType_DOME,				// �h�[���^
		EffectType_WATER_CREST,			// ����̂悤��
		EffectType_SMOKE,				// ��
		EffectType_LANDING,				// ���n
		EffectType_MAX					// �ő吔
	} EffectType;

	//-----------------------------------------------------------------------------
	//�F�̎��
	//-----------------------------------------------------------------------------
	typedef enum
	{
		ColorType_RED = 0,				// ��
		ColorType_GREEN,				// ��
		ColorType_BLUE,					// ��
		ColorType_ARUFA,				// �����x
		ColorType_MAX					// �ő吔
	} ColorType;

	//-----------------------------------------------------------------------------
	//�x�N�g��3�̒��g�̎��(pos,size�Ȃ�)
	//-----------------------------------------------------------------------------
	typedef enum
	{
		Vector_X = 0,					// X
		Vector_Y,						// Y
		Vector_Z,						// Z
		Vector_MAX						// �ő吔
	} Vector3;


	CEffect_Manager(PRIORITY nPriority);									  // �R���X�g���N�^
	~CEffect_Manager();														  // �f�X�g���N�^
																			  
	// �v���g�^�C�v�錾
	static CEffect_Manager *Create(EffectType EffectType);					  // ����
	HRESULT Init(EffectType EffectType);									  // ������
	void Uninit(void);														  // �I��
	void Update(void);														  // �X�V
	void Draw(void);														  // �`��
	D3DXVECTOR3 GetPos(void) { return m_pos; }								  // �ʒu�̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; }							  // �ړ��ʂ̎擾
	D3DXVECTOR3 GetAddMove(void) { return m_Addmove; }						  // �v�Z����ړ��ʂ̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; }							  // �傫���̎擾
	D3DXVECTOR3 GetAddSize(void) { return m_AddSize; }						  // �v�Z����傫���̎擾
	D3DXCOLOR GetCol(void) { return m_col; }								  // �F�̎擾
	D3DXCOLOR GetAddCol(void) { return m_AddColor; }						  // �v�Z����F�̎擾
	int GetLife(void) { return m_nLife; }									  // �����̎擾
	int GetDensity(void) { return m_nDensity; }								  // ���x�̎擾
	int GetRadius(void) { return m_nRadius; }								  // ���a�̎擾
	int GetEffectType(void) { return m_nEffectType; }						  // �G�t�F�N�g�̎�ނ��擾
	int GetColorType(void) { return m_nColorType; }							  // �F�̎�ނ��擾
	int GetVectorType(void) { return m_nVecType; }							  // �x�N�g���̎�ނ��擾

private:									// �����������A�N�Z�X�\
	inline void Reset(void);
	inline void Save(void);
	inline void Lode(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;						// ���݂̈ʒu
	D3DXVECTOR3 m_rot;						// ��]��
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_Addmove;					// �v�Z����ړ���
	D3DXVECTOR3 m_size;						// �傫��
	D3DXVECTOR3 m_AddSize;					// �v�Z����傫��
	D3DXCOLOR m_col;						// �F
	D3DXCOLOR m_AddColor;					// �v�Z����F
	int m_nLife;							// ����
	int m_nDensity;							// ���x
	int m_nRadius;							// ���a
	int m_nEffectType;						// �G�t�F�N�g�̎��
	int m_nColorType;						// �F�̎��
	int m_nVecType;							// �ʒu��傫���Ȃǂ̎��
	bool m_bColorTrigger;					// �F�̑������g���K�[�ɂ��邩�ǂ���
	bool m_bVecTrigger;						// �ʒu��傫���Ȃǂ̑������g���K�[�ɂ��邩�ǂ���
	bool m_bEffectTrigger;
	const float m_fMaxSize;					// �傫���̍ő�l
	const float m_fMaxAddSize;				// �v�Z����傫���̍ő�l

	//-----------------------------------------------------------------------------
	// �ÓI�����o�ϐ�
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