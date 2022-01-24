#pragma once
#include "Enums.h"
#include "../entities/Entities.h"

struct SaveEntry {

	static constexpr size_t nameSize = NAME_LENGTH_PLUS_TERM;
	static constexpr size_t nameCount = (nameSize - 1);

	uint16_t score;
	char name[nameSize];

};

struct HighScoreVars {

  uint8_t winnerIdx = 0;
  uint8_t charIdx = 0;
  uint8_t clearScores = 0;
  uint8_t pressACounter = HS_PRESS_A_DELAY;

  SaveEntry players[eepromSaveEntriesCount];

  void reset() {

    this->winnerIdx = 0;
    this->charIdx = 0;
    this->clearScores = 0;
    this->pressACounter = HS_PRESS_A_DELAY;

  }

};

struct GameIntroVars {

  uint8_t xAmbulance = 156;
  uint8_t xPlayer = 0;
  uint8_t counter = 0;
  uint8_t speedInc = 0;    
  
  bool ambulanceDoor = false;
  bool playerImageIndex = false;

  void reset() {

    this->xAmbulance = 156;
    this->xPlayer = 0;
    this->counter = 0;
    this->speedInc = 0;    
    
    this->ambulanceDoor = false;
    this->playerImageIndex = false;

  }
  
};

struct TitleScreenVars {

  uint8_t restart = 0;
  uint8_t flameCounter = 0;
  uint8_t pressACounter = 0;

  uint8_t sloganCaption = 0;
  uint8_t sloganHeight = 0;
  bool sloganDisplay = false;

  void reset() {
    this->restart = 0;
    this->flameCounter = 0;
    this->pressACounter = 0;

    this->sloganCaption = 0;
    this->sloganHeight = 0;
    this->sloganDisplay = false;
  }

};

struct PlayGameVars {

  Victim victims[VICTIMS_MAX_NUMBER];
  Player player;
  Angel angel;

  uint8_t counter = 0;
  uint8_t puffIndex = 0;
  uint16_t victimCountdown = 200;
  uint8_t victimDelay = 1;
  uint8_t victimLevel = 0;

  bool takeARest = false;

  uint8_t smokeIndex;
  bool paused = false;
  LightsState lights = LightsState::Lights_1;

  uint16_t score = 0;
  uint8_t misses = 0;
  int16_t health = 0;
  uint16_t level = 0;
  uint8_t xPosition = 0;  // Player x position between sequences ..
  uint16_t targetScore = 0;
  bool gameOver = false;

  void resetGame() {

    this->level = 0;
    this->health = 0;
    this->misses = 0;
    this->score = 0; 
    this->gameOver = false;

  }

};