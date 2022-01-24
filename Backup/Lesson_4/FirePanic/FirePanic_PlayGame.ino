#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void playGame_Init() {

  playGameVars.gameOver = false;
  playGameVars.score = 0;
  playGameVars.victimCountdown = 200;
  playGameVars.victimDelay = 0;
  playGameVars.victimLevel = 0;
  playGameVars.misses = 0;
  
  setPaused(false);

  for (auto &victim : playGameVars.victims) {

    victim.setEnabled(false);

  }

  gameState = GameState::PlayGame;

}
  

// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void playGame() { 

  if (!getPaused()) {


    // Is a victim ready to jump?
    
    if (playGameVars.victimCountdown > 0 && playGameVars.victimCountdown < VICTIM_COUNTDOWN_NONE) {

      playGameVars.victimCountdown--;

    }

    if (playGameVars.victimCountdown == 0) {

      uint16_t gap = 3;
      if (playGameVars.score < 1000) {
        gap = ((1000 - playGameVars.score) / 250) + 3;
      }

      uint8_t nextAvailableVictim = getNextAvailable(gap);

      if (nextAvailableVictim != VICTIM_NONE_AVAILABLE) {

        // SJH playGameVars.victims[nextAvailableVictim].init(playGameVars.victimLevel);

        if (playGameVars.misses < 3) {

          uint16_t maxDelay = 150;
          uint16_t minDelay = 75;
          
          if (playGameVars.score < 1500)  { maxDelay = (1500 - (playGameVars.score / 2)) / 5; }
          if (playGameVars.score < 750)   { minDelay = (750 - (playGameVars.score / 2)) / 5; }

          playGameVars.victimCountdown = random(minDelay, maxDelay);

          switch (playGameVars.score) {

            case 0 ... 20:
              playGameVars.victimLevel = 0;
              break;

            case 21 ... 40:
              playGameVars.victimLevel = random(2);
              break;

            default:
              playGameVars.victimLevel = random(3);
              break;

          }

          /* SJH */ playGameVars.score = playGameVars.score + 5;

        }
        else {

          playGameVars.victimCountdown = VICTIM_COUNTDOWN_NONE;

        }

      }

    }

  }


  // Handle other buttons ..

  handleCommonButtons();

}


// ----------------------------------------------------------------------------
//  Get index of next available victim.
//
uint8_t getNextAvailable(uint8_t gap) {

  for (uint8_t i = 0; i < VICTIMS_MAX_NUMBER; i++) {

    if (!playGameVars.victims[i].getEnabled()) {

      return i;

    }

  }

  return VICTIM_NONE_AVAILABLE;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void playGame_Render() {

  renderCommonScenery();


  // Render misses ..

  renderMisses();


  // Render score ..

  renderScore(false, 0);


  // Render foreground grass ..

  renderLowerGrass();


  // Render victim about to jump ..

  if (playGameVars.victimCountdown < 75) {

    Sprites::drawExternalMask(edgePos[playGameVars.victimLevel * 4], edgePos[(playGameVars.victimLevel * 4) + 1], Images::Victim_OnEdge_01, Images::Victim_OnEdge_01_Mask, 0, 0);

    if (playGameVars.victimCountdown % 30 < 15) {

      Sprites::drawExternalMask(edgePos[(playGameVars.victimLevel * 4) + 2], edgePos[(playGameVars.victimLevel * 4) + 3], Images::Victim_OnEdge_02, Images::Victim_OnEdge_02_Mask, 0, 0);

    }

  }

  renderAmbulance(96, 31);
  renderGameOverOrPause();

}
