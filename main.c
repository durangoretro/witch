#include <sprites.h>
#include <system.h>
#include <glyph.h>
#include <font.h>
#include <qgraph.h>
#include <music.h>
#include <psv.h>
#include "bin/background.h"
#include "bin/sprites.h"
#include "bin/witch_sprite.h"
#include "bin/candy.h"
#include "bin/skull.h"
#include "bin/title.h"

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
    unsigned char active;
} s_candy;

typedef struct{
    unsigned char x, y;
    unsigned short mem;
    unsigned char width, height;
    void* resource;
    unsigned char vx;
    unsigned char active;
} s_bullet;

// method declarations
void updatePlayer(void);
void updatePumpkin(void);
void updateCandy(s_candy*);
void updateBullet(void);
void initCandy(s_candy*);
void updateScore(void);
void checkCols(s_candy*);
void displayTitle(void);
int main(void);

// global vars
sprite player;
s_pumpkin pumpkin;
s_candy candy, candy2;
s_bullet bullet;
char player_vx;
long score;
long candy_points=1;
rectangle rect;
char build_hash[17];

const unsigned char bullet_sprite[1] = {RED};
const unsigned char clinc[4] = {LA5, FUSA, 0xff,0xff};

// Implementation

int main() {
    displayTitle();
    
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
    player.x=50;
    player.y=70;
    player.width = 32;
    player.height = 37;
    player_vx = 1;
    calculate_coords(&player);
    draw_sprite(&player);
    
    candy.vx=0;
    candy.vy=1;
    initCandy(&candy);
    
    candy2.active=1;
    candy2.vx=0;
    candy2.vy=1;
    candy2.resource  = &candy_0_0;
    candy2.width=16;
    candy2.height=15;
    candy2.x=pumpkin.x+10;
    candy2.y=55;
    calculate_coords(&candy2);
    draw_sprite(&candy2);
    
    bullet.active=0;
    bullet.x=0;
    bullet.y=0;
    bullet.vx=1;
    bullet.width = 2;
    bullet.height = 1;
    bullet.resource = &bullet_sprite;
    
    rect.x=78;
    rect.y=118;
    rect.width=50;
    rect.height=10;
    rect.color=BLACK;
    drawRect(&rect);
    
    
    while(1) {
        waitFrames(2);
        updateCandy(&candy);
        updateCandy(&candy2);
        updatePumpkin();
        updatePlayer();
        updateBullet();
        checkCols(&candy);
        checkCols(&candy2);
        updateScore();
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
    //clean_sprite(mycandy);
    mycandy->good = random() & 0x01;
    mycandy->active=1;
    
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

void checkCols(s_candy* mycandy) {
    if(mycandy->good && mycandy->active) {
        if(check_collisions(mycandy, &player)) {
            mycandy->active=0;
            clean_sprite(mycandy);
            addBCD(&score, &candy_points);
            playMelody(clinc);
        }
    }
    else if(!mycandy->good && mycandy->active) {
        if(check_collisions(mycandy, &bullet)) {
            bullet.active=0;
            clean_sprite(&bullet);      
            clean_sprite(mycandy);
            mycandy->good=1;
            mycandy->resource  = &candy_0_0;
            mycandy->width=16;
            mycandy->height=15;
            draw_sprite(mycandy);
        }
        if(check_collisions(mycandy, &player)) {
            mycandy->active=0;
            clean_sprite(mycandy);
            subBCD(&score, &candy_points);
        }
    }
}

void updateCandy(s_candy *mycandy) {
    if(mycandy->active==0) {
        mycandy->y++;
        if(mycandy->y==108) {
            initCandy(mycandy);
        }
        return;
    }
    if(mycandy->vx==1) {
        move_sprite_right(mycandy);
    }
    if(mycandy->vx==-1) {
        move_sprite_left(mycandy);
    }
    if(mycandy->vy==1) {
        move_sprite_down(mycandy);
    }
    if(mycandy->y==108) {
        stamp_sprite(mycandy);
        drawRect(&rect);
        initCandy(mycandy);
    }
}

void updatePlayer() {
    unsigned char gamepad;
    
    // Read gamepad
    gamepad=readGamepad(0);
    // Move left
    if((gamepad & BUTTON_LEFT || readKeyboard(ROW_KEY_O) & KEY_O) && player.x!=2) {
        player.resource = &witch_sprite_0_1;
        move_sprite_left(&player);
        move_sprite_left(&player);
        move_sprite_left(&player);
        player_vx=-1;
    }
    // Move right
    else if((gamepad & BUTTON_RIGHT || readKeyboard(ROW_KEY_P) & KEY_P) && player.x!=98) {
        player.resource = &witch_sprite_0_0;
        move_sprite_right(&player);
        move_sprite_right(&player);
        move_sprite_right(&player);
        player_vx=1;
    }
    else if((gamepad & BUTTON_DOWN || readKeyboard(ROW_KEY_A) & KEY_A) && player.y+player.height<128) {
        player.resource = &witch_sprite_0_0;
        move_sprite_down(&player);
        move_sprite_down(&player);
    }
    else if((gamepad & BUTTON_UP || readKeyboard(ROW_KEY_Q) & KEY_Q) && player.y>35) {
        player.resource = &witch_sprite_0_0;
        move_sprite_up(&player);
        move_sprite_up(&player);
    }
    
    else if(gamepad & BUTTON_A) {
        if(bullet.active==0) {
            bullet.active=1;
            bullet.y=player.y+23;
            bullet.vx=player_vx;
            if(player_vx==1) {
                bullet.x=player.x+player.width;
            }
            else {
                bullet.x=player.x;
            }
            
            draw_sprite(&bullet);
        }
    }
    else {
        draw_sprite(&player);
    }
}

void updateBullet() {
    if(bullet.active) {
        if(bullet.vx==1) {
           move_sprite_right(&bullet); 
        }
        else {
            move_sprite_left(&bullet);
        }
        if(bullet.x==130 || bullet.x==0xfe) {
            bullet.active=0;
        }
    }
}

void displayTitle() {
    render_image(title);
    getBuildVersion(build_hash);
    printStr(16, 110, font, LIME, BLACK, build_hash);
    waitStart();
}

void updateScore() {
    printBCD(80, 119, font, ORANGE, BLACK, score);
}
