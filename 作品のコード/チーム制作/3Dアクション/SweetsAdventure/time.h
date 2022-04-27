#ifndef _TIME_H_
#define _TIME_H_
#include "scene.h"
#include "Scene2D.h"
#include "texture.h"

#define MAX_TIME (3)//描画するポリゴン枚数

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
	void SetTime(void);//描画されているテクスチャの設定

private:
	int m_nTime;//現在の時間
	int m_nAddTime = 0;//60フレーム回ったら1秒減らす
	CScene2D *m_apScene2D[MAX_TIME];
};

#endif // !_TIME_H_*/


