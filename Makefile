SOURCE_DIR=.
RESCOMP = ../rescomp/target/rescomp.jar
BUILD_DIR = bin
CFG=../dclib/cfg/durango16k.cfg
DCLIB=../dclib/bin
DCINC=../dclib/inc

all: witch.dux

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/background.h: background.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n background -m BACKGROUND -i background.png -o $(BUILD_DIR)/background.h

$(BUILD_DIR)/sprites.h: sprites.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n sprites -m SPRITESHEET -i sprites.png -h 27 -w 30 -o $(BUILD_DIR)/sprites.h
	
$(BUILD_DIR)/witch_sprite.h: witch_sprite.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n witch_sprite -m SPRITESHEET -i witch_sprite.png -h 37 -w 32 -o $(BUILD_DIR)/witch_sprite.h
	
$(BUILD_DIR)/candy.h: candy.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n candy -m SPRITESHEET -i candy.png -h 15 -w 16 -o $(BUILD_DIR)/candy.h
	
$(BUILD_DIR)/skull.h: skull.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n skull -m SPRITESHEET -i skull.png -h 20 -w 20 -o $(BUILD_DIR)/skull.h
	


$(BUILD_DIR)/main.casm: $(SOURCE_DIR)/main.c $(BUILD_DIR) $(BUILD_DIR)/background.h $(BUILD_DIR)/sprites.h $(BUILD_DIR)/witch_sprite.h $(BUILD_DIR)/candy.h $(BUILD_DIR)/skull.h
	cc65 -I $(DCINC) $(SOURCE_DIR)/main.c -t none --cpu 6502 -o $(BUILD_DIR)/main.casm

$(BUILD_DIR)/main.o: $(BUILD_DIR)/main.casm $(BUILD_DIR)
	ca65 -t none $(BUILD_DIR)/main.casm -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/witch.bin: $(BUILD_DIR) $(BUILD_DIR)/main.o
	ld65 -C $(CFG) $(BUILD_DIR)/main.o $(DCLIB)/durango.lib $(DCLIB)/sprites.lib $(DCLIB)/system.lib $(DCLIB)/psv.lib -o $(BUILD_DIR)/witch.bin	

witch.dux: $(BUILD_DIR)/witch.bin $(BUILD_DIR)
	java -jar ${RESCOMP} -m SIGNER -n $$(git log -1 | head -1 | sed 's/commit //' | cut -c1-8) -i $(BUILD_DIR)/witch.bin -o witch.dux

clean:
	rm -Rf $(BUILD_DIR) witch.dux
