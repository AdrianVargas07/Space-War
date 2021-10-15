#ifndef BACKGROUND
#define BACKGROUND

#include <stdio.h>
#include <string.h>
#include "space.h"
#include "inicio.h"
#include "winner.h"
#include "loser.h"
#include "space2.h"
#include "level2image.h"

void loadBackground( int i){

	if (i == 0){ //start
    dma3_cpy(pal_bg_mem, inicioPal, inicioPalLen);
		dma3_cpy(&tile_mem[1][0], inicioTiles, inicioTilesLen);
		dma3_cpy(&se_mem[30][0], inicioMap, inicioMapLen);
	}
	else if (i == 1){ // space first level
		dma3_cpy(pal_bg_mem, spacePal, spacePalLen);
		dma3_cpy(&tile_mem[1][0], spaceTiles, spaceTilesLen);
		dma3_cpy(&se_mem[30][0], spaceMap, spaceMapLen);
	}
	else if (i == 2){ //winner
		dma3_cpy(pal_bg_mem, winnerPal, winnerPalLen);
		dma3_cpy(&tile_mem[1][0], winnerTiles, winnerTilesLen);
		dma3_cpy(&se_mem[30][0], winnerMap, winnerMapLen);
	}
	else if (i == 3){ //loser
		dma3_cpy(pal_bg_mem, loserPal, loserPalLen);
		dma3_cpy(&tile_mem[1][0], loserTiles, loserTilesLen);
		dma3_cpy(&se_mem[30][0], loserMap, loserMapLen);
	}else if (i == 4){ //sapce second level
		dma3_cpy(pal_bg_mem, space2Pal, space2PalLen);
		dma3_cpy(&tile_mem[1][0], space2Tiles, space2TilesLen);
		dma3_cpy(&se_mem[30][0], space2Map, space2MapLen);
	}else if(i == 5){
		dma3_cpy(pal_bg_mem, level2imagePal, level2imagePalLen);
		dma3_cpy(&tile_mem[1][0], level2imageTiles,level2imageTilesLen);
		dma3_cpy(&se_mem[30][0], level2imageMap, level2imageMapLen);
	}
}

void moveBackground(int speed){

	REG_BG1HOFS += speed; //background movement
}

void resetPositionBg(){

	REG_BG1HOFS = 0;
}

#endif
