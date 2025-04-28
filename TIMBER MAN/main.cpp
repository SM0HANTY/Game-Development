#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include <SFML/Audio.hpp>
using namespace sf;

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side
{
    LEFT,
    RIGHT,
    NONE
};
side branchPositions[NUM_BRANCHES];

int main()
{
    VideoMode vm(960, 540);
    RenderWindow window(vm, "Timber!!",Style::Fullscreen);

    View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    Texture textureBackground;
    textureBackground.loadFromFile("objects/background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Texture texturetree;
    texturetree.loadFromFile("objects/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(texturetree);
    spriteTree.setPosition(810, 0);

    Texture textureBee;
    textureBee.loadFromFile("objects/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    Texture textureCloud;
    textureCloud.loadFromFile("objects/cloud.png");
    Sprite spriteCloud1, spriteCloud2, spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);
    spriteCloud3.setScale(0.5f, 0.5f);
    bool cloudActive1 = false;
    bool cloudActive2 = false;
    bool cloudActive3 = false;
    float cloudSpeed1 = 0.0f;
    float cloudSpeed2 = 0.0f;
    float cloudSpeed3 = 0.0f;

    // Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("objects/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    // The player starts on the left
    side playerSide = side::LEFT;

    // Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("objects/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // Prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("objects/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("objects/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    // Some other useful log related variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    bool acceptInput = false;

    Clock clock;
    Time dt;
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;
    int score = 0;
    Text messageText;
    Text scoreText;

    Font font;
    font.loadFromFile("KOMIKAP_.ttf");
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Please Enter to start!");
    scoreText.setString("Score =0");
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::Green);
    scoreText.setFillColor(Color::Red);

    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    scoreText.setPosition(20, 20);

    Texture textureBranch;
    textureBranch.loadFromFile("objects/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        branches[i].setOrigin(220, 20);
    }


    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sounds/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);


    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sounds/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);



    // Out of time

    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sounds/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);
    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);



    while (window.isOpen())
    {
        

	Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased && !paused)
            {
                // Listen for key presses again
                acceptInput = true;

                // hide the axe
                spriteAxe.setPosition(2000,
                                      spriteAxe.getPosition().y);
            }
        }



        // To handle the windows Close pop-up

        Event event1;
        while (window.pollEvent(event1))
        {
            if (event1.type == event1.Closed)
            {
                window.close();
            }
        }


       
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }



        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;
            score = 0;
            timeRemaining = 6;

            
	    // Make all the branches disappear
            for (int i = 1; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }

            // Make sure the gravestone is hidden
            spriteRIP.setPosition(675, 2000);

            // Move the player into position
            spritePlayer.setPosition(580, 720);

            acceptInput = true;
        }
        


	// Make sure we are accepting input

        if (acceptInput)
        {
            // First handle pressing the right cursor key
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                // Make sure the player is on the right
                playerSide = side::RIGHT;

                score++;

                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;

                spriteAxe.setPosition(AXE_POSITION_RIGHT,
                                      spriteAxe.getPosition().y);

                spritePlayer.setPosition(1200, 720);

                // update the branches
                updateBranches(score);

                // set the log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;

                acceptInput = false;

                // Play a chop sound
                chop.play();
            }



            // Handle the left cursor key

            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                // Make sure the player is on the left
                playerSide = side::LEFT;

                score++;

                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;

                spriteAxe.setPosition(AXE_POSITION_LEFT,
                                      spriteAxe.getPosition().y);

                spritePlayer.setPosition(580, 720);

                // update the branches
                updateBranches(score);

                // set the log flying
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logActive = true;

                acceptInput = false;

                // Play a chop sound
                chop.play();
            }
        }



        if (!paused)
        {

            dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("Out of Time!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
                // Play the out of time sound
                outOfTime.play();
            }
        

        if (!beeActive)
        {
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        }
        else
        {
            spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
            if (spriteBee.getPosition().x < -100)
            {
                beeActive = false;
            }
        }

        if (!cloudActive1)
        {
            srand((int)time(0) * 10);
            cloudSpeed1 = (rand() % 200);
            srand((int)time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);
            cloudActive1 = true;
        }
        else
        {
            spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloudSpeed1 * dt.asSeconds()), spriteCloud1.getPosition().y);
            if (spriteCloud1.getPosition().x > 1920)
            {
                cloudActive1 = false;
            }
        }

        if (!cloudActive2)
        {
            srand((int)time(0) * 20);
            cloudSpeed2 = (rand() % 200);
            srand((int)time(0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition(-200, height);
            cloudActive2 = true;
        }
        else
        {
            spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloudSpeed2 * dt.asSeconds()), spriteCloud2.getPosition().y);
            if (spriteCloud2.getPosition().x > 1920)
            {
                cloudActive2 = false;
            }
        }
        if (!cloudActive3)
        {
            srand((int)time(0) * 30);
            cloudSpeed3 = (rand() % 200);
            srand((int)time(0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition(-200, height);
            cloudActive3 = true;
        }
        else
        {
            spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloudSpeed3 * dt.asSeconds()), spriteCloud3.getPosition().y);
            if (spriteCloud3.getPosition().x > 1920)
            {
                cloudActive3 = false;
            }

            std::stringstream ss;
            ss << "Score=" << score;
            scoreText.setString(ss.str());

            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPositions[i] == side ::LEFT)
                {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                }
                else if (branchPositions[i] == side ::RIGHT)
                {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                }
                else
                {
                    branches[i].setPosition(3000, height);
                }
            }

            if (logActive)
            {

                spriteLog.setPosition(
                    spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                    spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

                // Has the insect reached the right hand edge of the screen?
                if (spriteLog.getPosition().x < -100 ||
                    spriteLog.getPosition().x > 2000)
                {
                    // Set it up ready to be a whole new cloud next frame
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }

            // has the player been squished by a branch?
            if (branchPositions[5] == playerSide)
            {
                // death
                paused = true;
                acceptInput = false;

                // Draw the gravestone
                spriteRIP.setPosition(525, 760);

                // hide the player
                spritePlayer.setPosition(2000, 660);

                // Change the text of the message
                messageText.setString("SQUISHED!!");

                // Center it on the screen
                FloatRect textRect = messageText.getLocalBounds();

                messageText.setOrigin(textRect.left +
                                          textRect.width / 2.0f,
                                      textRect.top + textRect.height / 2.0f);

                messageText.setPosition(1920 / 2.0f,
                                        1080 / 2.0f);

                // Play the death sound
                death.play();
            }
	}

        }//End if (!paused)




        window.clear();
        window.draw(spriteBackground);

        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);

        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);
        if (paused)
        {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}




void updateBranches(int seed)
{
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
    {
        branchPositions[j] = branchPositions[j - 1];
    }
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r)
    {
    case 0:
        branchPositions[0] = side ::LEFT;
        break;
    case 1:
        branchPositions[0] = side ::RIGHT;
        break;
    default:
        branchPositions[0] = side ::NONE;
        break;
    }
}
