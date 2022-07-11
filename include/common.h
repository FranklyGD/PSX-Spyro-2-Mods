#ifndef GAME_COMMON_H
#define GAME_COMMON_H

/*
    Structs
    when we have researched more the game,
    we can group all these in different header files
*/

typedef struct {
    unsigned int * tail;
    unsigned int * head;
} LinkedList;

typedef struct {
    int vramYmin;
    int vramYmax;
    int length;
} TextConfig;

/*
    Functions
    when we have researched more the game,
    we can group all these in different header files
*/

void GAME_main();

void GAME_memcpyWord(int *dst,int *src,int size);
void GAME_memsetWord(int *buffer,int n,int size);

void GAME_DrawText(char * text, int x, int y, int colorIndex, TextConfig * textConfig);
// Semi-Transparent, Flat, RGB = (8, 8, 8)
void GAME_DrawSTBlackRect(short x1, short x2, short y1, short y2);
// Opaque, Flat, RGB = (0, 0, 0)
void GAME_DrawOpaqueBlackRect(short x1, short x2, short y1, short y2);
// Used during the pause menu
void GAME_DrawGameScreenshot();

/*
    Data
    when we have researched more the game,
    we can group all these in different header files
*/

#endif