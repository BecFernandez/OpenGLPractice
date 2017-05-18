#pragma once
#include <map>

template<typename T>
class ResourceLocationMap
{
public:
	void AddResource(T a_key, std::string a_filepath);
	std::string GetFilePath(T a_key);

private:
	std::map<T, std::string> m_resourceLocation;
};

template<typename T>
void ResourceLocationMap<T>::AddResource(T a_key, std::string a_filepath)
{
	m_resourceLocation.insert(std::pair<T, std::string>(a_key, a_filepath));
}

template<typename T>
std::string ResourceLocationMap<T>::GetFilePath(T a_key)
{
	if (m_resourceLocation.find(a_key) == m_resourceLocation.end()) {
		//TODO - add exception/assert
		return "";
	} 
	return m_resourceLocation[a_key];
}