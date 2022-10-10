#include <sprites.h>
#include <system.h>
#include <psv.h>
#include "bin/background.h"

sprite player;

int main(void) {
    load_background(background);
    clrscr();
    
    player.x=0;
    player.y=0;
    player.width = 30;
    player.height = 27;
    calculate_coords(&player);
    consoleLogWord(player.mem);
    
    
    while(1);
    
    return 0;
}
