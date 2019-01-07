#include<stdio.h>
#include "GameObj.h"
//OBJECT INIT
enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
bool keys[5]={false,false,false,false,false};

//SPACESHIP
class SpaceShip:public GameObj{
    public:
        int lives;
        int speed;
        int boundx;
        int boundy;
        int score;

        SpaceShip():GameObj(PLAYER){

        }
};
// BULLET
class Bullet:public GameObj{
    public:
        bool live;
        int speed;

        Bullet():GameObj(BULLENT){

        }
};
//BACKGROUNF 
class BackGround:public GameObj{
    public:
        bool live;
        int speed;
        int boundx;
        int boundy;
        BackGround():GameObj(BACKGROUNG){

        }
};
//ENEMY
class EnEmy:public GameObj{
    public:
        bool livebegin;
        int lives;
        int speed;
        int boundx;
        int boundy;

        EnEmy():GameObj(EMEMY){
            
        }
};

class Comet:public GameObj{
    public:
        bool live;
        int speed;
        int boundx;
        int boundy;

        Comet():GameObj(COMET){

        }
};