#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/utils/EEPROM_Utils.h"
#include "src/images/Images.h"
#include "src/sounds/Sounds.h"

constexpr const static uint8_t PRESS_A_DELAY = 200;


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void title_Init() {
	
  titleScreenVars.sloganCaption = 0;
  titleScreenVars.sloganDisplay = false;

  playGameVars.resetGame();

  #ifdef SOUND
  sound.tones(Sounds::Score);
  #endif

  gameState = GameState::Title;

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void title() {


	// Handle input ..

	if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::GameIntro_Arrive_Init;
	}

	if (arduboy.justPressed(B_BUTTON)) {
    gameState = GameState::HighScore_Init;
	}


  // Update flame counter.

  if (arduboy.everyXFrames(15)) {

    titleScreenVars.flameCounter++;
    if (titleScreenVars.flameCounter == 3) titleScreenVars.flameCounter = 0;

  }


  // Help !

  if (arduboy.everyXFrames(80) && titleScreenVars.pressACounter > 75) {

    titleScreenVars.sloganDisplay = !titleScreenVars.sloganDisplay;
    titleScreenVars.sloganCaption++;

    if (titleScreenVars.sloganCaption == 16) titleScreenVars.sloganCaption = 0;

  }


  // Update 'Press A' counter / delay ..

  if (titleScreenVars.pressACounter < PRESS_A_DELAY) titleScreenVars.pressACounter++;

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void title_Render() {

  renderCommonScenery(false, true);
  renderLowerGrass();
  
  Sprites::drawExternalMask(33, 1, Images::FirePanic_Logo, Images::FirePanic_Logo_Mask, 0, 0);
  Sprites::drawSelfMasked(42, 13, Images::FirePanic_Logo_Anim_1, titleScreenVars.flameCounter);
  Sprites::drawSelfMasked(54, 13, Images::FirePanic_Logo_Anim_2, titleScreenVars.flameCounter); 
  Sprites::drawSelfMasked(63, 13, Images::FirePanic_Logo_Anim_3, titleScreenVars.flameCounter);
  Sprites::drawSelfMasked(71, 13, Images::FirePanic_Logo_Anim_4, titleScreenVars.flameCounter);
  Sprites::drawSelfMasked(79, 13, Images::FirePanic_Logo_Anim_5, titleScreenVars.flameCounter); 

  if (titleScreenVars.pressACounter == PRESS_A_DELAY) {

    Sprites::drawOverwrite(43, 52, Images::PressA, 0);

  }

  uint8_t slogan = titleScreenVars.sloganCaption / 4;

  switch (slogan) {

    case 0:
      Sprites::drawExternalMask(0, 14, Images::Victim_OnEdge_01, Images::Victim_OnEdge_01_Mask, 0, 0);
      break;

    case 1:
      Sprites::drawExternalMask(112, 14, Images::Victim_OnEdge_01_RH, Images::Victim_OnEdge_01_RH_Mask, 0, 0);
      break;

    case 2:
      Sprites::drawExternalMask(0, 31, Images::Victim_OnEdge_01, Images::Victim_OnEdge_01_Mask, 0, 0);
      break;

    case 3:
      Sprites::drawExternalMask(112, 31, Images::Victim_OnEdge_01_RH, Images::Victim_OnEdge_01_RH_Mask, 0, 0);
      break;
      
  }

  if (titleScreenVars.sloganDisplay) {

    switch (slogan) {
      
      case 0:
        Sprites::drawExternalMask(18, 3, Images::Help, Images::Help_Mask, 0, 0);
        break;
      
      case 1:
        Sprites::drawExternalMask(91, 3, Images::Help, Images::Help_Mask, 1, 1);
        break;
      
      case 2:
        Sprites::drawExternalMask(18, 16, Images::Filmote, Images::Filmote_Mask, 0, 0);
        break;
      
      case 3:
        Sprites::drawExternalMask(71, 16, Images::Vampirics, Images::Vampirics_Mask, 0, 0);
        break;

    }

  }

}
