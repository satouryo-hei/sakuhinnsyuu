#ifndef _SCORE_H_
#define _SCORE_H_
#include "scene.h"
class CScene2D;
#define MAX_SCORE (3)//�ő�`�文��


class CScore : public CScene
{
public:
	CScore(OBJTYPE nPriority = OBJTYPE_NONE);
	~CScore();
	static CScore*Create(D3DXVECTOR3 pos, float fsize);
	HRESULT Init(D3DXVECTOR3 pos, float fsize);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(void);//�X�R�A�̕`��ݒ�
	static void AddScore(int AddScore) { m_nScore += AddScore; };//�X�R�A�̉��Z
private:
	CScene2D *m_apScene2D[MAX_SCORE];
	int m_nAddScore;//�X�R�A���Z�p�ϐ�
	static int m_nScore;//���݂̃X�R�A
};
#endif
