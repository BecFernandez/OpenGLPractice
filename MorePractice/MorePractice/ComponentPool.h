#pragma once
#include <utility>

template<typename T>
class ComponentPool
{
public:
	ComponentPool();
	ComponentPool(const int a_iSize);
	~ComponentPool();
	template<typename... Args>
	T* Create(Args&&... args);
	void Destroy(T* a_pComponent);

private:
	T *m_pComponent;
	int m_iSize;
	bool *m_pActive;
};

template<typename T>
ComponentPool<T>::ComponentPool() : m_iSize(0)
{

}

template<typename T>
ComponentPool<T>::ComponentPool(const int a_iSize) : m_iSize(a_iSize)
{
	m_pComponent = new T[m_iSize];
	m_pActive = new bool[m_iSize];

	for (unsigned int i = 0; i < m_iSize; ++i)
	{
		m_pActive[i] = false;
	}
}

template<typename T>
ComponentPool<T>::~ComponentPool()
{
	delete[] m_pComponent;
	delete[] m_pActive;
}

template<typename T>
template<typename... Args>
T* ComponentPool<T>::Create(Args&&... args)
{
	for (unsigned int i = 0; i < m_iSize; ++i)
	{
		if (m_pActive[i] != true)
		{
			m_pComponent[i].Init(std::forward<Args>(args)...);
			m_pActive[i] = true;
			return &m_pComponent[i];
		}
	}
	return nullptr;
}

template<typename T>
void ComponentPool<T>::Destroy(T* a_pComponent)
{
	for (unsigned int i = 0; i < m_iSize; ++i)
	{
		if (&m_pComponent[i] == a_pComponent)
		{
			m_pActive[i] = false;
		}
	}
}