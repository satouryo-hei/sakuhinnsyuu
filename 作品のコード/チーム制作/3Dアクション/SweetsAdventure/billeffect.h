#ifndef _BILLEFFECT_H_
#define _BILLEFFECT_H_
#include "main.h"
#include "scene.h"
#include "texture.h"

class CBilleffect : public CScene
{
public:
	CBilleffect(OBJTYPE nPriority = OBJTYPE_NONE);
	~CBilleffect();
	static CBilleffect *Create(D3DXVECTOR3 size);
	HRESULT Init(CTexture::Type type = CTexture::Effect);
	HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void BindTexture(CTexture::Type type);			//画像の設定
	void Setposition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//頂点情報設定
	void SetColor(D3DXCOLOR col);

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;									//ワールドマトリックス	
	D3DXMATRIX m_mtxView;									//ビューマトリックス
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;										//ポリゴンサイズ
	D3DXCOLOR m_col;

};
#endif // !_BILLBOARD_H_