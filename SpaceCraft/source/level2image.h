
//{{BLOCK(level2image)

//======================================================================
//
//	level2image, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 34 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 2176 + 2048 = 4736
//
//	Time-stamp: 2020-11-29, 12:40:28
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LEVEL2IMAGE_H
#define GRIT_LEVEL2IMAGE_H

#define level2imageTilesLen 2176
extern const unsigned int level2imageTiles[544];

#define level2imageMapLen 2048
extern const unsigned int level2imageMap[512];

#define level2imagePalLen 512
extern const unsigned int level2imagePal[128];

#endif // GRIT_LEVEL2IMAGE_H

//}}BLOCK(level2image)
