#include "exApplication.h"
#include "exInput.h"
#include "exTime.h"
#include "exTitleScene.h"
#include "exSceneManager.h"
#include "exCamera.h"
#include "exCollisionManager.h"
#include "exSoundManager.h"
#include "exResourceManager.h"


ex::Application::Application()
	: mHwnd(NULL)
	, mHdc(NULL)
	, mBackBuffer(NULL)
	, mBackHdc(NULL)
	, mWidth(0)
	, mHeight(0)
{
	
}

ex::Application::~Application()
{

}

void ex::Application::Initialize(HWND Hwnd)
{
	mHwnd = Hwnd;
	mHdc = ::GetDC(mHwnd);
	
	mWidth = 1280;
	mHeight = 720;

	RECT rc = { 0, 0, static_cast<LONG>(mWidth), static_cast<LONG>(mHeight)};
	::AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	::SetWindowPos(mHwnd,
		nullptr, 0, 0,
		rc.right - rc.left, 
		rc.bottom - rc.top,
		0);

	::ShowWindow(mHwnd, true);

	// ���� ������ ������ �ػ󵵿�  ������ ��Ʈ�� ����
	mBackBuffer = ::CreateCompatibleBitmap(mHdc, mWidth, mHeight);

	// ���� ������ ��Ʈ���� ����Ű�� DC ����
	mBackHdc = ::CreateCompatibleDC(mHdc);

	// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
	HBITMAP defaultBitmap = (HBITMAP)::SelectObject(mBackHdc, mBackBuffer);

	// ���� ����Ʈ ��Ʈ�� ����
	::DeleteObject(defaultBitmap);

	Time::Initialize();
	Input::Initialize();
	Camera::Initialize();
	SoundManager::Initialize();
	CollisionManager::Initialize();
	SceneManager::Initialize();
}

void ex::Application::Run()
{
	Update();
	Render();
}

void ex::Application::Update()
{
	Time::Update();
	Input::Update();
	Camera::Update();
	CollisionManager::Update();
	SceneManager::Update();

}


void ex::Application::Render()
{
	// ���� ����
	HBRUSH brush = CreateSolidBrush(RGB(125, 125, 125));
	HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, brush);
	// �簢������ �����
	::Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);

	CollisionManager::Render(mBackHdc);
	SceneManager::Render(mBackHdc);
	Camera::Render(mBackHdc);
	Time::Render(mBackHdc);

	::BitBlt(mHdc, 0, 0, mWidth, mHeight,
		mBackHdc, 0, 0, SRCCOPY);
}

void ex::Application::Release()
{
	// �Ŵ��� Ŭ�������� ��ü�� ������ �����ʱ� ������ �Ҹ��ڰ� ȣ��������� ���� �Լ��� ���� ���� ó���ؾ��� 
	// �������ڵ�, DC ����
	ReleaseDC(mHwnd, mHdc);

	DeleteDC(mBackHdc);
	DeleteObject(mBackBuffer);
}








