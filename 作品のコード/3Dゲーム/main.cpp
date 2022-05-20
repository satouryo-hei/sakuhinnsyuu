//=============================================================================
//
// ���C������ [main.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "main.h"
#include"manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"�|���S���̕`��"	// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
int						g_nCountFPS;			// FPS�J�E���^
//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEN�̃������T�C�Y�̎w��
		CS_CLASSDC,						//�\������E�B���h�E�̃X�^�C����ݒ�
		WndProc,						//�E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,								//�ӂ��g��񂩂�0���w��
		0,								//�ӂ��g��񂩂�0���w��
		hInstance,						//Windows�̈����̃C���X�^���X�n���h�����w��
		NULL,							//�^�X�N�o�[�Ɏg���A�C�R�����w��
		LoadCursor(NULL, IDC_ARROW),	//�g���}�E�X�J�[�\�����w��
		(HBRUSH)(COLOR_WINDOW + 1),		//�E�B���h�E�̃N���C�A���g�̈�̔w�i�F���w��
		NULL,							//Window�ɂ��郁�j���[��ݒ�
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		NULL							//�t�@�C���A�C�R���Ɏg���A�C�R����ݒ�
	};

	//�ϐ��錾
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;		//�E�B���h�E�n���h��
	MSG msg;		//���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬�i������E�B���h�E���E�B���h�E�n���h���ɔ[�߂ĊǗ�����j
	hWnd = CreateWindow(CLASS_NAME,					//�g���E�B���h�E�X�^�C��
		WINDOW_NAME,				//�E�B���h�E�N���X�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�B���h�E�̖��O
		CW_USEDEFAULT,				//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�B���h�E�̍���̂w���W
		(rect.right - rect.left),	//�E�B���h�E�̍���̂x���W
		(rect.bottom - rect.top),	//�E�B���h�E�̕�
		NULL,						//�E�B���h�E�̍���
		NULL,						//�e�E�B���h�E�̃n���h��
		hInstance,					//���j���[�E�B���h�E�܂��͎q�E�B���h�E
		NULL);						//�C�����^���X�n���h��
									//�E�B���h�E�쐬�f�[�^
									//���I�������̊m��
	CManager *pManager = NULL;

	pManager = new CManager;

	// ����������
	if (FAILED(pManager->Init(hInstance,hWnd, true)))
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwCurrentTime =
		dwFrameCount = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
#ifdef _DEBUG
			 // FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�

				// �X�V����
				if (pManager != NULL)
				{
					pManager->Update();
				}

				if (pManager != NULL)
				{
					// �`�揈��
					pManager->Draw();
				}
				dwFrameCount++;
			}
		}
	}

	if (pManager != NULL)
	{
		// �I������
		pManager->Uninit();
		//���I�������̊m�ۂ������̂����
		delete pManager;
		pManager = NULL;
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);	// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// FPS�\��
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}