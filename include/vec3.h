#ifndef GAME_VEC3_H
#define GAME_VEC3_H

/*
    Structs
*/

typedef struct {
    int x;
    int z;
    int y;
} Vec3;

/*
    Functions
*/

// v = 0
void GAME_Vec3_Null(Vec3 * v);
// dst = src
void GAME_Vec3_Move(Vec3 * dst, Vec3 * src);
// dst = v1 + v2
void GAME_Vec3_Sum(Vec3 * dst, Vec3 * v1, Vec3 * v2);
// dst = v1 - v2
void GAME_Vec3_Sub(Vec3 * dst, Vec3 * v1, Vec3 * v2);
// dst = v / n
void GAME_Vec3_DivByN(Vec3 * dst, Vec3 * v, int n);

#endif