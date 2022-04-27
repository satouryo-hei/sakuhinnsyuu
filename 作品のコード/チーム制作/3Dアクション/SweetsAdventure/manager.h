//--------------------------------------
//�}�l�[�W���[�̏���
//--------------------------------------
#ifndef _MANAGER_H
#define _MANAGER_H
#include "main.h"

//�O���錾
class CInputKeyBoard;
class CRenderer;
class CTexture;
class CCamera;
class CLight;
class CModel;
class CPlayer;
class CModel_Spawner;
class CTitle;
class CGame;
class CFade;
class CResult;
class CXInput;
class CMouse;
class CSound;

class CManager
{
public:
	typedef enum
	{
		MODE_TITLE=0,			//�^�C�g�����
		MODE_GAME,				//�Q�[�����
		MODE_RESULT,			//���U���g���
		MODE_MAX
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyBoard *GetInputKeyboard(void);
	static CTexture *GetTexture(void);
	static CFade *GetFade(void)								{ return m_Fade; }
	static CGame *GetGame(void)								{ return m_pGame; }
	static void SetMode(MODE mode);						//���[�h�̐ݒ�
	static MODE GetMode(void);
	static bool GetPause(void) { return m_bPause; }
	static void SetPause(bool bPause,bool bStop = false)	{ m_bPause = bPause;m_bStop = bStop;}
	static void SetEnd(bool bEnd)							{ m_bEnd = bEnd;}
	static CXInput *GetXInput(void)							{ return m_XInput; }
	static CCamera *GetCamera(void)							{ return m_pCamera; }
	static CMouse *GetMouse(void)							{ return m_Mouse; }
	static CSound *GetSound(void)							{ return m_pSound; }
	static bool GetClear(void)								{ return m_bClear; }
	static void SetClear(bool bClear)						{ m_bClear = bClear; }
private:
	static CRenderer		*m_pRenderer;
	static CInputKeyBoard	*m_pInputKeyboard;
	static CXInput			*m_XInput;
	static CTexture			*m_pTexture;
	static bool			m_bStop;
	static bool			m_bPause;
	static bool			m_bEnd;
	static CCamera			*m_pCamera;
	static CLight			*m_pLight[3];
	static CPlayer			*m_pPlayer;
	static CModel_Spawner	*m_pModel;
	static CTitle			*m_pTitle;
	static CGame			*m_pGame;
	static CResult			*m_pResult;
	static MODE			m_Mode;				//���݂̃��[�h
	static CFade			*m_Fade;
	static CMouse			*m_Mouse;
	static CSound			*m_pSound;
	static bool	m_bClear;					//�N���A�������̔���
};


#endif //_MANAGER_H