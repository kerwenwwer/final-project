//
//  main.cpp
//  Allegro Game 
//  Using Allegro API 
//
//  Created by Kerwin Tsai on 15/11/2018.
//  Copyright © 2018 Kerwin Tsai. All rights reserved.
//
#include<stdio.h>
#include<math.h>
#include "sys/types.h"
#include "sys/sysinfo.h"
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>              
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_ttf.h>    
#include<allegro5/allegro_acodec.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include"object.h"

#define GAME_TERMINATE 666
#define NUMBER_BULLETS 10
#define NUMBER_BADGUY 10
#define NUMBER_COMET 10
#define width 600
#define height 900
#define FPS 60



int pos_x, pos_y; // The position of rectangle's left-up corner.
bool redraw = true;
bool Done = false;
bool Game_Over = false;
int ImageRad = 2;
int ImageWidth, ImageHight;
int state = MENU;
float GameTime = 0;
int Frames = 0;
int GameFPS = 0;
int menustate = START;

//announce function for game base
void ConsoleLog(int &state, int newSate);
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
void CollideBullet(Bullet bullet[],int bSize,Comet comets[],int cSize, SpaceShip &ship);
//Announce function for badguy
void InitComet(Comet comets[],int size);
void DrawComet(Comet comets[],int size);
void StartComet(Comet comets[],int size);
void UpdateComet(Comet comets[],int size);
void CollideComet(Comet comet[],int cSize,SpaceShip &ship);
/*void InitEnemy(EnEmy &enemy);
void DrawEnemy(EnEmy &enemy);
void StartEnemy(EnEmy &enemy);
void MoveEnemyUp(EnEmy &enemy);
void MoveEnemyDown(EnEmy &enemy);
void MoveEnemyLeft(EnEmy &enemy);
void MoveEnemyRight(EnEmy &enemy);*/
void InitNote(Take_Note &take_note);
void DrawNote(Take_Note &take_note);

void DrawMenu();
void DownNote(Take_Note &take_note);
void UpNote(Take_Note &take_note);
void ShowGameMessage();
//init object
SpaceShip ship;
Bullet bullet[NUMBER_BULLETS];
//BackGround background[NUMBER_BADGUY];
Comet comets[NUMBER_COMET];
Take_Note take_note;

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_FONT* font = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER* timerfps = NULL;
ALLEGRO_TIMER* timerflip = NULL;
ALLEGRO_FONT* font_ARCADECLASSIC_30px = NULL;
ALLEGRO_FONT* font_monaco_25px = NULL;
ALLEGRO_FONT* font_ARCADECLASSIC_50px = NULL;
ALLEGRO_BITMAP* plane = NULL;
ALLEGRO_BITMAP* get_screen = NULL;

//MAIN FUNCTION
int main(int argc, char *argv[]) {
    printf("[%s:%s] \n",__FILE__,__DATE__);
    printf("Game Start\n");


    if (!al_init()) {
        printf("Game engine Init Error!\n");
        return -1;
    }
    display = al_create_display(width, height);
    
    if(!display){
        printf("Init Display Error\n");
        return -1;
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_image_addon();

    plane = al_load_bitmap("plane1.png");
    //get_screen = al_get_target_bitmap();

    event_queue = al_create_event_queue();
    timerfps = al_create_timer(1.0/FPS);
    timerflip = al_create_timer(1);
    font_ARCADECLASSIC_30px = al_load_font("ARCADECLASSIC.ttf", 30, 0);
    font_monaco_25px = al_load_font("monaco.ttf", 25, 0);
    font_ARCADECLASSIC_50px = al_load_font("ARCADECLASSIC.ttf", 50, 0);
    ImageWidth = al_get_bitmap_width(plane);
    ImageHight = al_get_bitmap_height(plane);

    //INIT ALL THING ON GAME
    srand(time(NULL));
    InitShip(ship);
    InitBullet(bullet,NUMBER_BULLETS);
    InitComet(comets,NUMBER_COMET);
    InitNote(take_note);

    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_timer_event_source(timerfps));
    al_register_event_source(event_queue,al_get_timer_event_source(timerflip));
    
    al_start_timer(timerfps);
    GameTime = al_current_time(); 

    while(!Done){       
        al_wait_for_event(event_queue,&event);

        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;

            //UPDATE FPS
            Frames++;
            if(al_current_time() - GameTime >= 1){
                GameTime = al_current_time();
                GameFPS = Frames;
                Frames = 0;
            }
            //SHOW MEMORY


            //GAME STATE
            if(state == MENU){
                if(keys[ENTER]){
                    if(menustate == START){
                        state = PLAYING;
                    }else{
                        Done = true;
                    }
                }
                if(keys[DOWN]){
                    DownNote(take_note);
                    menustate = EXIT;
                       
                }
                if(keys[UP]){
                    UpNote(take_note);
                    menustate = START;
                      
                }

            }else if(state == PLAYING){
                //getbitmap();
                
                if(keys[ESCAPE]) state = GAMEOVER;
                else if(ship.lives <= 0) state = GAMEOVER;
                else{
                    if(keys[UP])
                        MoveUp(ship);
                    if(keys[DOWN])
                        MoveDown(ship);
                    if(keys[LEFT])
                        MoveLeft(ship);
                    if(keys[RIGHT])
                        MoveRight(ship);
                    if(keys[SPACE]){
                    }
                    UpdateBullet(bullet, NUMBER_BULLETS);
                    StartComet(comets, NUMBER_COMET);
                    UpdateComet(comets, NUMBER_COMET);
                    CollideBullet(bullet, NUMBER_BULLETS, comets, NUMBER_COMET, ship);
                    CollideComet(comets, NUMBER_COMET, ship);
                }
            }else if(state == PAUSE){
                
            }else if(state == GAMEOVER){
                if(keys[SPACE])
                    Done = true;
            }
        }else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            Done = true;    
        }else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    keys[ESCAPE] = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = true;
                    break;
                case ALLEGRO_KEY_ENTER:
                    keys[ENTER] = true;
                    break;
                
            }
        }else if(event.type == ALLEGRO_EVENT_KEY_UP){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    keys[ESCAPE] = true;
                    break;
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = false;
                    FireBullet(bullet,NUMBER_BULLETS,ship);
                    break;
                case ALLEGRO_KEY_ENTER:
                    keys[ENTER] = false;
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue)){
            redraw = false;
            
            if(state == MENU){
                DrawMenu();
                DrawNote(take_note);
                
            }else if(state == PLAYING){
                
                DrawSip(ship);
                DrawBullet(bullet,NUMBER_BULLETS);
                DrawComet(comets,NUMBER_COMET);
                ShowGameMessage();

            }else if(state == GAMEOVER){
                al_draw_textf(font_ARCADECLASSIC_50px, al_map_rgb(255, 0, 0), width/2, height/2-100, ALLEGRO_ALIGN_CENTER, "Game Over");
                al_draw_textf(font_ARCADECLASSIC_30px, al_map_rgb(0, 255, 255), width/2, height/2+20, ALLEGRO_ALIGN_CENTER, "Your Score are %i", ship.score);
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_destroy_display(display);
    return 0;
}

void DrawMenu(void){
    al_draw_textf(font_ARCADECLASSIC_50px, al_map_rgb(0, 255, 255), width/2, height/4+30, ALLEGRO_ALIGN_CENTER, "Final Project");
    if(menustate == START){
        al_draw_textf(font_ARCADECLASSIC_50px, al_map_rgb(0, 255, 255), width/2+5, height/2-40, ALLEGRO_ALIGN_CENTER, "START");
        al_draw_textf(font_ARCADECLASSIC_50px, al_map_rgb(40, 40, 255), width/2+5, height/2+60, ALLEGRO_ALIGN_CENTER, "EXIT");
        al_draw_textf(font_ARCADECLASSIC_30px, al_map_rgb(0, 255, 255), width/2, height/4*3, ALLEGRO_ALIGN_CENTER, "Press space to start");
    }else{
        al_draw_textf(font_ARCADECLASSIC_50px, al_map_rgb(40, 40, 255), width/2+5, height/2-40, ALLEGRO_ALIGN_CENTER, "START");
        al_draw_textf(font_ARCADECLASSIC_50px, al_map_rgb(0, 255, 255), width/2+5, height/2+60, ALLEGRO_ALIGN_CENTER, "EXIT");
        al_draw_textf(font_ARCADECLASSIC_30px, al_map_rgb(0, 255, 255), width/2, height/4*3, ALLEGRO_ALIGN_CENTER, "Press space to exit");    
    }
}

void ShowGameMessage(void){
    al_draw_textf(font_ARCADECLASSIC_30px, al_map_rgb(255, 0, 255), 5, height-25, 0 ,"FPS %i", GameFPS);
    al_draw_textf(font_ARCADECLASSIC_30px, al_map_rgb(0, 255, 255), 50, 20, ALLEGRO_ALIGN_CENTER, "Score %i", ship.score);
    if(ship.lives >= 10){
        al_draw_textf(font_ARCADECLASSIC_30px, al_map_rgb(0, 255, 255), 50, 50, ALLEGRO_ALIGN_CENTER, "HP %i", ship.lives);
    }else{ 
        if(event.type == ALLEGRO_EVENT_TIMER){
            al_draw_textf(font_ARCADECLASSIC_30px, al_map_rgb(255, 48, 48), 50, 50, ALLEGRO_ALIGN_CENTER, "HP %i", ship.lives);
        }
    }
}

void InitNote(Take_Note &take_note){
    take_note.ID = NOTE;
    take_note.x = width/2+5;
    take_note.y = height/2-20;
}

void DrawNote(Take_Note &take_note){
    al_draw_rectangle(take_note.x-150, take_note.y+40, take_note.x+150, take_note.y-40, al_map_rgb(0,255,255),0); 
}

void DownNote(Take_Note &take_note){
    if(menustate != EXIT){
        take_note.y += 100;
    }
}

void UpNote(Take_Note &take_note){
    if(menustate != START){
        take_note.y -= 100;
    }
}
//SHIP FUNCTION
void InitShip(SpaceShip &ship){
    ship.x = width/2;
    ship.y = height-40;
    ship.ID = PLAYER;
    ship.lives = 12;
    ship.speed = 5.46;
    ship.boundx = 7;
    ship.boundy = 6;
    ship.score = 0;
}
void DrawSip(SpaceShip &ship){
    al_draw_bitmap(plane, ship.x-ImageWidth/2, ship.y-ImageHight/2, 0);
}
void MoveUp(SpaceShip &ship){
    ship.y -= ship.speed;
    ship.y = (ship.y < 15) ? 15 : ship.y;
}
void MoveDown(SpaceShip &ship){
    ship.y += ship.speed;
    ship.y = (ship.y > height-40) ? height-40 : ship.y;
}
void MoveLeft(SpaceShip &ship){
    ship.x -= ship.speed;
    ship.x = (ship.x < 17) ? 0 : ship.x;
}
void MoveRight(SpaceShip &ship){
    ship.x += ship.speed;
    ship.x = (ship.x > width) ? width : ship.x;   
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
            al_draw_filled_circle(bullet[i].x,bullet[i].y,3,al_map_rgb(253,2,255));
            //al_draw_filled_circle(bullet[i].x+9,bullet[i].y,3,al_map_rgb(253,2,255));
    }
}
void FireBullet(Bullet bullet[],int size,SpaceShip &ship){
    for(unsigned int i = 0;i < size; i++){
        if(!bullet[i].live){
            bullet[i].x = ship.x;
            bullet[i].y = ship.y - ImageHight/2; 
            bullet[i].live = true;
            break;
        }
    }
}
void UpdateBullet(Bullet bullet[],int size){
    for(int i=0;i<size;i++){
        if(bullet[i].live){
            bullet[i].y-=bullet[i].speed;
            if(bullet[i].y <10)
                bullet[i].live=false;

        }
    }
}
void CollideBullet(Bullet bullet[],int bSize,Comet comets[],int cSize, SpaceShip &ship){
    for(unsigned int i = 0; i < bSize; i++){
        if(bullet[i].live){
            for(int j = 0; j < cSize; j++){
                if(comets[j].live){
                    if(bullet[i].x < (comets[j].x + comets[j].boundx) &&
                        bullet[i].x > (comets[j].x - comets[j].boundx) &&
                        bullet[i].y < (comets[j].y + comets[j].boundy) &&
                        bullet[i].y > (comets[j].y - comets[j].boundy)){

                            bullet[i].live = false;
                            comets[j].live = false;
                            ship.score++;

                    }
                }
            }
        }
    }
}

//COMET FUNCTION
void InitComet(Comet comets[],int size){
    for(int i=0;i<size;i++){
        comets[i].ID = COMET;
        comets[i].live = false;
        comets[i].speed = 3.256;
        comets[i].boundx = 18;
        comets[i].boundy = 18;
    }
}
void DrawComet(Comet comets[],int size){
    for(int i=0;i<size;i++){
        if(comets[i].live)
            al_draw_filled_circle(comets[i].x,comets[i].y,18,al_map_rgb(99,99,99));
    }
}
void StartComet(Comet comets[],int size){
    for(int i = 0; i < size; i++){
        if(!comets[i].live){
            if(rand()%500 == 0){
                comets[i].live = true;
                comets[i].y = 30;
                comets[i].x = 30 + rand() % (width - 60);
                break;
            }
        }
    }
}
void UpdateComet(Comet comets[],int size){
    for(int i = 0; i < size; i++){
        if(comets[i].live){
            comets[i].y += comets[i].speed;
            if(comets[i].y > height)
                comets[i].live = false;
        }
    }
}
void CollideComet(Comet comets[],int cSize,SpaceShip &ship){
    for(unsigned int i=0;i<cSize;i++){
        if(comets[i].live){
            if(comets[i].x+comets[i].boundx>ship.x-ship.boundx&&
                comets[i].x-comets[i].boundx<ship.x+ship.boundx&&
                comets[i].y+comets[i].boundy>ship.y-ship.boundy&&
                comets[i].y-comets[i].boundy<ship.y+ship.boundy){
                    ship.lives--;
                    comets[i].live=false;
                }else if(comets[i].y > height+20){
                    comets[i].live=false;
                    ship.lives--;
                    
                }
        }
    }
}

void ConsoleLog(int &state, int newSate){
    if(state == MENU){
        printf("Enter MENU\n");
    }else if(state == PLAYING){
        printf("Enter PLAYING\n");
    }else if(state == PAUSE){
        printf("Enter PAUSE\n");
    }
}