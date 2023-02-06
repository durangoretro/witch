#include <sprites.h>
#include <system.h>
#include <psv.h>
#include "bin/background.h"
#include "bin/sprites.h"
#include "bin/witch_sprite.h"

void updatePlayer(void);
void updatePumpkin(void);
int main(void);

typedef struct{
    unsigned char x, y;
    unsigned short mem;
    unsigned char width, height;
    void* resource;
    unsigned char direction;
} s_pumpkin;

sprite player;
s_pumpkin pumpkin;

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
    consoleLogWord(pumpkin.mem);
    
    waitFrames(10);
    draw_sprite(&pumpkin);
    
    
    player.resource = &witch_sprite_0_0;
    player.x=0;
    player.y=70;
    player.width = 32;
    player.height = 37;
    calculate_coords(&player);
    waitFrames(10);
    draw_sprite(&player);
    
    while(1) {
        waitFrames(2);
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
}
