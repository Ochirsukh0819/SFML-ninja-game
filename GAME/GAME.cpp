#include<SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>
#include<math.h>
#include <vector>
#include <iostream>
#include<stdlib.h>
#include<sstream>


using namespace sf;
class Object {
public:
    Text text1;
    Font font;
    Texture owl;
    Sprite owlSprite;
    Object() {
        this->font.loadFromFile("images/Dosis-Bold.ttf");
        // text1
        this->text1.setFont(this->font);
        this->text1.setFillColor(Color::White);
        this->text1.setCharacterSize(24);

    } 
};

// create class
class Player {

    public:
        unsigned points;
        float health;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Texture background;
        sf::Sprite groundSprite;
    Player() {
        this->health = 10;
        this->points = 0;
        this->texture.loadFromFile("images/ninja.png");
        this->sprite.setTexture(texture);
        this->sprite.setScale(0.3f, 0.3f);
        this->background.loadFromFile("images/background1.png");
        this->groundSprite.setTexture(this->background);
        this->sprite.setPosition(50, 400);

        
    }
};

// princess 
class Princess {
public:
    sf::Texture ptext;
    sf::Sprite spriteP;
    Princess() {
        this->ptext.loadFromFile("images/princess.png");
        //this->ptext.loadFromFile("C:/Users/user/OneDrive/Desktop/images/princess.png");
        spriteP.setTexture(ptext); 
        spriteP.setScale(0.3f, 0.3f); 
        spriteP.setPosition(-40, 400); 

    }

};

// bullet class
class Bullet {
public:
    Vector2f currVelocity;
    float maxSpeed;
    int shootTimer;
    sf::Texture text;
    sf::Sprite s;

    Bullet()
    {
        this->currVelocity = Vector2f(0.f, 0.f);
        this->maxSpeed = 8.f;
        this->shootTimer = 0; 
        this->text.loadFromFile("images/weapon.png");
        s.setTexture(text);
        s.setScale(0.1f, 0.1f);
    }
};

// enemy class
class Enemy {
public:
    int random;
    sf::Texture enemyText;
    sf::Sprite enemySprite;
    Enemy() {
        this->enemyText.loadFromFile("images/enemy.png");
        this->enemySprite.setTexture(enemyText);
        enemySprite.setScale(0.2f, 0.2f);  
    }
 };

class Boss {
public:
    int life;
    Texture bossText;
    Sprite bossSprite;
    Boss() {
        this->life = 60;
        this->bossText.loadFromFile("images/boss.png");
        this->bossSprite.setTexture(bossText);
        this->bossSprite.setScale(0.7f, 0.7f);
        this->bossSprite.setPosition(1600.f, 400.f);
    }

 };

 int main()
    {

        srand(time(NULL));
        RenderWindow window(VideoMode(1800, 1000), "shooter game", Style::Default);
        window.setFramerateLimit(60);
      
        // game over sound

        SoundBuffer gameBuffer1;
        Sound gameSound1;
        gameBuffer1.loadFromFile("images/start.wav");
        gameSound1.setBuffer(gameBuffer1);
        gameSound1.play();

   
        //create player
        Player player;

        // Object
        Object object;

        // bullets
        Bullet b1;
        std::vector<Bullet> bullets;

        // princess
        Princess princess;
        
        // enemy
        Enemy enemy;
        std::vector<Sprite> enemies;

        // Vector
        Vector2f playerCenter;
        Vector2f mousePos;
        Vector2f aimDir;
        Vector2f aimDirNorm;
        float p;

        // line 
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(80, 50), Color::Red),
            sf::Vertex(sf::Vector2f(80, 1600), Color::Red)
        };

        // ami
        Texture love;
        Sprite loveSprite;
        std::vector<Sprite> lovies;

        Texture gameOver;
        Sprite game;

        Texture win;
        Sprite winSprite;
        
        // boss
        Boss boss;
        std::vector<Sprite> bossess;
        bossess.push_back(boss.bossSprite);

        //boss ami 
        Text text2;
        Font font;
        font.loadFromFile("images/Dosis-Bold.ttf");

        while (window.isOpen()) {

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            if (player.points == 500) {
                win.loadFromFile("images/you.png");
                winSprite.setTexture(win);
            }

            if (player.health < 0) {
                gameOver.loadFromFile("images/gameOver.png");
                game.setTexture(gameOver);
            
            }

            // mouse position
            playerCenter = Vector2f(player.sprite.getPosition().x + player.texture.getSize().x - 550, player.sprite.getPosition().y + player.texture.getSize().y - 330);
            mousePos = Vector2f(Mouse::getPosition(window));
            aimDir = mousePos - playerCenter;
            p = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
            aimDirNorm = aimDir / p;
         //   std::cout << aimDirNorm.x << " " << aimDirNorm.y << " \n";

            // enemy boss
            std::cout << "\n bossiin urt ==== " << bossess.size();


            if (player.points >= 10) {

                text2.setFont(font);
                text2.setFillColor(Color::White);
                text2.setString("None");
                text2.setCharacterSize(24);
                text2.setPosition(1700.f, 0.f);

                // text2
                std::stringstream ss1;
                ss1 << "Boss : " << boss.life;
                text2.setString(ss1.str());

                for (size_t i = 0; i < bossess.size(); i++) {
                    bossess[i].move(-0.5f, 0.f);

                    if (bossess[i].getPosition().x <= 130 - bossess[i].getGlobalBounds().width) {
                        bossess.erase(bossess.begin() + i);
                        player.health = -1;
                    }
                    if (bossess[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
                        player.health -= 1;
                    } 
                    
                }
                
            }
           
        // text1
            std::stringstream ss;
            ss << "Points : " << player.points << "\n"
               << "Ninja: "<< player.health;
            object.text1.setString(ss.str());

             // ami 
            if (player.points == 20 || player.points == 50) {
                love.loadFromFile("images/love.png");
                loveSprite.setTexture(love);
                loveSprite.setScale(0.02f, 0.02f);
                loveSprite.setPosition(900.f, 500.f);
                lovies.push_back(loveSprite);
            } 
            if (player.points >20) {

                for (int i = 0; i < lovies.size(); i++) {
                    if (lovies[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
                        player.health = 10;
                        lovies.erase(lovies.begin() + i);

                    }
                }
            }
            // Player move
            if (Keyboard::isKeyPressed(Keyboard::Left))
                player.sprite.move(-10.f, 0.f);
            if (Keyboard::isKeyPressed(Keyboard::Right)) 
                player.sprite.move(10.f, 0.f);
            if (Keyboard::isKeyPressed(Keyboard::Up))
                player.sprite.move(0.f, -10.f);
            if (Keyboard::isKeyPressed(Keyboard::Down))
                player.sprite.move(0.f, 10.f);

            // window collision
              if (player.sprite.getPosition().x <= 0)  // L 
                player.sprite.setPosition(10.f, player.sprite.getPosition().y);
             if (player.sprite.getPosition().x >= window.getSize().x - player.sprite.getGlobalBounds().width) // R
                 player.sprite.setPosition(window.getSize().x - player.sprite.getGlobalBounds().width, player.sprite.getPosition().y);
            if (player.sprite.getPosition().y <= 0) // T
                player.sprite.setPosition(player.sprite.getPosition().x, 0.f);
            if (player.sprite.getPosition().y >= window.getSize().y - player.sprite.getGlobalBounds().height -40.f) // B 
                player.sprite.setPosition(player.sprite.getPosition().x, window.getSize().y -40 - player.sprite.getGlobalBounds().height);


            // enemies
            if (enemy.random < 20)
                enemy.random++;

            if (enemy.random >= 20) {
                 enemy.enemySprite.setPosition(window.getSize().x - enemy.enemySprite.getGlobalBounds().width, rand() % (window.getSize().y -  150));
                enemies.push_back(Sprite(enemy.enemySprite));
                enemy.random = 0;
            }
            if (b1.shootTimer < 15)
                b1.shootTimer++;

            // shooting
            if (Mouse::isButtonPressed(Mouse::Left) && b1.shootTimer >=15)
            {
                b1.s.setPosition(playerCenter);
                b1.currVelocity = aimDirNorm * b1.maxSpeed;
                bullets.push_back(Bullet(b1));
                b1.shootTimer = 0;
            }

            for (size_t i = 0; i < bullets.size(); i++) {

                bullets[i].s.move(bullets[i].currVelocity);

                if (bullets[i].s.getPosition().x < 0 || bullets[i].s.getPosition().x > window.getSize().x
                    || bullets[i].s.getPosition().y< 0 || bullets[i].s.getPosition().y > window.getSize().y)
                {
                    bullets.erase(bullets.begin() + i);
                }
                // hoorondoh morgoldoon     
                else {
                    for (size_t k = 0; k < enemies.size(); k++) {
                        if (bullets[i].s.getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
                        {
                            bullets.erase(bullets.begin() + i);
                            enemies.erase(enemies.begin() + k);
                            player.points += 1;
                            break;
                        }
                    }
                }
            }
           // enemy boss  
            if (player.points >= 10) {
                for (size_t i = 0; i < bullets.size(); i++) {
                    for (size_t k = 0; k < bossess.size(); k++) {
                        if (bullets[i].s.getGlobalBounds().intersects(bossess[k].getGlobalBounds()))
                        {
                            bullets.erase(bullets.begin() + i);
                            boss.life -= 1;
                            std::cout<< "\nboss life: " << boss.life;
                            player.points += 1;
                            break;
                        }
                        if (boss.life == 0 ) {
                            bossess.erase(bossess.begin() + k);
                            player.points = 500;
                        }
                    }
                }
            }
            
            // enemy move and player collision
            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i].move(-6.f, 0.f);

                if (enemies[i].getPosition().x <= 130 - enemies[i].getGlobalBounds().width) {
                    enemies.erase(enemies.begin() + i);
                    player.health -= 1;
                }
                if (enemies[i].getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
                    enemies.erase(enemies.begin() + i);
                    player.health -= 1;
                }
            }

            window.clear();
            window.draw(player.groundSprite);

            // enemy
            for (size_t i = 0; i < enemies.size(); i++) {
                window.draw(enemies[i]);
            }
            // ami 
            for (size_t i = 0; i < lovies.size(); i++) {
                window.draw(lovies[i]);
            }

            //bullets
            for (size_t i = 0; i < bullets.size(); i++)
                window.draw(bullets[i].s);

            // bossess
                if(player.points >= 10)
            for (size_t i = 0; i < bossess.size(); i++)
              window.draw(bossess[i]);
       
            //window.draw(boss.bossSprite);
            // objects
            window.draw(player.sprite);
            window.draw(princess.spriteP);
            window.draw(object.text1);
            window.draw(text2);
            window.draw(line, 2, sf::Lines);
            window.draw(game);
            window.draw(winSprite);
            window.display();


        }
    } 