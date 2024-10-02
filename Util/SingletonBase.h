#pragma once

// �V���O���g���x�[�X
template<class T>
class SingletonBase
{
public:
	//�C���X�^���X�̏�����
	static  T* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new T();
		}

		return m_pInstance;
	}

	//�C���X�^���X�̍폜
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
	// �R�s�[�R���X�g���N�^�̋֎~
	SingletonBase(const SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&) = delete;

	// �V���O���g���p�|�C���^
	static T* m_pInstance;
};
// �C���X�^���X�̎��̉�
template <typename T> T* SingletonBase<T>::m_pInstance;