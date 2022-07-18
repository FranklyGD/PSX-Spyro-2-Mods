#ifndef GAME_COMMON_H
#define GAME_COMMON_H

/*
    Enums
    when we have researched more the game,
    we can group all these in different header files
*/

enum InputFlags {
    TRIGGERLEFT =   0x1, // L2
    TRIGGERRIGHT =  0x2, // R2
    BUMPERLEFT =    0x4, // L1
    BUMPERRIGHT =   0x8, // R1
    TRIANGLE =      0x10,
    CIRCLE =        0x20,
    CROSS =         0x40,
    SQUARE =        0x80,
    SELECT =        0x100,
    STICKLEFT =     0x200, // L3
    STICKRIGHT =    0x400, // R3
    START =         0x800,
    DPADUP =        0x1000,
    DPADRIGHT =     0x2000,
    DPADDOWN =      0x4000,
    DPADLEFT =      0x8000
};

enum Levels {
    SUMMER_FOREST = 0,
    GLIMMER = 1,
    IDOL_SPRINGS = 2,
    COLOSSUS = 3,
    HURRICOS = 4,
    AQUARIA_TOWERS = 5,
    SUNNY_BEACH = 6,
    OCEAN_SPEEDWAY = 7,
    CRUSHS_DUNGEON = 8,
    AUTUMN_PLAINS = 9,
    SKELOS_BADLANDS = 10,
    CRYSTAL_GLACIER = 11,
    BREEZE_HARBOR = 12,
    ZEPHYR = 13,
    METRO_SPEEDWAY = 14,
    SCORCH = 15,
    SHADY_OASIS = 16,
    MAGMA_CONE = 17,
    FRACTURE_HILLS = 18,
    ICY_SPEEDWAY = 19,
    GULPS_OVERLOOK = 20,
    WINTER_TUNDRA = 21,
    MYSTIC_MARSH = 22,
    CLOUD_TEMPLES = 23,
    CANYON_SPEEDWAY = 24,
    ROBOTICA_FARMS = 25,
    METROPOLIS = 26,
    DRAGON_SHORES = 27,
    RIPTOS_ARENA = 28
};

enum GameState {
    PLAYING = 0, // Normal gameplay
    TALKING = 1, // Interactions with Zoe, Moneybags...
    TRANSITION_LOAD_TO_PLAYING = 3, // Happens briefly after a loading screen
    PAUSED = 4,
    LOADING_HUBS = 5, // Book load
    CUTSCENE = 6,
    LOADING_LEVELS = 7 // Spyro flying skybox animation
};

enum CameraState {
    ALIGN = 0,
    MOVING = 1,
    CHASEFLY = 3,
    CHASESWIM = 4,
    PASSIVE = 6,
    LOOK = 7,
    QUICKALIGN = 8,
    DIALOGUE = 18,
    WHIRLWINDALIGN = 23
};

/*
    Structs
    when we have researched more the game,
    we can group all these in different header files
*/

typedef struct {
    int longitude;
    int latitude;
    int radius;
    int pitch;
    int yaw;
} Orbit;

typedef struct {
    int current;
    int pressed;
    int released;
    unsigned char rightStickAnalogX;
    unsigned char rightStickAnalogY;
    unsigned char leftStickAnalogX;
    unsigned char leftStickAnalogY;
} InputState;

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
void GAME_ReadInput();
void GAME_UpdateGame_Normal();
void GAME_InitSound();
void GAME_InitGeometry();

void GAME_memcpyWord(int *dst,int *src,int size);
void GAME_memsetWord(int *buffer,int n,int size);

void GAME_ProcessInputSpyro();

void GAME_DrawText(char * text, int x, short y, int colorIndex, TextConfig * textConfig);
void GAME_DrawText2(char * text, int x, short y, int colorIndex, TextConfig * textConfig);
int GAME_GetTextWidth(char * text);
void GAME_DrawText_Center(char * text, int x, short y, int colorIndex);
void GAME_DrawText_CenterWithBG(char * text, int x, int y, int colorIndex);
void GAME_DrawText_Right(char * text, int x, short y, int colorIndex);
void GAME_DrawNumberSmall(int value, int x, short y, int colorIndex);
void GAME_DrawNumberSmall_Right(int value, int x, short y, int colorIndex);
void GAME_DrawNumberBig(int x, int y, int value);

// Semi-Transparent, Flat, RGB = (8, 8, 8)
void GAME_DrawSTBlackRect(short left, short right, short top, short bottom);
void GAME_DrawOutlinedBG(short left, short right, short top, short bottom);
void GAME_DrawRoundedBG(short left, short right, short top, short bottom);
// Opaque, Flat, RGB = (0, 0, 0)
void GAME_DrawOpaqueBlackRect(short x1, short x2, short y1, short y2);
// Used during the pause menu
void GAME_DrawGameScreenshot();

/*
    Data
    when we have researched more the game,
    we can group all these in different header files
*/

extern int GAME_levelID;
extern int GAME_levelClock;
extern int GAME_gemCount;
extern int GAME_gemCountHUD;
extern int GAME_cameraState;
extern Orbit GAME_cameraOrbitAccel;
extern InputState GAME_inputStates[5];
extern int GAME_gameState;

#endif