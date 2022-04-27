//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : �H������
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
public:
	CTexture();	// �f�t�H���g�R���X�g���N�^
	~CTexture();// �f�t�H���g�f�X�g���N�^
	typedef enum
	{
		None = -1,		// �e�N�X�`������
		Text,			// ���e�N�X�`��
		TIME,			// �^�C���i���o�[
		FADE,			
		HAMMERTEX,		//HAMMER�̉摜
		NAIHUTEX,		//�i�C�t�̉摜
		FREAM,			//�g
		WEAPONSELECT,	//�����I������J�[�\��
		LB,
		RB,
		GOAL,
		SEA000,			//�C
		SEA001,			//�C
		SHADOW,			//�e
		FIELD,			//��
		SKY,			//��
		Title,			//�^�C�g���w�i
		GameOver,		//�Q�[���I�[�o�[�w�i
		Titlelogo,		//�^�C�g�����S
		GameStart,		//�Q�[���X�^�[�g
		Gameover000,	//�Q�[���I�[�o�[���S
		GameClear000,	//�Q�[���N���A���S
		GameClear001,	//�Q�[���N���A���S
		Cursol,			//�J�[�\��
		Retry,			//���g���C
		Texture001,		//�^�C�g���ɖ߂�
		GameBack,		//�Q�[���ɖ߂�
		a000,			//�i�C�t
		Gage003,		//�U�f�Q�[�W�A�C�R��
		Gage001,		//�U�f�Q�[�W
		Gage002,		//�Q�[�W
		Hammer000,		//�n���}�[
		Naifu000,		//�i�C�t
		Operation,		//�`���[�g���A��
		Operation01,
		Ranking000,		//�����L���O
		Effect,			//�G�t�F�N�g
		Max,			// �e�N�X�`���̍ő吔
	} Type;

	void Init(void);	// �e�N�X�`���̐���
	LPDIRECT3DTEXTURE9 GetTexture(Type Type) { return m_pTexture[Type]; }	// �e�N�X�`���̊��蓖��(�e�N�X�`���̎��) { return �I�񂾃e�N�X�`����Ԃ� }
	void Uniinit(void);	// �I��

private:
	LPDIRECT3DTEXTURE9	m_pTexture[Max];	//�e�N�X�`��
};

#endif