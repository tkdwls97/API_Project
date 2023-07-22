#pragma once
#include "exComponent.h"

namespace ex
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize()  override;
		virtual void Update()  override;
		virtual void Render(HDC _hdc)  override;

		// Vector2(x,y) ��ġ������ ���������� m_Pos������ �������ִ� �Լ�
		void SetPosition(const math::Vector2& _pos) { mPos = _pos; }
		void SetPosition(float _x, float _y) { mPos = math::Vector2(_x, _y); }

		// ���� �Է��� ���� �� �ְ�
		void SetPositionX(float _x) { mPos.x = _x; }
		void SetPositionY(float _y) { mPos.y = _y; }

		// ������ ��ġ������ �������ִ� m_Pos ������ �������� �Լ�
		math::Vector2 GetPosition() { return mPos; }

		// ���� ��ȯ ���� �� �ְ�
		float GetPositionX() { return mPos.x; }
		float GetPositionY() { return mPos.y; }

		// ȸ���� ������ ���� m_Rotation ������ �����ϴ� �Լ�
		void SetRotation(float _rotation) { mRotation = _rotation; }

		// ������ ������ ����ִ� m_Rotation�� �������� �Լ�
		float GetRotation() { return mRotation; }

		void SetMoveDir(enums::eMoveDir _dir) { mMoveDir = _dir; }
		enums::eMoveDir GetMoveDir() { return mMoveDir; }

	private:
		math::Vector2	mPos;
		enums::eMoveDir mMoveDir;
		float			mRotation;
	};
}
