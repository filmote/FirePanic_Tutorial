#include <Arduboy2.h>


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

  arduboy.drawFastHLine(0, 0, 128, WHITE);
  arduboy.drawFastHLine(0, 63, 128, WHITE);

  arduboy.setCursor(32, 30);
  arduboy.print(F("Play Game"));

}
