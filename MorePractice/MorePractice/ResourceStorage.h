#pragma once
#include <map>

template<typename T, typename Resource>
class ResourceStorage
{
public:
	void AddResource(T a_key, Resource a_resource); //this should probably error if there's no more space to add anything
	void RemoveResource(T a_key);
	Resource& GetResource(T a_key);

private:
	//should I write my own container instead? So I can guarantee stuff is stored next to eachother?
	std::map<T, Resource> m_resources;
};

template<typename T, typename Resource>
void ResourceStorage<T, Resource>::AddResource(T a_key, Resource a_resource)
{
	m_resources.insert(std::pair<T, Resource>(a_key, a_resource));
}

template<typename T, typename Resource>
void ResourceStorage<T, Resource>::RemoveResource(T a_key)
{
	m_resources.erase(a_key);
}

template<typename T, typename Resource>
Resource& ResourceStorage<T, Resource>::GetResource(T a_key)
{
	if (m_resources.find(a_key) == m_resources.end()) {
		//TODO - add error here that will take us out of this flow of execution.
	}
	return m_resources[a_key];
}