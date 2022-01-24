#include "src/utils/Arduboy2Ext.h"

void title_Init() {

  gameState = GameState::Title_Init;

}

void title() {

  arduboy.drawHorizontalDottedLine(0, 128, 0, WHITE);
  arduboy.drawHorizontalDottedLine(0, 128, 63, WHITE);

  arduboy.setCursor(32, 20);
  arduboy.print(F("Fire Panic!"));

  arduboy.setCursor(43, 40);
  arduboy.print(F("Press A"));


	// Handle input ..

	if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::PlayGame_Init;
	}

}
