#include "FontComponent.h"
#include <rapidxml.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameObject.h"

using namespace rapidxml;

FontComponent::FontComponent()
{
}


FontComponent::~FontComponent()
{
}

void FontComponent::Init(unsigned int a_uiId, const glm::vec4 a_colour,
	const glm::vec2 a_dimensions, const char* a_szTexName, const char* a_szXMLName,
	GLuint a_uiVAO, GLuint a_uiVBO, GLuint a_uiIBO, const GLSLProgram* a_pShader)
{
	SpriteComponent::Init(a_uiId, a_colour, a_dimensions, a_szTexName, a_uiVAO, a_uiVBO, a_uiIBO, a_pShader);
	
	std::ifstream ins(a_szXMLName);
	
	std::stringstream buffer;
	buffer << ins.rdbuf();
	std::string szTextFromFile(buffer.str());
	
	//then we can pass the text to the xml parser
	xml_document<> doc;
	try
	{
		doc.parse<parse_no_data_nodes>(&szTextFromFile[0]);
	}
	catch(parse_error p)
	{
		std::cout << p.what() << std::endl;
		const char *w = p.where<char>();
	}
	
	xml_node<> *font = doc.first_node("font");
	font = font->first_node("chars");
	xml_node<> *character = font->first_node("char");
	do
	{
		Character c;
	
		xml_attribute<> *id = character->first_attribute("id");
		c.m_cValue = atoi(id->value());
		xml_attribute<char> *x = character->first_attribute("x");
		c.m_iX = atoi(x->value());
		xml_attribute<char> *y = character->first_attribute("y");
		c.m_iY = atoi(y->value());
		xml_attribute<char> *width = character->first_attribute("width");
		c.m_iWidth = atoi(width->value());
		xml_attribute<char> *height = character->first_attribute("height");
		c.m_iHeight = atoi(height->value());
	
		m_characters.insert(std::pair<char, Character>(c.m_cValue, c));
	
		character = character->next_sibling();
	}while(character != nullptr);
}

void FontComponent::Draw(const char * a_szToDraw, glm::vec3 a_position, glm::vec4 a_colour)
{

	SpriteComponent::ChangeColour(a_colour);
	glm::vec3 centrePos = a_position;
	float curX = 0;
	const char* currentLetter = a_szToDraw;
	//not sure if better to put NULL or 0 here instead of the null terminator character. probably no difference.
	while(*currentLetter != '\0')
	{
		
		Character thisChar = m_characters[*currentLetter];
		//move the position of the sprite
		m_pGameObject->m_position.x = centrePos.x + curX + thisChar.m_iWidth*0.5;
		//update the width and height and align bottom of the letters
		UpdateCornersGrounded(thisChar.m_iWidth, thisChar.m_iHeight);
		//change the UVs
		SetSpriteUVCoords(thisChar.m_iX/m_dimensions.x, 
			1.0 - (thisChar.m_iY+ thisChar.m_iHeight)/m_dimensions.y,
			(thisChar.m_iX + thisChar.m_iWidth)/m_dimensions.x, 
			1.0 - (thisChar.m_iY )/m_dimensions.y);
		m_pGameObject->Update(0);
		SpriteComponent::Draw();
		curX += thisChar.m_iWidth;
				
		currentLetter++;
	}
	m_pGameObject->m_position = centrePos;
}
