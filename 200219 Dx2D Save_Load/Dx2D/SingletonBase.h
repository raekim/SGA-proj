#pragma once
/*
�̱��� ���� : ���� ��ü ���� ���
- �ν��Ͻ� ȣ�� �� ó�� ȣ�� �ϴ� ��� �ν��Ͻ��� �����ϰ� ���� �� �ν��Ͻ��� ��ȯ�Ѵ�.
- �ν��ͽ� ȣ�� �� ������ ȣ��Ǿ� ������ �Ǿ� �ִ� ��� �� ���� �Ǿ� �ִ� �ν��Ͻ��� ��ȯ�Ѵ�.

���ø� ����(Template, ����) : �Լ� �Ǵ� Ŭ������ ����� ���� ���� Ʋ
- �������� ���� �ڷ����� ���Ͽ� ���ø��� ����Ͽ� �����ϰ� ����� �����Ѵ�.
- �Լ� �Ǵ� Ŭ���� �ۼ��� ���ø��� ��� �� �ڷ����� ������ �ش�.
*/

template <typename T> // template <class T>
class SingletonBase
{
protected:
	static T* Instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetInstance();	// �̱��� �ν��Ͻ� ��������(����)
	void ReleaseInstance();		// �̱��� �ν��Ͻ� �����ϱ�
};

// �̱��� �ʱ�ȭ
template<typename T>
T* SingletonBase<T>::Instance = NULL;

template<typename T>
inline T* SingletonBase<T>::GetInstance()
{
	if (!Instance)
		Instance = new T;

	return Instance;
}

template<typename T>
inline void SingletonBase<T>::ReleaseInstance()
{
	if (Instance)
	{
		delete Instance;
		Instance = NULL;
	}
}

