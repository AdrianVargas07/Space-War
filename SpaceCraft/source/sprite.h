#ifndef SPRITE
#define SPRITE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int contador = 0;
int x = 0;

typedef struct{
	OBJ_ATTR *spriteAttribs;
	int firstAnimCycleFrame;
	int animFrame;
	int posX;
	int posY;
	int isColliding;
	int collided;
}Sprite;

void loadSprite(const unsigned int* tiles, const unsigned int tilesLen, const unsigned int*  pal, const unsigned int panLen){

	dma3_cpy(&tile_mem[4][0], tiles, tilesLen); // copy the sprite into memory (sprite definition)
	dma3_cpy(pal_obj_mem, pal, panLen);		  // copy the part of the palette into memory
}

void initializeSprite(Sprite* sprite, OBJ_ATTR* attribs, int x, int y) {

	sprite->spriteAttribs = attribs;
	sprite->firstAnimCycleFrame = 0;
	sprite->animFrame = 0;
	sprite->posX = x;
	sprite->posY = y;
}

void initializeEnemy(Sprite* sprite, OBJ_ATTR* attribs, int x, int y) {

	sprite->spriteAttribs = attribs;
	sprite->firstAnimCycleFrame = 15 * 8;
	sprite->animFrame = (sprite->animFrame) % 1;
	sprite->posX = x;
	sprite->posY = y;
}

void assignAttributesSprite(Sprite* sprite){

	sprite->spriteAttribs->attr0 = ATTR0_8BPP | ATTR0_SQUARE;
	sprite->spriteAttribs->attr1 = ATTR1_SIZE_16;
	obj_set_pos(sprite->spriteAttribs, sprite->posX, sprite->posY);
}

void assignAttributesSpriteEnemy(Sprite* sprite){

	sprite->spriteAttribs->attr0 = ATTR0_8BPP | ATTR0_SQUARE;
	sprite->spriteAttribs->attr1 = ATTR1_SIZE_16;
	sprite->spriteAttribs->attr2 = ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame * 8), 0, 0);
	obj_set_pos(sprite->spriteAttribs, sprite->posX, sprite->posY);
}

void movement (Sprite* sprite, int level){

	sprite->posX += 3*key_tri_horz();
	sprite->posY += 3*key_tri_vert();
	if (sprite->posX < 0) sprite->posX = 0;
	if (level == 1) {
		if (sprite->posX > 224) sprite->posX = 224;
	} else {
		if (sprite->posX > 112) sprite->posX = 112;
	}
	if (sprite->posY < 0) sprite->posY = 0;
	if (sprite->posY > 144) sprite->posY = 144;
	obj_set_pos(sprite->spriteAttribs, sprite->posX, sprite->posY );

}

void tickEnemyAnimation(Sprite* sprite){
	OBJ_ATTR* spriteAttribs = sprite->spriteAttribs;

	sprite->animFrame++;
	sprite->firstAnimCycleFrame = 8 * 15;
	sprite->animFrame = (sprite->animFrame) % 1;
	spriteAttribs->attr2= ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame*8), 0, 0);

	if(sprite->isColliding){
 		sprite->firstAnimCycleFrame = 8 * 6;
	 	sprite->animFrame = (sprite->animFrame) % 5;
		spriteAttribs->attr2= ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame*8), 0, 0);
	}
}

void tickSpriteAnimation(Sprite* sprite){

 	OBJ_ATTR* spriteAttribs = sprite->spriteAttribs;

  sprite->animFrame++;
	sprite->firstAnimCycleFrame = 8 * 1;
 	sprite->animFrame = (sprite->animFrame) % 3;
 	spriteAttribs->attr2= ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame*8), 0, 0);

 	if(sprite->isColliding){
 		sprite->firstAnimCycleFrame = 8 * 6;
	 	sprite->animFrame = (sprite->animFrame) % 5;
		spriteAttribs->attr2= ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame*8), 0, 0);
	}

 }

void moveAsteroid(Sprite* sprite){

	sprite->posX -= 2;
	obj_set_pos(sprite->spriteAttribs, sprite->posX, sprite->posY );

}

void asteroidRain(Sprite* sprite, OBJ_ATTR* objBuffer){

	x = rand() % 145;

	if(contador == 150){
		initializeSprite(sprite, &objBuffer[1], 250, x);
	 	assignAttributesSprite(sprite); //the sprite is loaded into memory
	  contador = 0;
  }
	contador++;

}

void moveEnemy(Sprite* sprite, int instance, int bigValue){
	if(!sprite->isColliding){
		int i = instance % 2;

		int y = rand() % 30;
		if(bigValue){
			y = 30;
		}
		if (i == 0){
			sprite->posY -= y;
		} else {
			sprite->posY += y;
		}

		if (sprite->posY < 0){
			if(!bigValue){
				sprite->posY += y;
			} else{
				sprite->posY += y * 2;
			}
		}
		if (sprite->posY > 144) {
			if(!bigValue){
				sprite->posY -= y;
			} else{
				sprite->posY -= y * 2;
			}
		}
		obj_set_pos(sprite->spriteAttribs, sprite->posX, sprite->posY );
	}
}

void enemyShot(Sprite* sprite, OBJ_ATTR* objBuffer, int x, int y){
	if(contador == 150){
		initializeSprite(sprite, &objBuffer[3], x - 16, y);
 		assignAttributesSprite(sprite); //the sprite is loaded into memory
		contador = 0;
	}
	contador++;
}

void beamShot(Sprite* sprite, OBJ_ATTR* objBuffer, int x, int y) {

	initializeSprite(sprite, &objBuffer[2], x + 16, y);
	assignAttributesSprite(sprite); //the sprite is loaded into memory

}

void tickSpriteAnimationBeam(Sprite* sprite) {

	OBJ_ATTR* spriteAttribs = sprite->spriteAttribs;

	sprite->animFrame++;
	sprite->firstAnimCycleFrame = 11 * 8;
	sprite->animFrame = (sprite->animFrame) % 3;
	spriteAttribs->attr2 = ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame * 8), 0, 0);

}

void tickSpriteAnimationEnemyShot(Sprite* sprite) {

	OBJ_ATTR* spriteAttribs = sprite->spriteAttribs;

	sprite->animFrame++;
	sprite->firstAnimCycleFrame = 5 * 8;
	sprite->animFrame = (sprite->animFrame) % 1;
	spriteAttribs->attr2 = ATTR2_BUILD(sprite->firstAnimCycleFrame + (sprite->animFrame * 8), 0, 0);

}

void moveBlasts(Sprite* sprite) {

	 if (sprite != NULL) {
		 sprite->posX += 2;
		 obj_set_pos(sprite->spriteAttribs, sprite->posX, sprite->posY);
	 }

}

typedef struct {
	int x, y;
}Point;

int doSpritesOverlap(Sprite* sprite1, Sprite* sprite2){

	Point l1 = {
	 .x = sprite1->posX + 2,
	 .y = sprite1->posY,
	};
	Point r1 = {
	 .x = sprite1->posX + 12,
	 .y = sprite1->posY + 14,
	};
	Point l2 = {
	 .x = sprite2->posX + 2,
	 .y = sprite2->posY,
	};
	Point r2 = {
	 .x = sprite2->posX + 12,
	 .y = sprite2->posY + 14
	};

	if(l1.x >= r2.x || l2.x >= r1.x){
	 return 0;
	}

	if(l1.y >= r2.y || l2.y >= r1.y){
	 return 0;
	}

	return 1;
}
#endif
