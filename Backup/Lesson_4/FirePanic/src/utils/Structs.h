#pragma once
#include "Enums.h"
#include "../entities/Entities.h"


struct PlayGameVars {

  Victim victims[VICTIMS_MAX_NUMBER];

  uint16_t victimCountdown = 200;
  uint8_t victimDelay = 1;
  uint8_t victimLevel = 0;
  uint16_t score = 0;
  uint8_t misses = 0;

  bool paused = false;
  bool gameOver = false;

  void resetGame() {

    this->misses = 0;
    this->score = 0; 
    this->gameOver = false;

  }

};