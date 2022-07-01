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

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
	// 現在の数を取得
	int nNumUI = CManager::GetUi_manager()->GetNumUI();

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
	ImGui::Text(u8"位置を変更できるか[F1]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"大きさを変更できるか[F2]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"移動量を変更できるか[F3]");		//日本語の設定（"u8=UTF-8"）
	ImGui::Text(u8"アニメーションできるか[F4]");		//日本語の設定（"u8=UTF-8"）
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

	// IMGUI開始
	ImGui::Begin(u8"UI情報");
	bool bUse = CManager::GetUi_manager()->GetUse();

	if (bUse)
	{
		bool bMove = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolMove();
		ImGui::Checkbox(u8"位置変更", &bMove);
		if (bMove)
		{
			D3DXVECTOR3 Pos = CManager::GetUi_manager()->GetUi(nNumUI)->GetPos();
			ImGui::InputFloat3(u8"位置", Pos);
			CManager::GetUi_manager()->GetUi(nNumUI)->SetPos(Pos);
		}
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolMove(bMove);

		bool bSize = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolSize();
		ImGui::Checkbox(u8"大きさ変更", &bSize);
		if (bSize)
		{
			D3DXVECTOR3 Size = CManager::GetUi_manager()->GetUi(nNumUI)->GetSize();
			ImGui::InputFloat2(u8"大きさ", Size);
			CManager::GetUi_manager()->GetUi(nNumUI)->SetSize(Size);
		}
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolSize(bSize);

		bool bSpeed = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolSpeed();
		ImGui::Checkbox(u8"移動量変更", &bSpeed);
		if (bSpeed)
		{
			D3DXVECTOR3 Move = CManager::GetUi_manager()->GetUi(nNumUI)->GetMove();
			ImGui::InputFloat3(u8"移動量", Move);
			CManager::GetUi_manager()->GetUi(nNumUI)->SetMove(Move);
		}
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolSpeed(bSpeed);

		int nMax = CManager::GetUi_manager()->GetMax();
		ImGui::InputInt(u8"現在の最大個数", &nMax);
		CManager::GetUi_manager()->SetMax(nMax);
		ImGui::Text(u8"～～～～～ココから変更不可～～～～～");
		int nDiff = LIMITUI - nMax;
		ImGui::InputInt(u8"限界値までの個数", &nDiff);		
		ImGui::InputInt(u8"現在の個数", &nNumUI);
	}
	ImGui::End();//終わり

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