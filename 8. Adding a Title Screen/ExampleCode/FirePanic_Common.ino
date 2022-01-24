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


void renderMisses(bool renderLatest) {

  uint8_t missCount = playGameVars.misses - (renderLatest ? 0 : 1);

  for (uint8_t i = 0; i < missCount; i++) {
    Sprites::drawExternalMask(angel_miss_X_Pos[i], ANGEL_MISS_TOP, Images::Misses, Images::Misses_Mask, 0, 0); 
  }

}

void renderCommonScenery(bool incSmoke, bool incRHSBuilding) {

  if (incSmoke) {  

    uint8_t xOffset = cloud_X_Pos[playGameVars.smokeIndex];
    uint8_t yOffset = cloud_Y_Pos[playGameVars.smokeIndex];

    Sprites::drawOverwrite(xOffset, yOffset, pgm_read_word_near(&Images::Smoke[playGameVars.smokeIndex]), 0);

    if (arduboy.everyXFrames(16)) {
      playGameVars.smokeIndex++;
      if (playGameVars.smokeIndex >= 5) playGameVars.smokeIndex = 0;
    }

  }

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    Sprites::drawExternalMask(i, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  }

  Sprites::drawExternalMask(0, 51, Images::Ground, Images::Ground_Mask, 0, 0);
  Sprites::drawExternalMask(0, 0, Images::Building, Images::Building_Mask, 0, 0);

  if (incRHSBuilding) {
    Sprites::drawExternalMask(112, 0, Images::Building_RHS, Images::Building_RHS_Mask, 0, 0);
  }

}


void renderLowerGrass() {

  for (uint8_t i = 0; i <= 120; i = i + 8) {
    Sprites::drawExternalMask(i, 59, Images::Grass, Images::Grass_Mask, 0, 0);
  }

}


void renderAmbulance(int8_t x, int8_t y, bool doorOpen) {

  // Alternate lights ..

  if (arduboy.everyXFrames(8)) {
    playGameVars.lights = (playGameVars.lights == LightsState::Lights_1 ? LightsState::Lights_2 : LightsState::Lights_1);
  }


  // Draw Ambulance with lights ..

  Sprites::drawExternalMask(x, y, Images::Ambulance, Images::Ambulance_Mask, 0, 0);
  Sprites::drawExternalMask(x + 18, y, Images::Ambulance_Lights, Images::Ambulance_Lights_Mask, static_cast<uint8_t>(playGameVars.lights), 0);

  if (doorOpen) {
    Sprites::drawExternalMask(x - 4, y + 5, Images::Ambulance_Door, Images::Ambulance_Door_Mask, 0, 0);
  }

}

void renderPuff(int8_t x, int8_t y, uint8_t puffIndex) {

  Sprites::drawExternalMask(x, y, Images::Puff, Images::Puff_Mask, puffIndex, puffIndex);

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