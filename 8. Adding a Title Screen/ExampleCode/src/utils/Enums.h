#pragma once

#include <stdint.h>
#include "Utils.h"


// - Overall Settings -----------------

#define ANGEL_MISS_1_LEFT 76
#define ANGEL_MISS_2_LEFT 63
#define ANGEL_MISS_3_LEFT 50
#define ANGEL_MISS_TOP 1

#define VICTIMS_MAX_NUMBER 4

#define VICTIM_ON_GROUND_1 43
#define VICTIM_ON_GROUND_2 50
#define VICTIM_HALO_DELAY 4
#define VICTIM_HALO_MAX 60
#define VICTIM_MISSED_TRAMPOLINE 1
#define VICTIM_BOUNCE_HEIGHT 37
#define VICTIM_WIDTH_HALF 8
#define VICTIM_IN_AMBULANCE 102

#define VICTIM_COUNTDOWN 180
#define VICTIM_COUNTDOWN_NONE 65535
#define VICTIM_NONE_AVAILABLE 255

#define PLAYER_MIN_X_POS 18
#define PLAYER_MID_X_POS 39
#define PLAYER_MAX_X_POS 60
#define PLAYER_WIDTH_HALF 20

#define ACCURACY_TOLERANCE 10

#define PLAYER_RANGE1_X_LEFT_START_POS PLAYER_MIN_X_POS
#define PLAYER_RANGE1_X_LEFT_END_POS PLAYER_RANGE1_X11_POS + 3
#define PLAYER_RANGE1_X_MID_START_POS PLAYER_MIN_X_POS
#define PLAYER_RANGE1_X_MID_END_POS PLAYER_RANGE1_X11_POS + 3
#define PLAYER_RANGE1_X_RIGHT_START_POS PLAYER_MID_X_POS - 4
#define PLAYER_RANGE1_X_RIGHT_END_POS PLAYER_MID_X_POS - 1

#define PLAYER_RANGE1_X_21_POS PLAYER_MID_X_POS
#define PLAYER_RANGE1_X_22_POS PLAYER_RANGE1_X21_POS + 3
#define PLAYER_RANGE1_X_23_POS PLAYER_MAX_X_POS - 4
#define PLAYER_RANGE1_X_24_POS PLAYER_MAX_X_POS - 1

#define PLAYER_Y_POS 42
#define PLAYER_STEP_INC 6 

const int8_t edgePos[] = { 5, 0, 22, 1, 5, 16, 22, 17, 5, 31, 22, 32 };
const uint8_t cloud_X_Pos[] = { 16, 16, 18, 18, 46 };
const uint8_t cloud_Y_Pos[] = { 10, 7, 0, 0, 0 };
const uint8_t angel_miss_X_Pos[] = { ANGEL_MISS_1_LEFT, ANGEL_MISS_2_LEFT, ANGEL_MISS_3_LEFT };

enum class GameState : uint8_t {
  None,
	Title_Init,
	Title,
  PlayGame_Init,
  PlayGame,
};
  
enum class LightsState : uint8_t {
  Lights_1,
  Lights_2
};

enum class Direction : uint8_t {
  Up,     // 00
  Down,   // 01
  Left,   // 02
  Right,  // 03
  None
};
