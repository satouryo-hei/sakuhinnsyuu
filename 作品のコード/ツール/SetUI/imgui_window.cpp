//=============================================================================
//
// IMGUIのウィンドウ設定の処理 [imgui_window.cpp]
// Author : 佐藤瞭平
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
// コンストラクタ
//=======================================================
CImgui_Window::CImgui_Window()
{
}

//=======================================================
// デストラクタ
//=======================================================
CImgui_Window::~CImgui_Window()
{

}

//=======================================================
// 初期化処理
//=======================================================
HRESULT CImgui_Window::Init(HWND hWnd, bool bWindow)
{

	// IMGUIの設定
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();// UIの色設定

	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	return S_OK;
}


//=======================================================
// 終了処理
//=======================================================
void CImgui_Window::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//=======================================================
// 更新処理
//=======================================================
void CImgui_Window::Update(void)
{
	CManager * pManager = NULL;
	int nNumUI = pManager->GetUi_manager()->GetNumUI();

	int nMax = pManager->GetUi_manager()->GetMax();
	int nDiff = LIMITUI - nMax;

	//FPSを取得
	int nCountFPS = GetFPS();
	//  ImGuiフレームの開始
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// IMGUI開始
	ImGui::Begin(u8"操作方法"); // タイトルテキスト　日本語の設定（"u8=UTF-8"）			
	ImGui::Text(u8"UIの移動[WASD]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"UIの大きさ変更[QEZC]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"移動量の変更Xは[FH],Yは[TG]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"移動量の加減値は[R(0.1),Y(1.0)]に");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"位置を変更できるか[0]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"大きさを変更できるか[9]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"移動量を変更できるか[8]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"アニメーションできるか[7]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"最大数の増減[左矢印キー][右矢印キー]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"位置と大きさの初期化[SPACE]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"移動量の初期化[X]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"UIを配置[ENTER]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"[F6]ですべてのUIを前回のデータで配置");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"[F7]で現在のUIを前回のデータで配置");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"[F8]でロード");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"[F9]でセーブ");		//日本語の設定（"u8=UTF-8"）	
	ImGui::Separator();
	ImGui::Text(u8"ESCキーで終了");
	ImGui::End();// 終わり

	ImGui::Begin(u8"UI情報");
	bool bUse = pManager->GetUi_manager()->GetUse();
	static bool bMove = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolMove();

	if (bUse)
	{
		ImGui::Checkbox(u8"位置変更", &bMove);
		if (bMove)
		{
			D3DXVECTOR3 Pos = pManager->GetUi_manager()->GetUi(nNumUI)->GetPos();
			ImGui::InputFloat3(u8"位置", Pos);
			pManager->GetUi_manager()->GetUi(nNumUI)->SetPos(Pos);
		}

		static bool bSize = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolSize();
		ImGui::Checkbox(u8"大きさ変更", &bSize);
		if (bSize)
		{
			D3DXVECTOR3 Size = pManager->GetUi_manager()->GetUi(nNumUI)->GetSize();
			ImGui::InputFloat2(u8"大きさ", Size);
			pManager->GetUi_manager()->GetUi(nNumUI)->SetSize(Size);
		}
		static bool bSpeed = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolSpeed();
		ImGui::Checkbox(u8"移動量変更", &bSpeed);
		if (bSpeed)
		{
			D3DXVECTOR3 Move = pManager->GetUi_manager()->GetUi(nNumUI)->GetMove();
			ImGui::InputFloat3(u8"移動量", Move);
			pManager->GetUi_manager()->GetUi(nNumUI)->SetMove(Move);
		}
		ImGui::InputInt(u8"現在の最大個数", &nMax);
		ImGui::InputInt(u8"限界値までの個数", &nDiff);
	}
	ImGui::End();

	ImGui::EndFrame();// ImGuiフレームの終了
}

//=======================================================
// 描画処理
//=======================================================
void CImgui_Window::Draw(void)
{
	// ImGuiの描画
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}