#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/utils/Physics.h"
#include "src/images/Images.h"
#include "src/sounds/Sounds.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void playGame_Init() {

  playGameVars.gameOver = false;
  playGameVars.score = 0;
  playGameVars.counter = 0;
  playGameVars.victimCountdown = 200;
  playGameVars.victimDelay = 0;
  playGameVars.victimLevel = 0;
  playGameVars.misses = 0;
  
  setPaused(false);

  for (auto &victim : playGameVars.victims) {

    victim.setEnabled(false);

  }

  sound.setOutputEnabled(arduboy.audio.enabled);
  gameState = GameState::PlayGame;

}
  

// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void playGame() { 

  if (!getPaused()) {


    // Update victim positions ..
    {
      //uint8_t playerXCentre = ...;

      if (arduboy.everyXFrames(5)) {

        for (auto &victim : playGameVars.victims) {

          if (victim.getEnabled()) {

            uint8_t victimX = victim.getX();

            if (victimX == VICTIM_IN_AMBULANCE) {

              playGameVars.score = playGameVars.score + 5;

              #ifdef SOUND
              sound.tones(Sounds::VictimSaved);
              #endif

            }
            else {

              uint8_t posIndex = victim.getPosIndex();
              uint8_t victimXCentre = victimX + VICTIM_WIDTH_HALF;
              // uint8_t delta = absT(victimXCentre - playerXCentre);

              #define PLAYER_POS_1 true
              #define PLAYER_POS_2 true
              #define PLAYER_POS_3 true

              uint8_t delta = 100;
              if (posIndex == (BOTTOM_ARC_1 - 1) && PLAYER_POS_1) delta = 1;
              if (posIndex == (BOTTOM_ARC_2 - 1) && PLAYER_POS_2) delta = 1;
              if (posIndex == (BOTTOM_ARC_3 - 1) && PLAYER_POS_3) delta = 1;

              if (posIndex == (BOTTOM_ARC_1 - 1) || posIndex == (BOTTOM_ARC_2 - 1) || posIndex == (BOTTOM_ARC_3 - 1)) {

                if (delta <= ACCURACY_TOLERANCE) {
                  victim.setPrevBounce(true);
                }
                
              }

              else if (posIndex == BOTTOM_ARC_1 || posIndex == BOTTOM_ARC_2 || posIndex == BOTTOM_ARC_3) {

                if (!victim.getPrevBounce() && delta > ACCURACY_TOLERANCE) {

                  victim.setEnabled(false);
                  playGameVars.misses++;

                  #ifdef SOUND
                  sound.tones(Sounds::VictimDead);
                  #endif
                  
                }
                else {

                  switch(posIndex) {

                    case BOTTOM_ARC_1: 
                      #ifdef SOUND
                      sound.tones(Sounds::VictimBounced_1);
                      #endif
                      break;

                    case BOTTOM_ARC_2: 
                      #ifdef SOUND
                      sound.tones(Sounds::VictimBounced_2);
                      #endif
                      break;

                    case BOTTOM_ARC_3: 
                      #ifdef SOUND
                      sound.tones(Sounds::VictimBounced_3);
                      #endif
                      break;

                  }
                  
                }  

              }

              else {

                victim.setPrevBounce(false);

              }

            }

            victim.move();
            
          }

        }

      }


      // If its the end of the game, remove all other victims ..

      if (playGameVars.misses >= 3) {

        for (auto &victim : playGameVars.victims) {

          if (victim.getEnabled()) {

            victim.setEnabled(false);

          }

        }

      }

    }


    // Rotate victims ..

    if (arduboy.everyXFrames(15)) {

      for (auto &victim : playGameVars.victims) {

        if (victim.getEnabled()) {
          victim.rotate();
        }

      }

    }


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
        playGameVars.victims[nextAvailableVictim].init(playGameVars.victimLevel);
        //playGameVars.victimCountdown = VICTIM_COUNTDOWN_NONE;

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

        }
        else {

          playGameVars.victimCountdown = VICTIM_COUNTDOWN_NONE;

        }

      }

    }


    if (playGameVars.misses >= 3 && allVictimsDisabled()) {

      playGameVars.gameOver = true;

    }

  }


  // Handle other buttons ..

  handleCommonButtons();

}


// ----------------------------------------------------------------------------
//  Get index of next available victim.
//
uint8_t getNextAvailable(uint8_t gap) {

  for (auto &victim : playGameVars.victims) {

    if (victim.getEnabled()) {

      uint8_t posIndex = victim.getPosIndex();
      
      if (posIndex == TOP_ARC_1_2 || posIndex == TOP_ARC_2_3) { //22, 44,  b1g = -22, b2g = -1
        return VICTIM_NONE_AVAILABLE;
      }

      {
        int8_t bottom1Gap = absT(TOP_ARC_1_2 - posIndex);
        int8_t bottom2Gap = absT(TOP_ARC_2_3 - posIndex);

        if (bottom1Gap < gap || bottom2Gap < gap)   {
          return VICTIM_NONE_AVAILABLE;
        }

      }

    }

  }

  for (uint8_t i = 0; i < VICTIMS_MAX_NUMBER; i++) {

    if (!playGameVars.victims[i].getEnabled()) {

      return i;

    }

  }

  return VICTIM_NONE_AVAILABLE;

}


// ----------------------------------------------------------------------------
//  Are all the victims disabled?
//
bool allVictimsDisabled() {

  for (auto &victim : playGameVars.victims) {

    if (victim.getEnabled()) {
      return false;
    }

  }

  return true;

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


  // Render victims ..

  for (auto &victim : playGameVars.victims) {

    if (victim.getEnabled()) {

      uint8_t imageIndex = victim.getRotation();
      Sprites::drawExternalMask(victim.getX(), victim.getY(), Images::Victims, Images::Victims_Mask, imageIndex, imageIndex);

    }

  }


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
