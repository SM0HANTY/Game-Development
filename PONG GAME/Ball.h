#include<SFML/Graphics.hpp>
using namespace sf;

class Ball{

	Vector2f m_Position;
	CircleShape m_Shape;
	
	float m_Speed=600.0f;	//Controls how fast the ball moves
	float m_DirectionX=0.2f;	//ball moves to the right
	float m_DirectionY=0.2f;	//ball moves downward

public:
	Ball(float startX, float startY);

	FloatRect getPosition();
	CircleShape getShape();
	
	void reboundSides();	//called when the ball hits the left or right side wall
				//change the horizontal direction
	
	void reboundBatOrTop();	//called when the ball hit the bat or top of the screen
				//change the vertical direction
	
	void reboundBottom();	//called when the ball misses the bat and hits the bottom
				//resets the ball (player loses a life)
	
	void update(Time dt);
	
};

