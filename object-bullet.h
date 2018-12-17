#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>              //Our primitive header file
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_acodec.h>
#include"object.h"

#define GAME_TERMINATE 666
#define NUMBER_BULLETS 510
#define NUMBER_BADGUY 10
#define width 600
#define height 800
#define FPS 120

struct Bullet{
    int ID;
    int x;
    int y;
    bool live;
    int speed;

};
Bullet bullet[NUMBER_BULLETS];

//BULLET FUNCTION
void InitBullet(Bullet bullet[],int size){
    for(int i=0;i<size;i++){
        bullet[i].ID=BULLENT;
        bullet[i].speed=10;
        bullet[i].live=false;
    }
}
void DrawBullet(Bullet bullet[],int size){
    for(int i=0;i<size;i++){
        if(bullet[i].live) 
            al_draw_filled_circle(bullet[i].x,bullet[i].y,2,al_map_rgb(253,2,255));
    }
}
void FireBullet(Bullet bullet[],int size,spaceship &ship){
    for(int i=0;i<size;i++){
        if(!bullet[i].live){
            bullet[i].x=ship.x;
            bullet[i].y=ship.y+17;
            bullet[i].live=true;
            break;
        }
    }
}
void UpdateBullet(Bullet bullet[],int size){
    for(int i=0;i<size;i++){
        if(bullet[i].live){
            bullet[i].y-=bullet[i].speed;
            if(bullet[i].y >height)
                bullet[i].live=false;
        }
    }
}