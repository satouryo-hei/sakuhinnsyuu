//--------------------------------------
//�^�C�g���̏���
//--------------------------------------
#ifndef _TITLE_H
#define _TITLE_H
#include "main.h"
#include "scene.h"
#define MAX_TITLE_POLYGON (5)
//�O���錾
class CBg;
class CPolygon;
class CSound;
class CTitle
{
public:
	typedef enum
	{
		GAME_START=0,
		OPERATION,
		MAX,
	}TYPE;
	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NextMode(bool bNextMode) { m_bNextMode = bNextMode; }

private:
	CPolygon			*m_Polygon[MAX_TITLE_POLYGON];
	CPolygon			*m_Cursol;
	int					m_nSelectType;//�I�������^�C�v
	bool				m_bNextMode;//���̃��[�h�ɍs�����߂�
	bool				m_bOpra;//�`���[�g���A��UI��I�����Ă��邩
};


#endif //_TITLE_H