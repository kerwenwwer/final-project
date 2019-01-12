#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>              //Our primitive header file
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_acodec.h>
#include "GameObj.h"
//OBJECT INIT
enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE, ESCAPE, ENTER};
enum STATUS{MENU, PLAYING, GAMEOVER, PAUSE};
enum MENUSTATE{START, EXIT, AGAIN, ENDEXIT};
bool keys[7]={false,false,false,false,false,false,false};

//SPACESHIP
class SpaceShip:public GameObj{
    public:
        int lives;
        float speed;
        int boundx;
        int boundy;
        int score;
        ALLEGRO_BITMAP *image_path;
        SpaceShip():GameObj(PLAYER){

        }
};
// BULLET
class Bullet:public GameObj{
    public:
        bool live;
        float speed;

        Bullet():GameObj(BULLENT){

        }
};
//BACKGROUNF 
class BackGround:public GameObj{
    public:
        bool live;
        float speed;
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
        float speed;
        int boundx;
        int boundy;

        EnEmy():GameObj(EMEMY){
            
        }
};

class Comet:public GameObj{
    public:
        bool live;
        float speed;
        int boundx;
        int boundy;

        Comet():GameObj(COMET){

        }
};

class Take_Note:public GameObj{
    public:
        Take_Note():GameObj(NOTE){

        }
};