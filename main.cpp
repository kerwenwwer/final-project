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
#define NUMBER_BADGUY 15
#define width 600
#define height 800
#define FPS 60



int pos_x, pos_y; // The position of rectangle's left-up corner.
bool redraw=true;
bool done=false;

//announce function for game base
void game_destroy();
void InitShip(SpaceShip &ship);
void DrawSip(SpaceShip &ship);
void MoveUp(SpaceShip &ship);
void MoveDown(SpaceShip &ship);
void MoveLeft(SpaceShip &ship);
void MoveRight(SpaceShip &ship);

//Announce function for bullet
void InitBullet(Bullet bullet[],int size);
void DrawBullet(Bullet bullet[],int size);
void FireBullet(Bullet bullet[],int size,SpaceShip &ship);
void UpdateBullet(Bullet bullet[],int size);
void CollideBullet();
//Announce function for badguy
void InitBackGround(BackGround background[],int size);
void DrawBackGround(BackGround background[],int size);
void StartBackGround(BackGround background[],int size);
void UpdateBackGround(BackGround background[],int size);
//INIT ENEMY
void InitEnemy(EnEmy &enemy);
void DrawEnemy(EnEmy &enemy);
void StartEnemy(EnEmy &enemy);
void MoveEnemyUp(EnEmy &enemy);
void MoveEnemyDown(EnEmy &enemy);
void MoveEnemyLeft(EnEmy &enemy);
void MoveEnemyRight(EnEmy &enemy);
//init object
SpaceShip ship;
Bullet bullet[NUMBER_BULLETS];
BackGround background[NUMBER_BADGUY];
EnEmy enemy;

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_FONT *font=NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timerfps=NULL;

//MAIN FUNCTION
int main(int argc, char *argv[]) {
    if (!al_init()) {
        return -1;
    }
    display = al_create_display(width, height);
    
    if(!display){
        return -1;
    }
    al_init_primitives_addon();
    al_install_keyboard();

    event_queue=al_create_event_queue();
    timerfps=al_create_timer(1.0/FPS);
    //INIT ALL THING ON GAME
    srand(time(NULL));
    InitShip(ship);
    InitBullet(bullet,NUMBER_BULLETS);
    InitBackGround(background,NUMBER_BADGUY);

    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_timer_event_source(timerfps));

    al_start_timer(timerfps);

    while(!done){
        
        al_wait_for_event(event_queue,&event);

        if(event.type==ALLEGRO_EVENT_TIMER){
            redraw=true;
            if(keys[UP])
                MoveUp(ship);
            if(keys[DOWN])
                MoveDown(ship);
            if(keys[LEFT])
                MoveLeft(ship);
            if(keys[RIGHT])
                MoveRight(ship);
            UpdateBullet(bullet,NUMBER_BULLETS);
            StartBackGround(background,NUMBER_BADGUY);
            UpdateBackGround(background,NUMBER_BADGUY);

        }else if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            done=true;    
        }else if(event.type==ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    done=true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP]=true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN]=true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT]=true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT]=true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE]=true;
                    FireBullet(bullet,NUMBER_BULLETS,ship);
                    break;
                
            }
        }else if(event.type==ALLEGRO_EVENT_KEY_UP){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    done=false;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP]=false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN]=false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT]=false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT]=false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE]=false;
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw=false;
            DrawSip(ship);
            DrawBullet(bullet,NUMBER_BULLETS);
            DrawBackGround(background,NUMBER_BADGUY);
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
    al_destroy_display(display);
}

//SHIP FUNCTION
void InitShip(SpaceShip &ship){
    ship.x=width/2;
    ship.y=height-40;
    ship.ID=PLAYER;
    ship.lives=3;
    ship.speed=7;
    ship.boundx=6;
    ship.boundy=7;
    ship.score=0;
}

void DrawSip(SpaceShip &ship){
    al_draw_filled_rectangle(ship.x-9,ship.y-5,ship.x-7,ship.y+10,al_map_rgb(255,0,255));
    al_draw_filled_rectangle(ship.x+9,ship.y-5,ship.x+7,ship.y+10,al_map_rgb(255,0,255));

    al_draw_filled_triangle(ship.x-17,ship.y+12,ship.x,ship.y-12,ship.x+17,ship.y+12,al_map_rgb(0,255,0));
    al_draw_filled_rectangle(ship.x-2,ship.y-12,ship.x+2,ship.y+15,al_map_rgb(0,0,255));
}
void MoveUp(SpaceShip &ship){
    ship.y-=ship.speed;
    ship.y=(ship.y<15)?15:ship.y;
}
void MoveDown(SpaceShip &ship){
    ship.y+=ship.speed;
    ship.y=(ship.y>height-40)?height-40:ship.y;
}
void MoveLeft(SpaceShip &ship){
    ship.x-=ship.speed;
    ship.x=(ship.x<17)?0:ship.x;
}
void MoveRight(SpaceShip &ship){
    ship.x+=ship.speed;
    ship.x=(ship.x>width)?width:ship.x;   
}


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
            al_draw_filled_circle(bullet[i].x-9,bullet[i].y,3,al_map_rgb(253,2,255));
            al_draw_filled_circle(bullet[i].x+9,bullet[i].y,3,al_map_rgb(253,2,255));
    }
}
void FireBullet(Bullet bullet[],int size,SpaceShip &ship){
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

//BACKGROUND FUNCTION
void InitBackGround(BackGround background[],int size){
    for(int i=0;i<size;i++){
        background[i].ID=BACKGROUNG;
        background[i].live=false;
        background[i].speed=5;
    }
}
void DrawBackGround(BackGround background[],int size){
    for(int i=0;i<size;i++){
        al_draw_filled_circle(background[i].x,background[i].y,5,al_map_rgb(99,99,99));
    }
}
void StartBackGround(BackGround background[],int size){
    for(int i=0;i<size;i++){
        if(rand()%500==0){
            background[i].live=true;
            background[i].y=20;
            background[i].x=30+rand()%(width-60);
            break;
        }
    }
}
void UpdateBackGround(BackGround background[],int size){
    for(int i=0;i<size;i++){
        if(background[i].live){
            background[i].y+=background[i].speed;
            if(background[i].y>height+40)
                background[i].live=false;
        }
    }
}

//ENEMY FUNCTIONS
void InitEnemy(EnEmy &enemy){
    enemy.livebegin=false;
    enemy.x=10+rand()%(width-40);
    enemy.y=(rand()%100)+1;
    enemy.ID=EMEMY;
    enemy.speed=5;
    enemy.lives=50;
}
void DrawEnemy(EnEmy &enemy){
    al_draw_filled_circle(enemy.x,enemy.y,10,al_map_rgb(255,0,0));
}
void StartEnemy(EnEmy &enemy){
    
}
void MoveEnemyUp(EnEmy &enemy){

}
void MoveEnemyDown(EnEmy &enemy){

}
void MoveEnemyLeft(EnEmy &enemy){
}
void MoveEnemyRight(EnEmy &enemy){

}