#pragma once

/*
싱글톤 패턴 : 단일 객체 관리 방법
인스턴스를 호출 시 처음 호출(인스턴스가 생성 되기 전)이 되면
인스턴스를 생성 해서 반환 한다.
인스턴스가 생성 된 이후 호출 하게 되면 기존에 생성 된 인스턴스를 반환한다.
*/

template <class T> // template<typename T>
class SingletonBase
{
protected:
    // 싱글톤 인스턴스 선언
    static T* instance;

    SingletonBase() {};
    ~SingletonBase() {};

public:
    // 싱글톤 인스턴스 가져오기
    static T* GetInstance();
    // 싱글톤 인스턴스 해제하기
    void ReleaseInstance();
};

// 싱글톤 초기화
template<typename T>
T* SingletonBase<T>::instance = NULL;

// 싱글톤 인스턴스 가져오기
template<typename T>
T* SingletonBase<T>::GetInstance()
{
    // 싱글톤 인스턴스가 생성 되어 있지 않다면 새로 생성
    if (!instance)
        instance = new T;

    return instance;
}

// 싱글톤 인스턴스 해제하기
template<typename T>
void SingletonBase<T>::ReleaseInstance()
{
    // 싱글톤 인스턴스가 생성되어 있다면 해제 한다.
    if (instance)
    {
        delete instance;
        instance = NULL;
    }
}