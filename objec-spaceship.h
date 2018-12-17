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
enum ID{PLAYER,BULLENT,EMEMY};
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

spaceship ship;
void InitShip(spaceship &ship){
    ship.x=width/2;
    ship.y=height-40;
    ship.ID=PLAYER;
    ship.lives=3;
    ship.speed=7;
    ship.boundx=6;
    ship.boundy=7;
    ship.score=0;
}

void DrawSip(spaceship &ship){
    //al_draw_filled_rectangle(ship.x,ship.y-9,ship.x+10,ship.y-7,al_map_rgb(255,0,255));
    //al_draw_filled_rectangle(ship.x,ship.y+9,ship.x+10,ship.y+7,al_map_rgb(255,0,255));
    al_draw_filled_rectangle(ship.x-9,ship.y-5,ship.x-7,ship.y+10,al_map_rgb(255,0,255));
    al_draw_filled_rectangle(ship.x+9,ship.y-5,ship.x+7,ship.y+10,al_map_rgb(255,0,255));


    //al_draw_filled_triangle(ship.x-12,ship.y-17,ship.x+12,ship.y,ship.x-12,ship.y+17,al_map_rgb(0,255,0));
    //al_draw_filled_rectangle(ship.x-12,ship.y-2,ship.x+15,ship.y+2,al_map_rgb(0,0,255));
    al_draw_filled_triangle(ship.x-17,ship.y+12,ship.x,ship.y-12,ship.x+17,ship.y+12,al_map_rgb(0,255,0));
    al_draw_filled_rectangle(ship.x-2,ship.y-12,ship.x+2,ship.y+15,al_map_rgb(0,0,255));
}