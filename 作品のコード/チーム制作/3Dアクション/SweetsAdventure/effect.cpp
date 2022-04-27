#include "main.h"
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include <stdlib.h> // move, smove�֐�
#include <time.h>   // time�֐�

CEffect::CEffect(OBJTYPE nPriority) : CBillboard(nPriority)
{
}

CEffect::~CEffect()
{

}

//---------------------------------------------------
//�C���X�^���X����
//---------------------------------------------------
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col,float ScaleSpeed,CTexture::Type type)
{//	�ʒu, �ړ���, �T�C�Y,�F, �������Ȃ�X�s�[�h
	//�C���X�^���X����
	CEffect *pEffect = new CEffect(OBJTYPE_EFFECT);
	pEffect->m_pos = pos;
	pEffect->m_move = move;
	pEffect->m_size = size;
	pEffect->m_col = col;
	pEffect->m_fScaleSpeed = ScaleSpeed;

	if (pEffect != NULL)
	{
		//�摜�ǂݍ���
		pEffect->Init(type);
	}

	return pEffect;
}

//----------------------------------------------------
//����������
//-----------------------------------------------------
HRESULT CEffect::Init(CTexture::Type type)
{
	CBillboard::Init(type);
	m_fRand = float(rand() %314/100.0f) - float(rand() % 314 + 314/100.0f);//z�������_���ړ��p
	return S_OK;
}

HRESULT CEffect::Init()
{
	return S_OK;
}

//---------------------------------------------------------
//�I������
//---------------------------------------------------------
void CEffect::Uninit()
{
	CBillboard::Uninit();
}

void CEffect::Update()
{
	CBillboard::Setpos(m_pos, m_size);//���_���̐ݒ�
	CBillboard::SetColor(m_col);

	
	//�ړ�����
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += cosf(m_fRand);

	//�t���[���񃋂��ƂɃT�C�Y���������Ȃ�
	m_size.x -= m_fScaleSpeed;
	m_size.y -= m_fScaleSpeed;

	//���邳��������
	m_col.a -= 0.01;
	//m_col.g += 0.005;

	//X��Y�̃T�C�Y��0�ɂȂ��������
	if (m_size.x <= 0 && m_size.y <=0)
	{
		Uninit();
	}
	//���l��0�ȉ��ɂȂ����������
	if (m_col.a <= 0.0)
	{
		Uninit();
	}
}

void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//���u�����f�B���O��ʏ�ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

