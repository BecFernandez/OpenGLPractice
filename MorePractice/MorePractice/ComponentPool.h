#pragma once
#include <utility>

struct Index
{
	unsigned int id;
	unsigned short index;
	unsigned short next;
};

template<typename T>
class ObjectPool
{
public:
	ObjectPool();
	ObjectPool(const unsigned int a_uiSize);
	~ObjectPool();
	template<typename... Args>
	unsigned int Create(Args&&... args);
	void Destroy(const unsigned int a_id);
	void Update(const double a_dDeltaTime);
	unsigned int GetCurrentSize() { return m_uiCapacity; }
	T* GetObjectByIndex(const unsigned int a_uiIndex);

private:
	T *m_pComponent;
	unsigned int m_uiCapacity;
	unsigned int m_uiCount;
	Index *m_pIndices;
	unsigned short m_usFreelistDequeue;
	unsigned short m_usFreelistEnqueue;
};

template<typename T>
ObjectPool<T>::ObjectPool() : m_uiCapacity(0)
{

}

template<typename T>
ObjectPool<T>::ObjectPool(const unsigned int a_uiSize) : m_uiCapacity(a_uiSize)
{
	m_pComponent = new T[m_uiCapacity];
	m_pIndices = new Index[m_uiCapacity];

	for (unsigned int i = 0; i < m_uiCapacity; ++i)
	{
		m_pIndices[i].id = i;
		//what happens when we get to the end??
		m_pIndices[i].next = i + 1;
	}

	m_usFreelistDequeue = 0;
	m_usFreelistEnqueue = m_uiCapacity - 1;
	m_uiCount = 0;
}

template<typename T>
ObjectPool<T>::~ObjectPool()
{
	delete[] m_pComponent;
	delete[] m_pIndices;
}

template<typename T>
template<typename... Args>
unsigned int ObjectPool<T>::Create(Args&&... args)
{
	if (m_uiCount != m_uiCapacity) 
	{
		Index &nextFree = m_pIndices[m_usFreelistDequeue];
		m_usFreelistDequeue = nextFree.next;
		nextFree.id += m_uiCapacity;
		nextFree.index = m_uiCount++;
		m_pComponent[nextFree.index].Init(nextFree.id, std::forward<Args>(args)...);
		return nextFree.id;
	}
	else
	{
		return m_uiCapacity;
	}
}

template<typename T>
void ObjectPool<T>::Destroy(const unsigned int a_id)
{
	Index &indexToDelete = m_pIndices[a_id % m_uiCapacity];
	if (indexToDelete.index < m_uiCount) {
		T &object = m_pComponent[indexToDelete.index];
		object = m_pComponent[--m_uiCount];
		m_pIndices[object.GetID() % m_uiCapacity].index = indexToDelete.index;

		indexToDelete.index = m_uiCapacity;
		//m_pIndices[m_usFreelistEnqueue].next = a_pComponent->GetID() % m_uiCapacity;
		//m_usFreelistEnqueue = a_pComponent->GetID() % m_uiCapacity;
		//if we have just removed something from a completely full pool
		if (m_uiCount == m_uiCapacity - 1)
		{
			m_usFreelistDequeue = m_usFreelistEnqueue;
		}
	}
}

template<typename T>
void ObjectPool<T>::Update(const double a_dDeltaTime)
{
	for (unsigned int i = 0; i < m_uiCount; ++i)
	{
		m_pComponent[i].Update(a_dDeltaTime);
	}
}

template<typename T>
T* ObjectPool<T>::GetObjectByIndex(const unsigned int a_uiIndex)
{
	if (m_pIndices[a_uiIndex].index < m_uiCount) {
		return &m_pComponent[m_pIndices[a_uiIndex].index];
	}
	return nullptr;
}