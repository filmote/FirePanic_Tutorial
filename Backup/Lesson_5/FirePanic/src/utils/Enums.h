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

#define ACCURACY_TOLERANCE 10

constexpr size_t eepromStart = 120;
constexpr size_t eepromStart_C1 = eepromStart + 1;
constexpr size_t eepromStart_C2 = eepromStart + 2;
constexpr size_t eepromSaveEntriesCount = 3;
constexpr size_t eepromSaveEntriesStart = eepromStart + 3;

#define FLASH_FRAME_COUNT_2 56

const int8_t edgePos[] = { 5, 0, 22, 1, 5, 16, 22, 17, 5, 31, 22, 32 };
const uint8_t angel_miss_X_Pos[] = { ANGEL_MISS_1_LEFT, ANGEL_MISS_2_LEFT, ANGEL_MISS_3_LEFT };

enum class GameState : uint8_t {
  None,
	Title_Init,
	Title,
  PlayGame_Init,
  PlayGame,
};
  