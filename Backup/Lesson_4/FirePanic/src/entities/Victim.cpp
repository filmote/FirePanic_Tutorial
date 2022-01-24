#include "Victim.h"
#include "../utils/Physics.h"

Victim::Victim() { 

  this->enabled = false;
  this->posIndex = 0;

}

uint8_t Victim::getX() {

  return this->x;

}

uint8_t Victim::getY() {

  return this->y;

}

uint8_t Victim::getPosIndex() {

  return this->posIndex;

}

uint8_t Victim::getRotation() {

  return this->rotIndex;

}

uint8_t Victim::getEnabled() {

  return this->enabled;

}

bool Victim::getPrevBounce() {

  return this->prevBounce;

}

void Victim::setEnabled(bool value) {

  this->enabled = value;

}

void Victim::setPrevBounce(bool value) {

  this->prevBounce = value;

}

void Victim::init(uint8_t level) {

  this->enabled = true;
  this->posIndex = 0;  
  this->startingLevel = level;

  this->x = pgm_read_word_near(&Physics_Arc_1[this->startingLevel][this->posIndex * 2]);
  this->y = pgm_read_word_near(&Physics_Arc_1[this->startingLevel][this->posIndex * 2] + 1);

}

void Victim::move() {
  
  if (this->enabled) {
    this->posIndex++;  
  }
  else {
    this->posIndex = 255;
  }

  if (this->posIndex == PYHSICS_ARC_NO_OF_ELEM) {
    this->posIndex = 0;
    this->enabled = false;
    return;
  }

  if (this->posIndex < 11) {
    this->x = pgm_read_word_near(&Physics_Arc_1[this->startingLevel][this->posIndex * 2]);
    this->y = pgm_read_word_near(&Physics_Arc_1[this->startingLevel][this->posIndex * 2] + 1);
  }
  else {
    this->x = pgm_read_word_near(&Physics_Arc_2[(this->posIndex - 11) * 2]);
    this->y = pgm_read_word_near(&Physics_Arc_2[(this->posIndex - 11) * 2] + 1);
  }

}

void Victim::rotate() {

  this->rotIndex++;
  if (this->rotIndex == 8) this->rotIndex = 0;

}