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
	ImGui::Begin(u8"UI情報"); //タイトルテキスト

	// 使用しているかどうかの取得
	bool bUse = CManager::GetUi_manager()->GetUse();

	if (bUse)
	{
		// 移動できるか
		bool bMove = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolMove();
		ImGui::Checkbox(u8"位置変更", &bMove);

		// 移動できるなら
		if (bMove)
		{
			// 現在の位置を取得する
			D3DXVECTOR3 Pos = CManager::GetUi_manager()->GetUi(nNumUI)->GetPos();
			ImGui::InputFloat3(u8"位置", Pos);

			// 現在の位置を設定する
			CManager::GetUi_manager()->GetUi(nNumUI)->SetPos(Pos);
		}
		// // 移動できるかの設定をする
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolMove(bMove);

		// 大きさ変更できるか
		bool bSize = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolSize();
		ImGui::Checkbox(u8"大きさ変更", &bSize);
		// できるなら
		if (bSize)
		{
			// 大きさを取得する
			D3DXVECTOR3 Size = CManager::GetUi_manager()->GetUi(nNumUI)->GetSize();
			ImGui::InputFloat2(u8"大きさ", Size);
			// 大きさを設定をする
			CManager::GetUi_manager()->GetUi(nNumUI)->SetSize(Size);
		}
		// 大きさ変更できるかの設定をする
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolSize(bSize);

		// 移動量の変更ができるか
		bool bSpeed = CManager::GetUi_manager()->GetUi(nNumUI)->GetBoolSpeed();
		ImGui::Checkbox(u8"移動量変更", &bSpeed);
		// できるなら
		if (bSpeed)
		{
			// 移動量を取得する
			D3DXVECTOR3 Move = CManager::GetUi_manager()->GetUi(nNumUI)->GetMove();
			ImGui::InputFloat3(u8"移動量", Move);
			// 移動量を設定をする
			CManager::GetUi_manager()->GetUi(nNumUI)->SetMove(Move);
		}
		// 移動量の変更ができるかの設定をする
		CManager::GetUi_manager()->GetUi(nNumUI)->SetBoolSpeed(bSpeed);

		// 最大個数の取得をする
		int nMax = CManager::GetUi_manager()->GetMax();
		ImGui::InputInt(u8"現在の最大個数", &nMax);

		// 最大個数の設定をする
		CManager::GetUi_manager()->SetMax(nMax);

		// 現在のテクスチャを取得する
		int nTex = CManager::GetUi_manager()->GetUi(nNumUI)->GetTex();
		ImGui::InputInt(u8"現在のテクスチャ", &nTex);

		// 現在のテクスチャを設定する
		CManager::GetUi_manager()->GetUi(nNumUI)->SetTex(nTex);

		ImGui::Text(u8"～～～～～ココから変更不可～～～～～");

		// 差分を計算
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