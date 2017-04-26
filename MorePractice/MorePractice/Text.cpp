//#include "Text.h"
//#include <rapidxml.hpp>
//#include <fstream>
//#include <sstream>
//
//using namespace rapidxml;
//
//Text::Text(const glm::vec3 a_position,
//		const glm::vec4 a_colour,
//		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName, const char* a_szXMLName) :
//		Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName)
//{
//	//need to load in all text from xml file
//	std::ifstream ins(a_szXMLName);
//
//	std::stringstream buffer;
//	buffer << ins.rdbuf();
//	std::string szTextFromFile(buffer.str());
//
//	//then we can pass the text to the xml parser
//	xml_document<> doc;
//	try
//	{
//		doc.parse<parse_no_data_nodes>(&szTextFromFile[0]);
//	}
//	catch(parse_error p)
//	{
//		std::cout << p.what() << std::endl;
//		const char *w = p.where<char>();
//	}
//
//	xml_node<> *font = doc.first_node("font");
//	font = font->first_node("chars");
//	xml_node<> *character = font->first_node("char");
//	do
//	{
//		Character c;
//
//		xml_attribute<> *id = character->first_attribute("id");
//		c.value = atoi(id->value());
//		xml_attribute<char> *x = character->first_attribute("x");
//		c.x = atoi(x->value());
//		xml_attribute<char> *y = character->first_attribute("y");
//		c.y = atoi(y->value());
//		xml_attribute<char> *width = character->first_attribute("width");
//		c.width = atoi(width->value());
//		xml_attribute<char> *height = character->first_attribute("height");
//		c.height = atoi(height->value());
//
//		m_characters.push_back(c);
//
//		character = character->next_sibling();
//	}while(character != nullptr);
//}
//
//void Text::DrawString(const GLuint VBO, const GLuint IBO, GLSLProgram *shader, const char* a_szToDraw)
//{
//	glm::vec3 centrePos = m_oCentrePos;
//	float curX = 0;
//	const char* currentLetter = a_szToDraw;
//	//not sure if better to put NULL or 0 here instead of the null terminator character. probably no difference.
//	while(*currentLetter != '\0')
//	{
//		//loop through all letters to find current. Got to be a faster way. A map?
//		for(std::vector<Character>::iterator it = m_characters.begin(); it != m_characters.end(); it++)
//		{
//			if((*it).value == *currentLetter)
//			{
//				Character& thisChar = *it;
//				//move the position of the sprite
//				m_oCentrePos.x = centrePos.x + curX + thisChar.width*0.5;
//				//update the width and height and align bottom of the letters
//				UpdateCornersGrounded(thisChar.width, thisChar.height);
//				//change the UVs
//				setSpriteUVCoords(thisChar.x/(float)m_uiTextureWidth, 1.0 - (thisChar.y+ thisChar.height)/(float)m_uiTextureHeight,
//					(thisChar.x + thisChar.width)/(float)m_uiTextureWidth, 1.0 - (thisChar.y )/(float)m_uiTextureHeight);
//				
//				Sprite::Update(0);
//				Sprite::Draw(VBO, IBO, shader);
//				curX += thisChar.width;
//				break;
//			}
//		}
//		currentLetter++;
//	}
//	m_oCentrePos = centrePos;
//}
//
//void Text::Update(const double a_dDeltaTime)
//{
//	Sprite::Update(a_dDeltaTime);
//}
//
