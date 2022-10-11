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
    consoleLogDecimal(0x00);
    startStopwatch();
    draw_sprite(&player);
    stopStopwatch();
    
    
    while(1);
    
    return 0;
}
