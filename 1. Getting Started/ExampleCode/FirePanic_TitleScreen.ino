#include <Arduboy2.h>

void title_Init() {

  gameState = GameState::Title_Init;

}

void title() {

  arduboy.drawFastHLine(0, 0, 128, WHITE);
  arduboy.drawFastHLine(0, 63, 128, WHITE);

  arduboy.setCursor(32, 20);
  arduboy.print(F("Fire Panic!"));

  arduboy.setCursor(43, 40);
  arduboy.print(F("Press A"));


	// Handle input ..

	if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::PlayGame_Init;
	}

}
