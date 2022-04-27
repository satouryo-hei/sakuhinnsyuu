//--------------------------------------
//�^�C�g���̏���
//--------------------------------------
#ifndef _GAME_H
#define _GAME_H
#include "main.h"
#include "scene.h"
//�O���錾
class CBg;
class CPlayer;
class CScene3D;
class CTime;
class CModel_Spawner;
class CScore;
class CGoal;
class CField;
class CMeshSphere;
class CEffectSphere;
class CStage;
class CEnemy;
class CGauge;
class CPolygon;

class CGame
{
public:
	typedef enum
	{
		LEVEL_EASY=0,
		LEVEL_NORMAL,
		LEVEL_HARD,
		LEVEL_MAX
	}LEVEL;
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *GetPlayer(void) { return m_Player; }
	static CModel_Spawner *GetModel(void) { return m_pModel; }
	static CScore			*GetScore(void) { return m_pScore; }
	static CGoal			*GetGoal(void) { return m_pGoal; }
	static CMeshSphere		*GetMeshSphere(void) { return m_pMeshSphere; }
	static CStage		*GetStage(void) { return m_pStage; }
	static CEnemy		*GetEnemy(void) { return m_pEnemy; }
	static CGauge		*GetGauge(void) { return m_pGauge; }
	static CPolygon		*GetCursol(void) { return m_Cursol; }

private:
	static CScore		*m_pScore;
	static CBg			*m_pBg;
	static CPlayer		*m_Player;
	static CTime *m_pTime;
	static CModel_Spawner *m_pModel;
	static CGoal *m_pGoal;
	static CField *m_pField;//��
	static CField *m_pSea;//��
	static 	CGauge *m_pGauge;
	static CPolygon *m_Polygon;
	static  CPolygon *m_Cursol;
	static CMeshSphere *m_pMeshSphere;
	static CEffectSphere *m_pEffectSphere;
	static CStage *m_pStage;
	static CEnemy *m_pEnemy;
	float m_fAlpha;
	bool				m_bNextMode;//��d�����h�~�ϐ�
	int					m_nTimer;//�J�E���^�[
	CScene3D *m_pFlore;//��
};


#endif //_RESULT_H