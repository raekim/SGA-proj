#pragma once
/*
싱글톤 패턴 : 단일 객체 관리 방식
- 인스턴스 호출 시 처음 호출 하는 경우 인스턴스를 생성하고 생성 된 인스턴스를 반환한다.
- 인스터스 호출 시 이전에 호출되어 생성이 되어 있는 경우 그 생성 되어 있는 인스턴스를 반환한다.

템플릿 형식(Template, 형판) : 함수 또는 클래스를 만들어 내기 위한 틀
- 정해지지 않은 자료형에 대하여 템플릿을 사용하여 선언하고 기능을 구현한다.
- 함수 또는 클래스 작성시 템플릿에 사용 될 자료형을 결정해 준다.
*/

template <typename T> // template <class T>
class SingletonBase
{
protected:
	static T* Instance;

	SingletonBase() {};
	~SingletonBase() {};

public:
	static T* GetInstance();	// 싱글톤 인스턴스 가져오기(생성)
	void ReleaseInstance();		// 싱글톤 인스턴스 해제하기
};

// 싱글톤 초기화
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

