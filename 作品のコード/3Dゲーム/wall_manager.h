//=============================================================================
//
// �ǂ̊Ǘ��̏��� [wall_manager.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _WALL_MANAGER_H_
#define _WALL_MANAGER_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_WALL (4)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CWall;

//*****************************************************************************
// �ǂ̊Ǘ��̃N���X
//*****************************************************************************
class CWall_Manager : public CScene
{
public:
	CWall_Manager(int nPriority = PRIORITY_NOMAL);										// �R���X�g���N�^
	~CWall_Manager();																	// �f�X�g���N�^

	// �����o�֐�
	static CWall_Manager *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);	// �ǂ̊Ǘ��̐���
	HRESULT Init(D3DXVECTOR3 pos);												// �ǂ̊Ǘ��̏������֐�
	void Uninit(void);															// �ǂ̊Ǘ��̏I���֐��@
	void Update(void);															// �ǂ̊Ǘ��̍X�V�֐�
	void Draw(void);															// �ǂ̊Ǘ��̕`��֐�


private:																		// �����������A�N�Z�X�\
	void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);			// �ǂ̐ݒ�
	// �����o�ϐ�
	static CWall * m_pWall[MAX_WALL];											// �ǂ̃|�C���^�[
	D3DXVECTOR3 m_pos;															// �ʒu
	D3DXVECTOR3 m_size;															// �傫��
	D3DXVECTOR3 m_rot;															// ����
};

//��Z����
template<class T, class P> T Multiplication(T data0, P data1)
{
	T answer;
	answer = data0 * data1;
	return answer;
}
#endif