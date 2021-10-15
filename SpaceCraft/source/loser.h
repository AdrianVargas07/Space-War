
//{{BLOCK(loser)

//======================================================================
//
//	loser, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 56 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 3584 + 2048 = 6144
//
//	Time-stamp: 2020-10-15, 01:28:28
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LOSER_H
#define GRIT_LOSER_H

#define loserTilesLen 3584
extern const unsigned int loserTiles[896];

#define loserMapLen 2048
extern const unsigned int loserMap[512];

#define loserPalLen 512
extern const unsigned int loserPal[128];

#endif // GRIT_LOSER_H

//}}BLOCK(loser)
