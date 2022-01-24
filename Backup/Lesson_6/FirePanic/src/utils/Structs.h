#pragma once
#include "Enums.h"
#include "../entities/Entities.h"

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

  uint8_t counter = 0;
  uint16_t victimCountdown = 200;
  uint8_t victimDelay = 1;
  uint8_t victimLevel = 0;

  uint16_t score = 0;
  uint8_t misses = 0;
  int16_t health = 0;
  uint16_t level = 0;
  uint8_t xPosition = 0;  // Player x position between sequences ..

  bool paused = false;
  bool gameOver = false;

  void resetGame() {

    this->level = 0;
    this->health = 0;
    this->misses = 0;
    this->score = 0; 
    this->gameOver = false;

  }

};