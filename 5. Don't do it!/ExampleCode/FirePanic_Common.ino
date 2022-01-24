#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"

void renderScore(bool renderHealth, int16_t health) {

  Sprites::drawExternalMask(89, 0, Images::Scoreboard, Images::Scoreboard_Mask, 0, 0);

  if (!renderHealth) {

    uint8_t digits[6] = {};
    extractDigits(digits, playGameVars.score);

    for (uint8_t j = 6; j > 0; --j) {

      Sprites::drawSelfMasked(124 - (j*5), 3, Images::Scoreboard_Numbers, digits[j - 1]);

    }

  }
  else {

    for (uint8_t i = 0; i < health; i = i + 2) {
      
      arduboy.drawFastVLine(94 + i, 3, 8);

    }

  }

}


void renderMisses() {

  for (uint8_t i = 0; i < playGameVars.misses; i++) {
    Sprites::drawExternalMask(angel_miss_X_Pos[i], ANGEL_MISS_TOP, Images::Misses, Images::Misses_Mask, 0, 0); 
  }

}

void renderCommonScenery() {

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    Sprites::drawExternalMask(i, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  }

  Sprites::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);

}


void renderLowerGrass() {

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    Sprites::drawExternalMask(i, 59, Images::Grass, Images::Grass_Mask, 0, 0);
  }

}


void renderAmbulance(int8_t x, int8_t y) {

  Sprites::drawExternalMask(x, y, Images::Ambulance, Images::Ambulance_Mask, 0, 0);
  Sprites::drawExternalMask(x - 4, y + 5, Images::Ambulance_Door, Images::Ambulance_Door_Mask, 0, 0);

}


bool getPaused() {

  return playGameVars.paused;

}

void setPaused(bool value) {
  
  playGameVars.paused = value;

}

void handleCommonButtons() {

  if (playGameVars.gameOver) {

    if (arduboy.justPressed(A_BUTTON)) {
      gameState = GameState::Title_Init;
    }

  }
  else {

    if (arduboy.justPressed(B_BUTTON)) {
      playGameVars.paused = !playGameVars.paused; 
    }

  }

}

void renderGameOverOrPause() {

  // Game Over?

  if (playGameVars.gameOver) {

    Sprites::drawExternalMask(32, 20, Images::GameOver, Images::GameOver_Mask, 0, 0); 

  }

  // Pause?

  if (playGameVars.paused) {

    Sprites::drawExternalMask(39, 20, Images::Pause, Images::Pause_Mask, 0, 0); 

  }

}