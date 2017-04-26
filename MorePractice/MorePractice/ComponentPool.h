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
	ObjectPool(const unsigned short a_uiSize);
	~ObjectPool();
	template<typename... Args>
	unsigned int Create(Args&&... args);
	void Destroy(const unsigned int a_id);
	void Update(const double a_dDeltaTime);
	unsigned short GetCurrentSize() { return m_uiCapacity; }
	T* GetObjectByIndex(const unsigned short a_uiIndex);
	T* GetObjectById(const unsigned int a_uiId);

private:
	T *m_pComponent;
	unsigned short m_uiCapacity;
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
ObjectPool<T>::ObjectPool(const unsigned short a_uiSize) : m_uiCapacity(a_uiSize)
{
	m_pComponent = new T[m_uiCapacity];
	m_pIndices = new Index[m_uiCapacity];

	for (unsigned short i = 0; i < m_uiCapacity; ++i)
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
	if (m_uiCount < m_uiCapacity) 
	{
		Index &nextFree = m_pIndices[m_usFreelistDequeue];
		nextFree.id += m_uiCapacity;
		m_usFreelistDequeue = nextFree.next;
		nextFree.index = m_uiCount++;
		m_pComponent[nextFree.index].Init(nextFree.id, std::forward<Args>(args)...);
		return nextFree.id;
	}
	else
	{
		//0 should be an invalid number to get (unless the id overflows), since we always add capacity to the ID before returning
		return 0;
	}
}

template<typename T>
void ObjectPool<T>::Destroy(const unsigned int a_id)
{
	Index &indexToDelete = m_pIndices[a_id % m_uiCapacity];
	if (indexToDelete.index < m_uiCount) {
		T &object = m_pComponent[indexToDelete.index];
		if (object.GetID() == a_id) {
			object = m_pComponent[--m_uiCount];
			m_pIndices[object.GetID() % m_uiCapacity].index = indexToDelete.index;
			indexToDelete.index = m_uiCapacity;
			m_pIndices[m_usFreelistEnqueue].next = a_id % m_uiCapacity;
			m_usFreelistEnqueue = a_id % m_uiCapacity;
			//if we have just removed something from a completely full pool
			if (m_uiCount == m_uiCapacity - 1)
			{
				m_usFreelistDequeue = m_usFreelistEnqueue;
			}
			//if the thing we just deleted wasn't the last object in the array (meaning we did actually assign something different in object)
			if (m_pIndices[object.GetID() % m_uiCapacity].index != m_uiCapacity) {
				object.PostMoveUpdate();
			}
		}
		else {
			//probably give an error saying that object isn't there anymore??
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
T* ObjectPool<T>::GetObjectByIndex(const unsigned short a_uiIndex)
{
	if (a_uiIndex < m_uiCount) {
		return &m_pComponent[a_uiIndex];
	}
	return nullptr;
}

template <typename T>
T* ObjectPool<T>::GetObjectById(const unsigned int a_uiID)
{
	Index &indexToGet = m_pIndices[a_uiID % m_uiCapacity];
	if (indexToGet.index < m_uiCount) {
		if (m_pComponent[indexToGet.index].GetID() == a_uiID) {
			return &m_pComponent[indexToGet.index];
		}
	}
	return nullptr;
}