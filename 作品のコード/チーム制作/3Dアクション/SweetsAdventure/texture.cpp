//=============================================================================
//
// �e�N�X�`������ [texture.cpp]
// Author : �H�������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "Renderer.h"
#include "manager.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����

	D3DXCreateTextureFromFile(pDevice,
		"",	// ����
		&m_pTexture[None]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/text_texture.png",//���e�N�X�`��
		&m_pTexture[Text]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Flag.png",//���e�N�X�`��
		&m_pTexture[GOAL]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",//����
		&m_pTexture[TIME]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/fade.png",//����
		&m_pTexture[FADE]);
	//---------------------------------
	//����̑I��
	//---------------------------------
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Hammer000.png",//����
		&m_pTexture[HAMMERTEX]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Naifu000.png",//����
		&m_pTexture[NAIHUTEX]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Frame_Black.png",//����
		&m_pTexture[FREAM]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Frame0.png",//����
		&m_pTexture[WEAPONSELECT]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/LB.png",//����
		&m_pTexture[LB]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/RB.png",//����
		&m_pTexture[RB]);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sky_loop001.png",//��
		&m_pTexture[SKY]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/floor001.png",//�C1
		&m_pTexture[SEA000]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/floor.png",//�C�Q
		&m_pTexture[SEA001]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",//�e
		&m_pTexture[SHADOW]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",//�G�t�F�N�g
		&m_pTexture[Effect]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Tyoko.png",//��	
		&m_pTexture[FIELD]);
	//============================================================
	//�^�C�g��
	//============================================================
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Title000.png",//�^�C�g���w�i
		&m_pTexture[Title]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Titlelogo.png",//�^�C�g�����S
		&m_pTexture[Titlelogo]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GameStart.png",//�Q�[���X�^�[�g
		&m_pTexture[GameStart]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Operation.png",//�`���[�g���A��
		&m_pTexture[Operation]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Ranking000.png",//�����L���O
		&m_pTexture[Ranking000]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/002.png",		  //�J�[�\��
		&m_pTexture[Cursol]);

	//============================================================
	//�Q�[���I�[�o�[
	//============================================================
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameover.png",//�Q�[���I�[�o�[�w�i
		&m_pTexture[GameOver]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Gameover000.png",//�Q�[���I�[�o�[���S
		&m_pTexture[Gameover000]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameclear002.png",//�Q�[���N���A�w�i
		&m_pTexture[GameClear000]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameclear003.png",//�Q�[���I�[�o�[���S
		&m_pTexture[GameClear001]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Retry.png",//���g���C
		&m_pTexture[Retry]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Texture001.png",//�^�C�g���ɖ߂�
		&m_pTexture[Texture001]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ReturnGame.png",//�^�C�g���ɖ߂�
		&m_pTexture[GameBack]);
	//============================================================
	//�Q�[�����
	//============================================================
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAUGE/icon.png",//�U�f�Q�[�W
		&m_pTexture[Gage003]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAUGE/Gage.png",//�U�f�Q�[�W
		&m_pTexture[Gage001]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAUGE/Gage002.png",//�Q�[�W
		&m_pTexture[Gage002]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Naifu000.png",//��
		&m_pTexture[Naifu000]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Hammer000.png",//�n���}�[
		&m_pTexture[Hammer000]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/000.png",//�n���}�[
		&m_pTexture[a000]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Tutorial000.png",//�`���[�g���A�����
		&m_pTexture[Operation01]);



}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uniinit(void)
{
	for (int nCntTexture = 0; nCntTexture < Max; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}