//�t�F�[�h�̏���

#ifndef _FADE_H_
#define _FADE_H_
#include "scene.h"
#include "texture.h"
#include "manager.h"
class CScene2D;
class CBg;

class CFade : public CScene
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	} FADE;
	CFade(OBJTYPE nPriority = OBJTYPE_FADE);
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(CManager::MODE modeNext);
	FADE GetFade(void);
	static CFade *Create(CTexture::Type type,CManager::MODE modeNext);//�C���X�^���X��������
private:
	CTexture::Type				m_Type;
	static CBg							*m_pBg;
	static FADE					m_fade;			//�t�F�[�h�̏��
	static CManager::MODE		m_modeNext;		//���̉�ʁi���[�h�j
	static float				m_colorAlpha;	//�t�F�[�h�̐F

};
#endif // !_FADE_H_

