#ifndef _TIME_H_
#define _TIME_H_
#include "scene.h"
#include "Scene2D.h"
#include "texture.h"

#define MAX_TIME (3)//�`�悷��|���S������

class CTime : public CScene
{
public:
	CTime(OBJTYPE nPriority = OBJTYPE_UI);
	~CTime();
	static CTime*Create(D3DXVECTOR3 pos, float fsize);
	HRESULT Init(D3DXVECTOR3 pos,float fsize);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTime(void);//�`�悳��Ă���e�N�X�`���̐ݒ�

private:
	int m_nTime;//���݂̎���
	int m_nAddTime = 0;//60�t���[���������1�b���炷
	CScene2D *m_apScene2D[MAX_TIME];
};

#endif // !_TIME_H_*/


