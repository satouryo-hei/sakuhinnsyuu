//=============================================================================
//
// �}�l�[�W���[���� [main.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;		
class CInputKeyboard;
class CCamera;
class CLight;
class CScene3D;
class CTexture;
class CEffect_Manager;

//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:
	CManager();											// �R���X�g���N�^
	~CManager();										// �f�X�g���N�^
														// �����o�֐�
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// �|���S���̏������֐�
	void Uninit(void);									// �|���S���̏I���֐��@
	void Update(void);									// �|���S���̍X�V�֐�
	void Draw(void);									// �|���S���̕`��֐�
	
	static CRenderer*GetRenderer(void){ return m_pRenderer; }
	static CInputKeyboard*GetInputKeyboard(void){ return m_pInputKeyboard; }
	static CScene3D*GetScene3D(void) { return m_pScene3D; }
	static CCamera*GetCamera(void) { return m_pCamera; }
	static CLight*GetLight(void) { return m_pLight[0]; }
	static CTexture*GetTexture(void) { return m_pTexture; }
	static CEffect_Manager*GetEffectManager(void) { return m_pEffect_Manager; }

private:												// �����������A�N�Z�X�\
	static CRenderer*m_pRenderer;						//�C���X�^���X����
	static CInputKeyboard*m_pInputKeyboard;
	static CScene3D * m_pScene3D;
	static CCamera * m_pCamera;
	static CLight * m_pLight[3];
	static CTexture * m_pTexture;
	static CEffect_Manager * m_pEffect_Manager;
};
#endif
