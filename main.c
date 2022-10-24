#include <sprites.h>
#include <system.h>
#include <psv.h>
#include "bin/background.h"
#include "bin/sprites.h"

sprite player;

int main(void) {
    load_background(background);
    clrscr();
    
    player.resource = &sprites_0_0;
    player.x=0;
    player.y=50;
    player.width = 30;
    player.height = 27;
    calculate_coords(&player);
    consoleLogWord(player.mem);
    
    waitFrames(10);
    draw_sprite(&player);
    
    while(1) {
	waitFrames(10);
    consoleLogBinary(0x00);
	move_sprite_right(&player);
    consoleLogStr("\n");
    }
    
        
    return 0;
}
