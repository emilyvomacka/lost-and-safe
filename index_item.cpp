#include "index_item.h"

using namespace std;

IndexItem::IndexItem(int id, int timesReturned, time_t timeLastSurfaced) {
  id_ = id;
  score_ = calculateScore(id, timesReturned, timeLastSurfaced);
}

int IndexItem::getScore() {
  return score_;
}

unsigned int IndexItem::getId() {
  return id_;
}

int IndexItem::calculateScore(int id, int timesReturned, time_t timeLastSurfaced) {
  return 1;
}
