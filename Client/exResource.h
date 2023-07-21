#pragma once
#include "exEntity.h"


// �̹����� ���� ���� ���ҽ��� �����Ѵ�
namespace ex
{
	class Resource : public Entity
	{

	public:
		Resource();
		virtual ~Resource();

		// ���ҽ� Ŭ������ �ڽ��� �׻� Load�� �����ϰ� �ϱ����� ���� �����Լ��� �������
		virtual HRESULT Load(const std::wstring& _path) = 0;

		// ������ �̹����� ��θ� ��ȯ���ش� (��� ������ private�̱� ������ Get�Լ� �̿�)
		std::wstring& GetPath() { return mPath; }

		//  �̹����� ��θ� ��� ������ �������ش�(��� ������ private�̱� ������ Set�Լ� �̿�)
		void SetPath(const std::wstring& _path) { mPath = _path; }


	private:
		std::wstring mPath;
	};

}



