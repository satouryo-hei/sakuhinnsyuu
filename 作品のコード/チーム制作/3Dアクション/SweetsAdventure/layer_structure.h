//===================================================
//階層構造の設定をするクラス
//===================================================
#ifndef _LAYER_STRUCTURE_H
#define _LAYER_STRUCTURE_H

class CModel;

class CLayer_Structure
{
#define MAX_LAYER_PARTS (20)

public:
	CLayer_Structure();
	~CLayer_Structure();
	void SetLayer_Structure(const char *sFileName, CModel **apModel);
	int	 GetMaxParts(void) { return m_MaxParts; }
	//D3DXVECTOR3 GetPos( int nNumModel) { return m_pos[nNumModel]; }
	//D3DXVECTOR3 GetRot( int nNumModel) { return m_rot[nNumModel]; }
private:
	int		m_MaxParts;//パーツの最大数
//	D3DXVECTOR3 m_pos[MAX_LAYER_PARTS];
//	D3DXVECTOR3 m_rot[MAX_LAYER_PARTS];

};


#endif // !_LAYER_STRUCTURE_H

