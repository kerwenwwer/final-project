#include<stdio.h>
//OBJECT INIT
enum ID{PLAYER,BULLENT,BACKGROUNG,EMEMY};
enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
bool keys[5]={false,false,false,false,false};

//SPACESHIP
struct spaceship{
    int ID;
    int x;
    int y;
    int lives;
    int speed;
    int boundx;
    int boundy;
    int score;
};
// BULLET
struct Bullet{
    int ID;
    int x;
    int y;
    bool live;
    int speed;

};
//BACKGROUNF 
struct BackGround{
    int ID;
    int x;
    int y;
    bool live;
    int boundx;
    int boundy;
    int speed;
};
//ENEMY

