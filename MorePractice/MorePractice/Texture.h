#pragma once
class Texture
{
public:
	Texture() {}
	Texture(const char* a_szPath);
	~Texture();
	unsigned int GetWidth() { return m_uiWidth; }
	unsigned int GetHeight() { return m_uiHeight; }
	unsigned int GetHandle() { return m_uiTexHandle; }

private:
	unsigned int m_uiTexHandle;
	const char* m_szPath;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	unsigned int m_uiBPP;
};

