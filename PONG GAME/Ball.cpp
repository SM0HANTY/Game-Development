#include "Ball.h"

Ball::Ball(float startX, float startY){
	m_Position.x=startX;	//Set the horizontal position
	m_Position.y=startY;	//Vertical position
	
	m_Shape.setRadius(20);	//Define ball size
	m_Shape.setPosition(m_Position);	//Set ball's position
}
FloatRect Ball::getPosition(){
	return m_Shape.getGlobalBounds();
}

CircleShape Ball::getShape(){
	return m_Shape;
}
void Ball::reboundSides(){
	m_DirectionX=-m_DirectionX;
}
void Ball::reboundBatOrTop(){
	m_DirectionY=-m_DirectionY;
}
void Ball::reboundBottom(){
	m_Position.x=960;	//resets ball to the top
	m_Position.y=10;
	m_DirectionY=-m_DirectionY;
}
void Ball::update(Time dt){

//update the ball's position
m_Position.y+=m_DirectionY*m_Speed*dt.asSeconds();
m_Position.x+=m_DirectionX*m_Speed*dt.asSeconds();

//move the ball
m_Shape.setPosition(m_Position);
}

