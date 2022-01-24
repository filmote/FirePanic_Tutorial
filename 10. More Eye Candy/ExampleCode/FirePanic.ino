#include "src/utils/Arduboy2Ext.h"

#include "src/images/Images.h"
#include "src/utils/Utils.h"
#include "src/utils/Enums.h"
#include "src/utils/Structs.h"
#include "src/utils/EEPROM_Utils.h"
#include "src/images/Images.h"
#include "src/sounds/Sounds.h"
#include "src/arduboyTones/ArduboyTonesExt.h"

Arduboy2Ext arduboy;
ArduboyTonesExt sound;

GameState gameState = GameState::Title_Init;

GameIntroVars gameIntroVars;
HighScoreVars highScoreVars;
PlayGameVars playGameVars;
TitleScreenVars titleScreenVars;

void setup() {

	arduboy.boot();
	arduboy.flashlight();
	arduboy.systemButtons();
	arduboy.audio.begin();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(75);


	EEPROM_Utils::initialiseEEPROM();

	gameState = GameState::Title_Init; 

}

void loop() {

	if (!arduboy.nextFrame()) return;
	arduboy.pollButtons();

	switch (gameState) {

		case GameState::Title_Init:
      title_Init(); 
      title();
      title_Render();
      break;

    case GameState::Title:
      title();
      title_Render();
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

		case GameState::GameIntro_Arrive_Init: 
		case GameState::GameIntro_Leave_Init: 
      gameIntro_Init();
      gameIntro();
      gameIntro_Render();
      break;

		case GameState::GameIntro_Arrive: 
		case GameState::GameIntro_Leave: 
      gameIntro();
      gameIntro_Render();
      break;

		case GameState::HighScore_Init:
      highScore_Init(); 
      highScore(); 
      highScore_Render(); 
      break;

		case GameState::HighScore:
      highScore(); 
      highScore_Render(); 
      break;

		default: break;	

	}

  arduboy.display();

  // Clear to white ..
  memset(arduboy.sBuffer, 0xff, 1024);

}
