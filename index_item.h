#ifndef _index_item_
#define _index_item_

#include <string>
#include <ctime>
#include <stdexcept>
#include "storage_item.h"


class IndexItem {
  public:
    IndexItem(StorageItem& storageItem, unsigned int id); 

    int getTimesReturned();

    time_t getTimeLastSurfaced();

    unsigned int getRandomFactor();

    unsigned int getId();

  private:
    int timesReturned_;
    time_t timeLastSurfaced_;
    unsigned int randomFactor_;
    unsigned int id_; // seek distance
};

#endif