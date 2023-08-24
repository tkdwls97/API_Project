#pragma once
#include "exResource.h"

namespace ex
{
	class ResourceManager
	{

	public:
		template <typename T>
		static T* Find(const std::wstring& name)
		{
			// auto�� �ڵ� Ÿ�� �߷� (map)���� �������� m_Resource�� name(key)�� �ִ��� Ž��
			auto iter = mResources.find(name);

			// ������ end�� ��ȯ�� ���̹Ƿ� nullptr ��ȯ
			if (iter == mResources.end())
				return nullptr;

			// �ش� Ÿ������ dynamic_cast�� �̿��Ͽ� ���� ��(��� ��������) ��ȯ
			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& _name, const std::wstring& _path)
		{
			// ���ڷ� �Ѱ��� Ÿ���� T�� ġȯ�Ͽ� T ������ Ÿ���� ������ name(key)�� �ִ���
			// ã���ִ� �Լ� ����
			T* resource = ResourceManager::Find<T>(_name);

			// ����ó���� nullptr�� �ƴϸ� ã�Ƴ� ���̹Ƿ�
			// ã�Ƴ� ���ҽ��� ��ȯ�Ѵ�.
			if (resource != nullptr)
				return resource;

			// ���޹��� Ÿ������ �����Ҵ��� �̿��ؼ� ���� �����Ѵ�.
			resource = new T();

			// ���ҽ��� ���޹��� ��� ����(path)�� �̿��Ͽ� Load�Ѵ�.
			// ��ȯ���� ����� ���� Fail�� ��� �ڵ��� ������ ������ �����Ѵ�.
			if (FAILED(resource->Load(_path)))
			{
				// �޽��� �ڽ��� �̿��Ͽ� ���� �߻��� ��Ÿ����.
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				// �����Ҵ��� �̿��ؼ� ���ҽ��� �����߾����Ƿ� ���� ó���� �Ѵ�. �� �׷���
				// �޸𸮰� �������� �ʾƼ� memory leak�� ���´�.
				delete resource;
				// �����̹Ƿ� nullptr�� ��ȯ�Ѵ�.
				return nullptr;
			}

			// ���������� (Entity class)�̸�����
			resource->SetName(_name);
			// ���������� ��μ���
			resource->SetPath(_path);

			// �����ϰ� �ִ� ����ü�� �־��ش�.
			mResources.insert(std::make_pair(_name, resource));

			// ������ ���ҽ��� ��ȯ�Ѵ�.
			return resource;
		}

		template <typename T>
		static void Insert(const std::wstring& name, T* resource)
		{
			resource->SetName(name);
			mResources.insert(std::make_pair(name, resource));
		}

		static void Release()
		{
			for (auto iter : mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}



	private:
		// ���ҽ� �Ŵ��� Ŭ�������� ���ҽ��� �����ϱ� ���Ͽ� 
		// �ð����⵵�� vector�� �̿������� ���� �����⶧����
		// �ڷᱸ�� map(tree����)�� �̿��Ͽ� �����Ѵ�
		// (std::wstring(key), Type)�� �޴´�
		// �������� �����ϱ����ؼ� static�� ����Ѵ�
		// �׷��� ���������� �������ؼ� private���� ������ �����ϰ�
		// static ��� �Լ��� ���ؼ� �����ϴ°͸� ����Ѵ�
		static std::map<std::wstring, Resource*> mResources;

	};

}
