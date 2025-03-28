#include "Bat.h"

Bat::Bat(float startX, float startY){
	m_Position.x=startX;	//Set the horizontal position
	m_Position.y=startY;	//Vertical position
	
	m_Shape.setSize(sf::Vector2f(200,50));	//Define bat size (50x5 pixels)
	m_Shape.setPosition(m_Position);	//Set bat's position
}
	
FloatRect Bat::getPosition(){
	return m_Shape.getGlobalBounds();
}

RectangleShape Bat::getShape(){
	return m_Shape;
}

void Bat::moveLeft(){
m_movingLeft=true;
}

void Bat::moveRight(){
m_movingRight=true;
}

void Bat::stopLeft(){
m_movingLeft=false;
}

void Bat::stopRight(){
m_movingRight=false;
}

void Bat::update(Time dt){
if(m_movingLeft){
m_Position.x-=m_Speed*dt.asSeconds();	//moves left
}
if(m_movingRight){
m_Position.x+=m_Speed*dt.asSeconds();	//moves right
}
m_Shape.setPosition(m_Position);
}
