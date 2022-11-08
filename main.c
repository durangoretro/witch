#include <sprites.h>
#include <system.h>
#include <psv.h>
#include "bin/background.h"
#include "bin/sprites.h"
#include "bin/witch_sprite.h"

void updatePlayer(void);
int main(void);

sprite player;
sprite pumpkin;

int main() {
    load_background(background);
    clrscr();
    
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
    player.y=50;
    player.width = 32;
    player.height = 37;
    calculate_coords(&player);
    waitFrames(10);
    draw_sprite(&player);
    
    while(1) {
        waitFrames(2);
        move_sprite_right(&pumpkin);
        updatePlayer();
    }
    
        
    return 0;
}

void updatePlayer() {
    unsigned char gamepad;
    
    // Read gamepad
    gamepad=readGamepad(0);
    // Move left
    if(gamepad & BUTTON_LEFT && player.x>0) {
        player.resource = &witch_sprite_0_1;
        move_sprite_left(&player);
    }
    // MOve right
    else if(gamepad & BUTTON_RIGHT && player.x+player.width<128) {
        player.resource = &witch_sprite_0_0;
        move_sprite_right(&player);
    }
}
