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



  // Handle other buttons ..

  handleCommonButtons();

}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void playGame_Render() {

  renderCommonScenery();
  renderMisses();
  renderScore(false, 0);

  renderLowerGrass();

  renderAmbulance(96, 31);
  renderGameOverOrPause();

}
