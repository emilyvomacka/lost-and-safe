#include <string>
#include <ctime>
#include <stdexcept>

int VERSION = 1; 

class StorageItem {
  public:
    StorageItem(std::string text); 

    int getVersion();

    time_t getTimeLastSurfaced();

    int getTimesReturned();

    std::string getText();

    void serialize(const std::string& filename); 

    // StorageItem deserialize(std::string filename);

  private:
    int version;
    time_t timeLastSurfaced;   
    int timesReturned;
    std::string text;
};