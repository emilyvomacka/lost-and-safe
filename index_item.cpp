#include "index_item.h"

using namespace std;

IndexItem::IndexItem(int id, time_t timeLastSurfaced) {
  id_ = id;
  score_ = calculateScore(id, timeLastSurfaced);
}

int IndexItem::getScore() {
  return score_;
}

unsigned int IndexItem::getId() {
  return id_;
}

int calculateScore(int id, time_t timeLastSurfaced) {
  return 1;
}
