#include <stdio.h>
#include <stdlib.h>
#include <tonc.h>
#include "Level1.h"

OBJ_ATTR obj_buffer[128];

int copy_completed = 0;
void dma3_handler(){
    copy_completed = 1;
}

void initIrq(){
    irq_init(NULL); // Descomentar si se quiere depurar el codigo (por texto)
		irq_add(II_VBLANK, NULL); // Descomentar si se quiere depurar el codigo (por texto)
    irq_add(II_DMA3, dma3_handler);
}


int main(){
		initIrq();

		srand(time(NULL));
		oam_init(obj_buffer, 128); // initialize oam memory

		REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D |  DCNT_BG0 | DCNT_BG1 | DCNT_MODE0;
		REG_BG1CNT = BG_CBB(1) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;

		firstLevel(obj_buffer, &copy_completed);

	return 0;
}
