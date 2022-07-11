#ifndef GAME_LIBGRAPHICS_H
#define GAME_LIBGRAPHICS_H

/*
    Structs
*/

typedef struct {
    short m[3][3];
    long t[3];
} MATRIX;

typedef struct {
    int vx, vy, vz;
    int pad;
} VECTOR;

typedef struct {
    short x, y;
    short w, h;
} RECT;

typedef struct {
    unsigned int * tag;
    unsigned int code[15];
} DR_ENV;

typedef struct {
    RECT disp;
    RECT screen;
    unsigned char isinter;
    unsigned char isrgb24;
    unsigned char pad0, pad1;
} DISPENV;

typedef struct {
    RECT clip;
    short ofs[2];
    RECT tw;
    unsigned short tpage;
    unsigned char dtd;
    unsigned char dfe;
    unsigned char isbg;
    unsigned char r0, g0, b0;
    DR_ENV dr_env;
} DRAWENV;

/*
    Functions
*/

int LIBG_VSync(int mode);
void LIBG_InitGeom();
DRAWENV * LIBG_SetDefDrawEnv(DRAWENV * env, int x, int y, int w, int h);
DISPENV * LIBG_SetDefDispEnv(DISPENV * env, int x, int y, int w, int h);
void LIBG_SetDrawMode(DR_MODE * p, int dfe, int dtd, int tpage, RECT * tw);
MATRIX * LIBG_MulMatrix0(MATRIX * m0, MATRIX * m1, MATRIX * dst);
MATRIX * LIBG_ScaleMatrix(MATRIX * m, VECTOR * v);

#endif