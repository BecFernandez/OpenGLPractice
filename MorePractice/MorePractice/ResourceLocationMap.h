#pragma once
#include <map>

template<typename T>
class ResourceLocationMap
{
public:
	ResourceLocationMap();
	~ResourceLocationMap();
	void AddResource(Levels a_level, T a_key, std::string a_filepath);
	std::string GetFilePath(Levels a_level, T a_key);

private:
	std::map<T, std::string> *m_resourceLocation;
};

template<typename T>
ResourceLocationMap<T>::ResourceLocationMap()
{
	m_resourceLocation = new std::map<T, std::string>[static_cast<int>(Levels::NUM_LEVELS)];
}

template<typename T>
ResourceLocationMap<T>::~ResourceLocationMap()
{
	delete[] m_resourceLocation;
}

template<typename T>
void ResourceLocationMap<T>::AddResource(Levels a_level, T a_key, std::string a_filepath)
{
	m_resourceLocation[static_cast<int>(a_level)].insert(std::pair<T, std::string>(a_key, a_filepath));
}

template<typename T>
std::string ResourceLocationMap<T>::GetFilePath(Levels a_level, T a_key)
{
	if (m_resourceLocation[static_cast<int>(a_level)].find(a_key) == m_resourceLocation[static_cast<int>(a_level)].end()) {
		//TODO - add exception/assert
		return "";
	} 
	return m_resourceLocation[static_cast<int>(a_level)][a_key];
}