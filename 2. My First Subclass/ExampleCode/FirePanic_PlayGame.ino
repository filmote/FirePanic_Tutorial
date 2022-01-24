#include "src/utils/Arduboy2Ext.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void playGame_Init() {

  gameState = GameState::PlayGame;

}
  

// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void playGame() { 

  arduboy.drawHorizontalDottedLine(0, 128, 0, WHITE);
  arduboy.drawHorizontalDottedLine(0, 128, 63, WHITE);

  arduboy.setCursor(32, 30);
  arduboy.print(F("Play Game"));

}
