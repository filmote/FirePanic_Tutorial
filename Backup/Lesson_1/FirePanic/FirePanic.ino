#include <Arduboy2.h>

#include "src/utils/Enums.h"

Arduboy2 arduboy;

GameState gameState = GameState::Title_Init;

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
  arduboy.clear();

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
			break;

		case GameState::PlayGame: 
      playGame();
			break;

		default: break;	

	}

  arduboy.display();

}
