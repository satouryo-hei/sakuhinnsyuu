//=============================================================================
//
// IMGUI�̃E�B���h�E�ݒ�̏��� [imgui_window.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"imgui_window.h"
#include"renderer.h"
#include"manager.h"
#include"ui_manager.h"
#include"ui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

//=======================================================
// �R���X�g���N�^
//=======================================================
CImgui_Window::CImgui_Window()
{
}

//=======================================================
// �f�X�g���N�^
//=======================================================
CImgui_Window::~CImgui_Window()
{

}

//=======================================================
// ����������
//=======================================================
HRESULT CImgui_Window::Init(HWND hWnd, bool bWindow)
{

	// IMGUI�̐ݒ�
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();// UI�̐F�ݒ�

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	return S_OK;
}


//=======================================================
// �I������
//=======================================================
void CImgui_Window::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//=======================================================
// �X�V����
//=======================================================
void CImgui_Window::Update(void)
{		
	// ���݂̐����擾
	int nNumUI = CManager::GetUi_manager()->GetNumUI();

	//FPS���擾
	int nCountFPS = GetFPS();
	//  ImGui�t���[���̊J�n
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// IMGUI�J�n
	ImGui::Begin(u8"������@"); // �^�C�g���e�L�X�g�@���{��̐ݒ�i"u8=UTF-8"�j			
	ImGui::Text(u8"UI�̈ړ�[WASD]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"UI�̑傫���ύX[QEZC]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ړ��ʂ̕ύXX��[FH],Y��[TG]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ړ��ʂ̉����l��[R(0.1),Y(1.0)]��");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ʒu��ύX�ł��邩[F1]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�傫����ύX�ł��邩[F2]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ړ��ʂ�ύX�ł��邩[F3]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�A�j���[�V�����ł��邩[F4]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ő吔�̑���[�����L�[][�E���L�[]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ʒu�Ƒ傫���̏�����[SPACE]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ړ��ʂ̏�����[X]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"UI��z�u[ENTER]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"[F6]�ł��ׂĂ�UI��O��̃f�[�^�Ŕz�u");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"[F7]�Ō��݂�UI��O��̃f�[�^�Ŕz�u");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"[F8]�Ń��[�h");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"[F9]�ŃZ�[�u");		//���{��̐ݒ�i"u8=UTF-8"�j	
	ImGui::Separator();
	ImGui::Text(u8"ESC�L�[�ŏI��");
	ImGui::End();// �I���

	// IMGUI�J�n
	ImGui::Begin(u8"UI���"); //�^�C�g���e�L�X�g

	// �g�p���Ă��邩�ǂ����̎擾
	bool bUse = CManager::GetUi_manager()->GetUse();

	if (bUse)
	{
		// �ړ��ł��邩
		bool bMove = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolMove();
		ImGui::Checkbox(u8"�ʒu�ύX", &bMove);

		// �ړ��ł���Ȃ�
		if (bMove)
		{
			// ���݂̈ʒu���擾����
			D3DXVECTOR3 Pos = CManager::GetUi_manager()->GetUi(nNumUI)->GetPos();
			ImGui::InputFloat3(u8"�ʒu", Pos);

			// ���݂̈ʒu��ݒ肷��
			CManager::GetUi_manager()->GetUi(nNumUI)->SetPos(Pos);
		}
		// // �ړ��ł��邩�̐ݒ������
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolMove(bMove);

		// �傫���ύX�ł��邩
		bool bSize = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolSize();
		ImGui::Checkbox(u8"�傫���ύX", &bSize);
		// �ł���Ȃ�
		if (bSize)
		{
			// �傫�����擾����
			D3DXVECTOR3 Size = CManager::GetUi_manager()->GetUi(nNumUI)->GetSize();
			ImGui::InputFloat2(u8"�傫��", Size);
			// �傫����ݒ������
			CManager::GetUi_manager()->GetUi(nNumUI)->SetSize(Size);
		}
		// �傫���ύX�ł��邩�̐ݒ������
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolSize(bSize);

		// �ړ��ʂ̕ύX���ł��邩
		bool bSpeed = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolSpeed();
		ImGui::Checkbox(u8"�ړ��ʕύX", &bSpeed);
		// �ł���Ȃ�
		if (bSpeed)
		{
			// �ړ��ʂ��擾����
			D3DXVECTOR3 Move = CManager::GetUi_manager()->GetUi(nNumUI)->GetMove();
			ImGui::InputFloat3(u8"�ړ���", Move);
			// �ړ��ʂ�ݒ������
			CManager::GetUi_manager()->GetUi(nNumUI)->SetMove(Move);
		}
		// �ړ��ʂ̕ύX���ł��邩�̐ݒ������
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolSpeed(bSpeed);

		// �ő���̎擾������
		int nMax = CManager::GetUi_manager()->GetMax();
		ImGui::InputInt(u8"���݂̍ő��", &nMax);

		// �ő���̐ݒ������
		CManager::GetUi_manager()->SetMax(nMax);

		// ���݂̃e�N�X�`�����擾����
		int nTex = CManager::GetUi_manager()->GetUi(nNumUI)->GetTex();
		ImGui::InputInt(u8"���݂̃e�N�X�`��", &nTex);

		// ���݂̃e�N�X�`����ݒ肷��
		CManager::GetUi_manager()->GetUi(nNumUI)->SetTex(nTex);

		ImGui::Text(u8"�`�`�`�`�`�R�R����ύX�s�`�`�`�`�`");

		// �������v�Z
		int nDiff = LIMITUI - nMax;
		ImGui::InputInt(u8"���E�l�܂ł̌�", &nDiff);		
		ImGui::InputInt(u8"���݂̌�", &nNumUI);
	}
	ImGui::End();//�I���

	ImGui::EndFrame();// ImGui�t���[���̏I��
}

//=======================================================
// �`�揈��
//=======================================================
void CImgui_Window::Draw(void)
{
	// ImGui�̕`��
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}