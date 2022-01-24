#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/images/Images.h"
#include "src/sounds/Sounds.h"
#include "src/arduboyTones/ArduboyTonesExt.h"

Arduboy2Ext arduboy;
ArduboyTonesExt sound;

GameState gameState = GameState::Title_Init;

PlayGameVars playGameVars;
TitleScreenVars titleScreenVars;

void setup() {

	arduboy.boot();
	arduboy.flashlight();
	arduboy.systemButtons();
	arduboy.audio.begin();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(75);

	gameState = GameState::Title_Init; 

}

void loop() {

	if (!arduboy.nextFrame()) return;
	arduboy.pollButtons();

	switch (gameState) {

    case GameState::Title_Init:
      title_Init();
      title();
      break;

    case GameState::Title:
      title();
      break;

		case GameState::PlayGame_Init: 
      playGame_Init();
      playGame();
      playGame_Render();
			break;

		case GameState::PlayGame: 
      playGame();
      playGame_Render();
			break;

		default: break;	

	}

  arduboy.display();

  // Clear to white ..
  memset(arduboy.sBuffer, 0xff, 1024);

}
