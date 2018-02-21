#pragma once
#include <map>

template<typename T, typename Resource>
class ResourceStorage
{
public:
	ResourceStorage();
	~ResourceStorage();
	void AddResource(Levels a_level, T a_key, Resource a_resource); //this should probably error if there's no more space to add anything
	void RemoveResource(Levels a_level, T a_key);
	void RemoveAllResourcesFromLevel(Levels a_level);
	Resource& GetResource(Levels a_level, T a_key);

private:
	//should I write my own container instead? So I can guarantee stuff is stored next to eachother?
	std::map<T, Resource> *m_resources;
};

template<typename T, typename Resource>
ResourceStorage<T, Resource>::ResourceStorage()
{
	m_resources = new std::map<T, Resource>[static_cast<int>(Levels::NUM_LEVELS)];
}

template<typename T, typename Resource>
ResourceStorage<T, Resource>::~ResourceStorage()
{
	delete[] m_resources;
}

template<typename T, typename Resource>
void ResourceStorage<T, Resource>::AddResource(Levels a_level, T a_key, Resource a_resource)
{
	m_resources[static_cast<int>(a_level)].insert(std::pair<T, Resource>(a_key, a_resource));
}

template<typename T, typename Resource>
void ResourceStorage<T, Resource>::RemoveResource(Levels a_level, T a_key)
{
	m_resources[static_cast<int>(a_level)].erase(a_key);
}

template<typename T, typename Resource>
void ResourceStorage<T, Resource>::RemoveAllResourcesFromLevel(Levels a_level)
{
	m_resources[static_cast<int>(a_level)].clear();
}

template<typename T, typename Resource>
Resource& ResourceStorage<T, Resource>::GetResource(Levels a_level, T a_key)
{
	if (m_resources[static_cast<int>(a_level)].find(a_key) == m_resources[static_cast<int>(a_level)].end()) {
		//TODO - add error here that will take us out of this flow of execution.
	}
	return m_resources[static_cast<int>(a_level)][a_key];
}