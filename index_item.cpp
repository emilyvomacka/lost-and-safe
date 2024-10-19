#include "index_item.h"
#include "math.h"
#include <iostream>

using namespace std;

//#define FREQUENCY_EXP 0.1

IndexItem::IndexItem(int id, int timesReturned, time_t timeLastSurfaced, float randomFactor) {
  id_ = id;
  score_ = calculateScore(timesReturned, timeLastSurfaced, randomFactor);
}

int IndexItem::getScore() {
  return score_;
}

unsigned int IndexItem::getId() {
  return id_;
}

int IndexItem::calculateScore(int timesReturned, time_t timeLastSurfaced, float randomFactor) {
  int score = randomFactor * pow(0.1, timesReturned) * (time(nullptr) - timeLastSurfaced);
  return score;
}
