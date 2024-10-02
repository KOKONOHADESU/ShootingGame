#pragma once

// シングルトンベース
template<class T>
class SingletonBase
{
public:
	//インスタンスの初期化
	static  T* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new T();
		}

		return m_pInstance;
	}

	//インスタンスの削除
	static void Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
protected:
	SingletonBase() {};
	virtual ~SingletonBase() {};
private:
	// コピーコンストラクタの禁止
	SingletonBase(const SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&) = delete;

	// シングルトン用ポインタ
	static T* m_pInstance;
};
// インスタンスの実体化
template <typename T> T* SingletonBase<T>::m_pInstance;