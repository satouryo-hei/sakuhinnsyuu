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

bool CImgui_Window::m_bUseWindow = true;
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

	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

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
	CManager * pManager = NULL;
	int nNumUI = pManager->GetUi_manager()->GetNumUI();

	int nMax = pManager->GetUi_manager()->GetMax();
	int nDiff = LIMITUI - nMax;

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
	ImGui::Text(u8"�ʒu��ύX�ł��邩[0]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�傫����ύX�ł��邩[9]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�ړ��ʂ�ύX�ł��邩[8]");		//���{��̐ݒ�i"u8=UTF-8"�j
	ImGui::Text(u8"�A�j���[�V�����ł��邩[7]");		//���{��̐ݒ�i"u8=UTF-8"�j
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

	ImGui::Begin(u8"UI���");
	bool bUse = pManager->GetUi_manager()->GetUse();
	static bool bMove = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolMove();

	if (bUse)
	{
		ImGui::Checkbox(u8"�ʒu�ύX", &bMove);
		if (bMove)
		{
			D3DXVECTOR3 Pos = pManager->GetUi_manager()->GetUi(nNumUI)->GetPos();
			ImGui::InputFloat3(u8"�ʒu", Pos);
			pManager->GetUi_manager()->GetUi(nNumUI)->SetPos(Pos);
		}

		static bool bSize = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolSize();
		ImGui::Checkbox(u8"�傫���ύX", &bSize);
		if (bSize)
		{
			D3DXVECTOR3 Size = pManager->GetUi_manager()->GetUi(nNumUI)->GetSize();
			ImGui::InputFloat2(u8"�傫��", Size);
			pManager->GetUi_manager()->GetUi(nNumUI)->SetSize(Size);
		}
		static bool bSpeed = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolSpeed();
		ImGui::Checkbox(u8"�ړ��ʕύX", &bSpeed);
		if (bSpeed)
		{
			D3DXVECTOR3 Move = pManager->GetUi_manager()->GetUi(nNumUI)->GetMove();
			ImGui::InputFloat3(u8"�ړ���", Move);
			pManager->GetUi_manager()->GetUi(nNumUI)->SetMove(Move);
		}
		ImGui::InputInt(u8"���݂̍ő��", &nMax);
		ImGui::InputInt(u8"���E�l�܂ł̌�", &nDiff);
	}
	ImGui::End();

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