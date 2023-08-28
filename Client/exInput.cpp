#include "exInput.h"
#include "exApplication.h"

extern ex::Application application;

namespace ex
{
	//static (�������� �ʱ�ȭ)
	std::vector<Input::Key> Input::mKeys = {};
	math::Vector2 Input::mMousePos = {};
	int ASCII[(int)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I' ,'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE, VK_CONTROL,
		VK_LBUTTON,
	};

	void Input::Initialize()
	{
		for (int i = 0; i < (int)eKeyCode::End; i++)
		{
			Key key = {};
			key.keyCode = (eKeyCode)i;
			key.keyState = eKeyState::None;
			key.autoCode = eAutoCode::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}

	}
	void Input::Update()
	{
		for (int i = 0; i < (int)eKeyCode::End; i++)
		{
			POINT MousePos = {};
			// ���� ���콺 Pos �� �޾ƿ´�
			GetCursorPos(&MousePos);
			// ���콺 Pos �� ��ũ�� ��ǥ���� Ư�� Ŭ���̾�Ʈ ��ǥ�� �ٲ��ش�
			ScreenToClient(application.GetHwnd(), &MousePos);

			mMousePos.x = (float)MousePos.x;
			mMousePos.y = (float)MousePos.y;


			// �ش�Ű�� �������� üũ
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// ���� �����ӿ��� ������ �־���.
				if (mKeys[i].bPressed == true)
					mKeys[i].keyState = eKeyState::Pressed;
				else
					mKeys[i].keyState = eKeyState::Down;

				mKeys[i].bPressed = true;
			}
			else // �ش�Ű�� �ȴ����� �ִ�.
			{
				// ���� �����ӿ� �������־���.
				if (mKeys[i].bPressed == true)
					mKeys[i].keyState = eKeyState::Up;
				else
					mKeys[i].keyState = eKeyState::None;

				mKeys[i].bPressed = false;
			}
		}
	}
}






