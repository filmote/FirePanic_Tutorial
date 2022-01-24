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
  playGameVars.counter = 0;
  playGameVars.puffIndex = 0;
  playGameVars.victimCountdown = 200;
  playGameVars.victimDelay = 0;
  playGameVars.victimLevel = 0;

  playGameVars.angel.setEnabled(false);
  playGameVars.player.setX(PLAYER_MIN_X_POS);

  setPaused(false);

  for (auto &victim : playGameVars.victims) {

    victim.setEnabled(false);
    victim.setAlive(0);

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
      uint8_t playerXCentre = playGameVars.player.getX() + PLAYER_WIDTH_HALF;

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
              uint8_t delta = absT(victimXCentre - playerXCentre);

              if (posIndex == (BOTTOM_ARC_1 - 1) || posIndex == (BOTTOM_ARC_2 - 1) || posIndex == (BOTTOM_ARC_3 - 1)) {

                if (delta <= ACCURACY_TOLERANCE) {
                  victim.setPrevBounce(true);
                }
                
              }

              else if (posIndex == BOTTOM_ARC_1 || posIndex == BOTTOM_ARC_2 || posIndex == BOTTOM_ARC_3) {

                if (!victim.getPrevBounce() && delta > ACCURACY_TOLERANCE) {

                  victim.setAlive(VICTIM_MISSED_TRAMPOLINE);
                  playGameVars.misses++;

                  #ifdef SOUND
                  sound.tones(Sounds::VictimDead);
                  #endif

                  if (playGameVars.misses < 3) {

                    switch (victim.getX()) {

                      case PLAYER_MIN_X_POS ... PLAYER_MID_X_POS - 1:
                        playGameVars.angel.init(0, playGameVars.misses);
                        break;

                      case PLAYER_MID_X_POS ... PLAYER_MAX_X_POS - 1:
                        playGameVars.angel.init(1, playGameVars.misses);
                        break;

                      case PLAYER_MAX_X_POS ... WIDTH:
                        playGameVars.angel.init(2, playGameVars.misses);
                        break;

                    }

                  }
                  
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

          if (victim.getEnabled() && victim.getAlive() == 0 && victim.getPuffIndex() == 0) {

            victim.incPuffIndex();

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

    if (!playGameVars.takeARest) {
      
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

    }



    // Update player position ..

    if (arduboy.pressed(LEFT_BUTTON) && playGameVars.player.canMoveLeft())      { playGameVars.player.setDirection(Direction::Left); }
    if (arduboy.pressed(RIGHT_BUTTON) && playGameVars.player.canMoveRight())    { playGameVars.player.setDirection(Direction::Right); }
    
    if (arduboy.everyXFrames(2)) {

      playGameVars.player.move();

    }


    // Update angel ..
      
    if (arduboy.everyXFrames(6)) {
    
      if (playGameVars.angel.getEnabled()) {

        if (playGameVars.angel.move()) {

          playGameVars.puffIndex++;

          if (playGameVars.puffIndex == 8) {

            playGameVars.angel.setEnabled(false);
            playGameVars.puffIndex = 0;

          }

        }
        else {

          playGameVars.puffIndex = 0;

        }
        
      }


      // Update the puff index on any victims mid flight ..

      for (auto &victim : playGameVars.victims) {

        if (victim.getEnabled() && victim.getPuffIndex() > 0) {

          victim.incPuffIndex();

        }

      }

    }

    if (playGameVars.misses >= 3 && allVictimsDisabled()) {

      playGameVars.gameOver = true;

    }

  }


  // Transition to race ..

  if (playGameVars.score > playGameVars.targetScore) {

    playGameVars.takeARest = true;

  }

  if (playGameVars.takeARest) {

    if (allVictimsDisabled()) {
      playGameVars.xPosition = playGameVars.player.getX();
      playGameVars.level++;

      if (playGameVars.misses < 3) {
        gameState = GameState::GameIntro_Leave_Init;
      }
      else {
        playGameVars.gameOver = true;
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

  renderCommonScenery(true, false);


  // Render misses ..

  renderMisses(!playGameVars.angel.getEnabled() || playGameVars.puffIndex >= 3);


  // Render score ..

  renderScore(false, 0);


  // Render firemen ..

  uint8_t i = playGameVars.player.getImageIndex();
  Sprites::drawExternalMask(playGameVars.player.getX(), playGameVars.player.getY(), Images::FireMen, Images::FireMen_Mask, i, i);


  // Render foreground grass ..

  renderLowerGrass();


  // Render victims ..

  for (auto &victim : playGameVars.victims) {

    if (victim.getEnabled()) {

      if (victim.getPuffIndex() < 3) {

        uint8_t imageIndex = victim.getRotation();
        Sprites::drawExternalMask(victim.getX(), victim.getY(), Images::Victims, Images::Victims_Mask, imageIndex, imageIndex);

        uint8_t isAlive = victim.getAlive();

        if (isAlive >= 2) {
          
          uint8_t haloIndex = victim.getHaloIndex();

          Sprites::drawExternalMask(victim.getX(), victim.getY() - 5, Images::Victim_Halos, Images::Victim_Halos_Mask, haloIndex, haloIndex);

        }

      }

      if (victim.getPuffIndex() > 0) {

        uint8_t puffIndex = victim.getPuffIndex() - 1;
        renderPuff(victim.getX(), victim.getY(), puffIndex);

      }

    }

  }


  // Render victim about to jump ..

  if (playGameVars.victimCountdown < 75) {

    Sprites::drawExternalMask(edgePos[playGameVars.victimLevel * 4], edgePos[(playGameVars.victimLevel * 4) + 1], Images::Victim_OnEdge_01, Images::Victim_OnEdge_01_Mask, 0, 0);

    if (playGameVars.victimCountdown % 30 < 15) {

      Sprites::drawExternalMask(edgePos[(playGameVars.victimLevel * 4) + 2], edgePos[(playGameVars.victimLevel * 4) + 3], Images::Victim_OnEdge_02, Images::Victim_OnEdge_02_Mask, 0, 0);

    }

  }


  // Render angel if required ..

  if (playGameVars.angel.getEnabled() && playGameVars.angel.renderImage() && playGameVars.puffIndex <= 3) {

    uint8_t imageIndex = playGameVars.angel.getImageIndex();
    Sprites::drawExternalMask(playGameVars.angel.getX(), playGameVars.angel.getY(), Images::Angels, Images::Angels_Mask, imageIndex, imageIndex);

  }

  renderAmbulance(96, 31, false);

  if (playGameVars.puffIndex > 0) {

    if (playGameVars.misses < 3) {

      uint8_t puffIndex = playGameVars.puffIndex - 1;
      renderPuff((playGameVars.misses == 1 ? ANGEL_MISS_1_LEFT : ANGEL_MISS_2_LEFT) - 1, ANGEL_MISS_TOP, puffIndex);

    }

  }

  renderGameOverOrPause();

}
