#ifndef _storage_item_
#define _storage_item_

#include <string>
#include <ctime>
#include <stdexcept>


class StorageItem {
  public:
    StorageItem(std::string text); 

    StorageItem(int version, int timesReturned, time_t timeLastSurfaced, std::string text); 

    int getVersion();

    int* getVersionPointer();

    time_t getTimeLastSurfaced();

    time_t* getTimeLastSurfacedPointer();

    void setTimeLastSurfaced(time_t timeLastSurfaced);

    int getTimesReturned();
    
    int* getTimesReturnedPointer();

    void setTimesReturned(int timesReturned);

    std::string getText();

    static StorageItem deserialize(std::ifstream& f);

  private:
    int version_;
    int timesReturned_;
    time_t timeLastSurfaced_;   
    std::string text_;
};

#endif