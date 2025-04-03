#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include<stdlib.h>
#include "Bat.cpp"
#include "Ball.cpp"
using namespace sf;

int main(){

//Define a window
VideoMode vm(1920,1080);

//Create a window
RenderWindow window(vm, "Pong Game", Style::Fullscreen);

View view(FloatRect(0,0,1920,1080));         //Calculates the coordinates according to the main resolution
window.setView(view);

int score=0;
int lives=3;

Bat bat(900, 1000);

Ball ball(960,10);

Text hud;

Font font;
font.loadFromFile("/home/student/Documents/sec44_SFML/font/KOMIKAP_.ttf");

//set the font to our style
hud.setFont(font);

//make it nice and big
hud.setCharacterSize(75);

//choose a color
hud.setFillColor(Color::White);


//20 pixels from the left edge of the window
hud.setPosition(20,20);


Clock clock;

//Gaming loop
while(window.isOpen()){
Event event;
while(window.pollEvent(event)){
if(event.type==Event::Closed){
window.close();
}
}
if(Keyboard::isKeyPressed(Keyboard::Escape)){
window.close();
}

if(Keyboard::isKeyPressed(Keyboard::Left)){
bat.moveLeft();
}else{
bat.stopLeft();
}

if(Keyboard::isKeyPressed(Keyboard::Right)){
bat.moveRight();
}else{
bat.stopRight();
}

Time dt=clock.restart();	//update the delta time
bat.update(dt);
ball.update(dt);

std::stringstream ss;
ss<<"Score:"<<score<<std::endl<<"Lives:"<<lives;
hud.setString(ss.str());

//Draw
window.clear();
window.draw(hud);
window.draw(bat.getShape());	//draws the bat
window.draw(ball.getShape());
window.display();
}
}
