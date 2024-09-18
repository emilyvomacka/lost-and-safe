#include "index_item.h"

using namespace std;

IndexItem::IndexItem(int id, time_t timeLastSurfaced, int randomFactor) {
  id_ = id;
  score_ = calculateScore(id, timeLastSurfaced, randomFactor);
}

int IndexItem::getScore() {
  return score_;
}

unsigned int IndexItem::getId() {
  return id_;
}

int calculateScore(int id, time_t timeLastSurfaced, int randomFactor) {
  return 1;
}
