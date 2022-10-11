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
    player.y=0;
    player.width = 30;
    player.height = 27;
    calculate_coords(&player);
    
	draw_sprite(&player);
	
    waitFrames(10);
	player.resource = &sprites_0_1;
	draw_sprite(&player);

	waitFrames(10);
	player.resource = &sprites_0_2;
	draw_sprite(&player);
    
    
    while(1);
    
    return 0;
}
