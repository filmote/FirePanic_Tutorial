#pragma once

#include <stdint.h>
#include "Utils.h"

// - Overall Settings -----------------

#define ANGEL_MISS_1_LEFT 76
#define ANGEL_MISS_2_LEFT 63
#define ANGEL_MISS_3_LEFT 50
#define ANGEL_MISS_TOP 1

#define VICTIMS_MAX_NUMBER 4

const uint8_t angel_miss_X_Pos[] = { ANGEL_MISS_1_LEFT, ANGEL_MISS_2_LEFT, ANGEL_MISS_3_LEFT };

enum class GameState : uint8_t {
  None,
	Title_Init,
	Title,
  PlayGame_Init,
  PlayGame,
};
  