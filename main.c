#include <sprites.h>
#include <system.h>
#include <psv.h>
#include "bin/background.h"
#include "bin/sprites.h"
#include "bin/witch_sprite.h"
#include "bin/candy.h"
#include "bin/skull.h"

// typedefs
typedef struct{
    unsigned char x, y;
    unsigned short mem;
    unsigned char width, height;
    void* resource;
    unsigned char direction;
} s_pumpkin;

typedef struct{
    unsigned char x, y;
    unsigned short mem;
    unsigned char width, height;
    void* resource;
    unsigned char vx;
    unsigned char vy;
    unsigned char good;
} s_candy;

// method declarations
void updatePlayer(void);
void updatePumpkin(void);
void updateCandy(s_candy*);
int main(void);

// global vars
sprite player;
s_pumpkin pumpkin;
s_candy candy;

// Implementation

int main() {
    load_background(background);
    clrscr();
    
    pumpkin.direction=0;
    pumpkin.resource = &sprites_0_0;
    pumpkin.x=0;
    pumpkin.y=5;
    pumpkin.width = 30;
    pumpkin.height = 27;
    calculate_coords(&pumpkin);
    draw_sprite(&pumpkin);
    
    
    player.resource = &witch_sprite_0_0;
    player.x=0;
    player.y=70;
    player.width = 32;
    player.height = 37;
    calculate_coords(&player);
    draw_sprite(&player);
    
    candy.resource  = &candy_0_0;
    candy.x=50;
    candy.y=35;
    candy.vx=0;
    candy.vy=1;
    candy.width=16;
    candy.height=15;
    calculate_coords(&candy);
    draw_sprite(&candy);
    
    while(1) {
        waitFrames(2);
        updateCandy(&candy);
        updatePumpkin();
        updatePlayer();
    }    
        
    return 0;
}

void updatePumpkin() {
    if(pumpkin.x==0) {
        pumpkin.direction=0;
        pumpkin.resource = &sprites_0_0;
    }
    if(pumpkin.x==96) {
        pumpkin.direction=1;
        pumpkin.resource = &sprites_0_2;
    }
    if(pumpkin.direction==0) {
        move_sprite_right(&pumpkin);
    }
    else {
        move_sprite_left(&pumpkin);
    }
}

void initCandy(s_candy *mycandy) {
    mycandy->good = random() & 0x01;
    
    if(mycandy->good==0) {
        mycandy->resource  = &skull_0_0;
        mycandy->width=20;
        mycandy->height=20;
    }
    else {
        mycandy->resource  = &candy_0_0;
        mycandy->width=16;
        mycandy->height=15;
    }
    
    mycandy->x=pumpkin.x+10;
    mycandy->y=35;
    calculate_coords(mycandy);
    draw_sprite(mycandy);
}

void updateCandy(s_candy *mycandy) {
    if(candy.vx==1) {
        move_sprite_right(mycandy);
    }
    if(candy.vx==-1) {
        move_sprite_left(mycandy);
    }
    if(candy.vy==1) {
        move_sprite_down(mycandy);
    }
    if(candy.y==113) {
        initCandy(mycandy);
    }
}

void updatePlayer() {
    unsigned char gamepad;
    
    // Read gamepad
    gamepad=readGamepad(0);
    // Move left
    if(gamepad & BUTTON_LEFT && player.x>0) {
        player.resource = &witch_sprite_0_1;
        move_sprite_left(&player);
        move_sprite_left(&player);
        move_sprite_left(&player);
    }
    // MOve right
    else if(gamepad & BUTTON_RIGHT && player.x+player.width<128) {
        player.resource = &witch_sprite_0_0;
        move_sprite_right(&player);
        move_sprite_right(&player);
        move_sprite_right(&player);
    }
    else if(gamepad & BUTTON_DOWN && player.y+player.height<128) {
        player.resource = &witch_sprite_0_0;
        move_sprite_down(&player);
        move_sprite_down(&player);
    }
    else if(gamepad & BUTTON_UP && player.y>35) {
        player.resource = &witch_sprite_0_0;
        move_sprite_up(&player);
        move_sprite_up(&player);
    }
    else {
        draw_sprite(&player);
    }
}
