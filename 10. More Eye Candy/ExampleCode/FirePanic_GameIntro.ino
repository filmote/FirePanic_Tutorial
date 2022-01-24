#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"

// ----------------------------------------------------------------------------
//  Initialise state ..
//
void gameIntro_Init() {

  switch (gameState) {

    case GameState::GameIntro_Arrive_Init:

      gameIntroVars.xAmbulance = 156;
      gameIntroVars.xPlayer = PLAYER_MIN_X_POS + 6 + (30 * 3);
      playGameVars.targetScore = playGameVars.score + TARGET_SCORE_BASE + (playGameVars.level * TARGET_SCORE_INC_PER_LEVEL);
      gameState = GameState::GameIntro_Arrive;
      break;

    case GameState::GameIntro_Leave_Init:

      gameIntroVars.xAmbulance = 96;
      gameIntroVars.xPlayer = playGameVars.xPosition;
      gameState = GameState::GameIntro_Leave;
      break;

  }

  gameIntroVars.counter = 0;
  gameIntroVars.ambulanceDoor = false;
  gameIntroVars.playerImageIndex = false;
  gameIntroVars.speedInc = 0;

  playGameVars.takeARest = false;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void gameIntro() { 

  if (arduboy.everyXFrames(2)) {

    switch (gameState) {

      case GameState::GameIntro_Arrive:

        switch (gameIntroVars.counter) {

          case 0 ... 59:
            gameIntroVars.xAmbulance--;
            break;

          case 60 ... 75:
            break;

          case 76 ... 90:
            gameIntroVars.ambulanceDoor = true;
            break;

          case 91 ... 161:

            gameIntroVars.ambulanceDoor = true;

            if (arduboy.everyXFrames(4)) {

              switch (gameIntroVars.xPlayer) {

                case PLAYER_MIN_X_POS : break;

                case PLAYER_MIN_X_POS + 1 ... PLAYER_MIN_X_POS + 3:
                  gameIntroVars.xPlayer = gameIntroVars.xPlayer - 1;
                  break;

                case PLAYER_MIN_X_POS + 4 ... PLAYER_MIN_X_POS + 8:
                  gameIntroVars.xPlayer = gameIntroVars.xPlayer - 2;
                  break;

                default:
                  gameIntroVars.xPlayer = gameIntroVars.xPlayer - 3;
                  break;

              }

            }

            break;

          case 162 ... 190:
            gameIntroVars.ambulanceDoor = false;
            break;

          case 191:
            gameState = GameState::PlayGame_Init;
            break;

        }

        gameIntroVars.counter++;
        break;

      case GameState::GameIntro_Leave:

        switch (gameIntroVars.counter) {

          case 0 ... 20:
            break;

          case 21 ... 40:
            gameIntroVars.ambulanceDoor = true;
            break;

          case 41 ... 115:

            gameIntroVars.ambulanceDoor = true;

            if (arduboy.everyXFrames(4)) {

              gameIntroVars.xPlayer = gameIntroVars.xPlayer + ((gameIntroVars.speedInc + 1) / 2);
              if (gameIntroVars.speedInc < 5) gameIntroVars.speedInc++;

            }

            break;

          case 116 ... 140:
            gameIntroVars.ambulanceDoor = false;
            break;

          case 141 ... 179:
            gameIntroVars.xAmbulance++;
            break;

          case 180:
            gameState = GameState::GameIntro_Arrive_Init;
            break;
        }

        gameIntroVars.counter++;
        break;

    }

  }


  // Skip intro ..
  
  if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::PlayGame_Init;
  }

  if (arduboy.everyXFrames(12) && gameIntroVars.xPlayer != PLAYER_MIN_X_POS) {
    gameIntroVars.playerImageIndex = !gameIntroVars.playerImageIndex;
  }
  
}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void gameIntro_Render() {

  renderCommonScenery(true, false);
  

  if (gameIntroVars.xPlayer < 100) {

    Sprites::drawExternalMask(gameIntroVars.xPlayer, PLAYER_Y_POS, Images::FireMen, Images::FireMen_Mask, gameIntroVars.playerImageIndex, gameIntroVars.playerImageIndex);

  }

  Sprites::drawExternalMask(104, 28, Images::Grass, Images::Grass_Mask, 0, 0);
  Sprites::drawOverwrite(104, 38, Images::Ground_RHS, 0);
  renderLowerGrass();


  // Draw Ambulance with lights ..

  renderAmbulance(gameIntroVars.xAmbulance, 31, gameIntroVars.ambulanceDoor);

}
