#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/images/Images.h"


void title_Init() {

  gameState = GameState::Title_Init;

}

void title() {

  arduboy.clear();
  arduboy.setTextColor(WHITE);

  arduboy.setCursor(32, 20);
  arduboy.print(F("Fire Panic!"));

  arduboy.setCursor(43, 40);
  arduboy.print(F("Press A"));


	// Handle input ..

	if (arduboy.justPressed(A_BUTTON)) {
    gameState = GameState::PlayGame_Init;
	}

}
