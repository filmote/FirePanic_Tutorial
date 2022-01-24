#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/utils/EEPROM_Utils.h"
#include "src/fonts/Font4x6.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void highScore_Init() {

  highScoreVars.charIdx = 0;
  highScoreVars.clearScores = 0;
  highScoreVars.pressACounter = HS_PRESS_A_DELAY;
  highScoreVars.winnerIdx = (playGameVars.score > 0 ? EEPROM_Utils::saveScore(playGameVars.score) : NO_WINNER);

  arduboy.clearButtonState();

  // Retrieve existing names and scores ..
  EEPROM_Utils::readSaveEntries(highScoreVars.players);

  gameState = GameState::HighScore;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void highScore() {


  // Is the new score a high score ?

  if (highScoreVars.winnerIdx < NO_WINNER) {

    if (arduboy.everyXFrames(12)) {

      if (arduboy.pressed(UP_BUTTON)) {

        char *player = highScoreVars.players[highScoreVars.winnerIdx].name;
        player[highScoreVars.charIdx]++;
        if (player[highScoreVars.charIdx] > 90)  player[highScoreVars.charIdx] = 65;
        if (player[highScoreVars.charIdx] == 64) player[highScoreVars.charIdx] = 65;

      }

      if (arduboy.pressed(DOWN_BUTTON)) {

        char *player = highScoreVars.players[highScoreVars.winnerIdx].name;
        player[highScoreVars.charIdx]--;
        if (player[highScoreVars.charIdx] < 65)  player[highScoreVars.charIdx] = 90;

      }

      if (arduboy.pressed(LEFT_BUTTON) && highScoreVars.charIdx > 0) {
        highScoreVars.charIdx--;
      }

      if (arduboy.pressed(RIGHT_BUTTON) && highScoreVars.charIdx < 2) {
        highScoreVars.charIdx++;
      }

      if (arduboy.pressed(A_BUTTON)) {

        char *player = highScoreVars.players[highScoreVars.winnerIdx].name;

        if (player[0] != 63 && player[1] != 63 && player[2] != 63) {
          
          for (uint8_t i = 0; i < 3; i++) {
            EEPROM_Utils::saveChar(highScoreVars.winnerIdx, i, player[i]);
          }
          
          highScoreVars.winnerIdx = NO_WINNER;
          highScoreVars.pressACounter = HS_PRESS_A_DELAY;

        }

      }

    }

  }
  else {


    // Handle other input ..

    if ((arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) && highScoreVars.pressACounter == 0) {
      gameState = GameState::Title_Init;
    }

  }


  // Decrement the 'Press A' counter if it has been set ..

  if (highScoreVars.pressACounter > 0) highScoreVars.pressACounter--;

}


void highScore_RenderSingleEntry(uint8_t y, const SaveEntry & saveEntry) {

  for (uint8_t i = 0; i < 3; i++) {
    Sprites::drawOverwrite(HS_NAME_LEFT + (i * 6), y, font_images, saveEntry.name[i] == 63 ? 0 : saveEntry.name[i] - 64);
  }

  for (uint8_t j = 6, x2 = HS_SCORE_LEFT - 4; j > 0; --j, x2 += 5) {
    
    uint8_t digits[6] = {};
    extractDigits(digits, saveEntry.score);
    Sprites::drawOverwrite(x2, y, font_images, digits[j - 1] + 27);

  }

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void highScore_Render() {

	const bool flash = arduboy.getFrameCountHalf(FLASH_FRAME_COUNT_2);

  renderCommonScenery(false, true);
  Sprites::drawExternalMask(30, 3, Images::HighscoreText, Images::HighscoreText_Mask, 0, 0);
  Sprites::drawExternalMask(28, 16, Images::HighscorePanel, Images::HighscorePanel_Mask, 0, 0);
  


  // Render scores ..
  for (uint8_t index = 0; index < eepromSaveEntriesCount; ++index) {

    highScore_RenderSingleEntry(HS_CHAR_TOP + (HS_CHAR_V_SPACING * index), highScoreVars.players[index]);

  }


  // Render edit field if the slot is being editted ..

  if (highScoreVars.winnerIdx < NO_WINNER && flash) {

    char *player = highScoreVars.players[highScoreVars.winnerIdx].name;

    arduboy.fillRect(HS_NAME_LEFT + (highScoreVars.charIdx * 6) - 1, HS_CHAR_TOP + (highScoreVars.winnerIdx * HS_CHAR_V_SPACING) - 1, 6, 8, WHITE);
    Sprites::drawErase(HS_NAME_LEFT + (highScoreVars.charIdx * 6), HS_CHAR_TOP + (HS_CHAR_V_SPACING * highScoreVars.winnerIdx), font_images, player[highScoreVars.charIdx] == 63 ? 0 : player[highScoreVars.charIdx] - 64);

  }


  // Render foreground grass ..

  renderLowerGrass();


  // Display Press A message?

  if (highScoreVars.winnerIdx == NO_WINNER && highScoreVars.pressACounter == 0) {

    Sprites::drawOverwrite(43, 52, Images::PressA, 0);

  }

}
