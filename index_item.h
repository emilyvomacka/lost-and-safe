#ifndef _index_item_
#define _index_item_

#include <string>
#include <ctime>
#include <stdexcept>
#include "storage_item.h"


class IndexItem {
  public:
    IndexItem(int id, int timesReturned, time_t timeLastSurfaced, float randomFactor);

    int getScore();

    unsigned int getId();

  private:
    int score_;
    unsigned int id_; // seek distance

    int calculateScore(int timesReturned, time_t timeLastSurfaced, float randomFactor);
};

#endif