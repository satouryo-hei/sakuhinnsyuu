//=============================================================================
//
// �X�e�[�^�X��UI�̏��� [status_ui.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _STATUS_UI_H_
#define _STATUS_UI_H_

#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CNumber;

//*****************************************************************************
// �X�e�[�^�X��UI�̃N���X
//*****************************************************************************
class CStatus_UI : public CScene
{
public:
	typedef enum
	{
		STAUI_BACK = 0,
		STAUI_STATUS,
		STAUI_ATTACK,
		STAUI_MAX
	} STAUI;

	CStatus_UI(int nPriority = PRIORITY_NOMAL);									// �R���X�g���N�^
	~CStatus_UI();																// �f�X�g���N�^

																				// �����o�֐�
	static CStatus_UI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// �����L���O�̐���
	HRESULT Init(D3DXVECTOR3 pos);												// �X�e�[�^�X��UI�̏������֐�
	void Uninit(void);															// �X�e�[�^�X��UI�̏I���֐��@
	void Update(void);															// �X�e�[�^�X��UI�̍X�V�֐�
	void Draw(void);															// �X�e�[�^�X��UI�̕`��֐�
	void SetStatusNumber(const int nStatus);

private:																		// �����������A�N�Z�X�\
	inline void LodeStatusUI();
	static const char *m_pStatusUIFlieName;												// 
	static const int m_nStatusNumber;												// 
	static CPolygon * m_pPolygon[STAUI_MAX];											// �|���S���N���X�̃|�C���^
	static CNumber * m_apNumber[2];												// �ԍ��N���X�̃|�C���^
	D3DXVECTOR2 m_Size;
	D3DXVECTOR3 m_LodePos[STAUI_MAX];
	D3DXVECTOR2 m_LodeSize[STAUI_MAX];
	int m_nStatus;
};

#endif