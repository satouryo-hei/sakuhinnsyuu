//--------------------------------------
//タイトルの処理
//--------------------------------------
#ifndef _GAME_H
#define _GAME_H
#include "main.h"
#include "scene.h"
//前方宣言
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
	static CField *m_pField;//床
	static CField *m_pSea;//床
	static 	CGauge *m_pGauge;
	static CPolygon *m_Polygon;
	static  CPolygon *m_Cursol;
	static CMeshSphere *m_pMeshSphere;
	static CEffectSphere *m_pEffectSphere;
	static CStage *m_pStage;
	static CEnemy *m_pEnemy;
	float m_fAlpha;
	bool				m_bNextMode;//二重押し防止変数
	int					m_nTimer;//カウンター
	CScene3D *m_pFlore;//床
};


#endif //_RESULT_H