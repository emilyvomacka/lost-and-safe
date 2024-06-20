#include <string>
#include <ctime>
#include <stdexcept>

int VERSION = 1; 

class StorageItem {
  public:
    StorageItem(std::string text); 

    StorageItem(int version, int timesReturned, time_t timeLastSurfaced, std::string text); 

    int getVersion();

    time_t getTimeLastSurfaced();

    int getTimesReturned();

    std::string getText();

    void serialize(const std::string& filename); 

    static StorageItem deserialize(const std::string& filename);

  private:
    int version_;
    int timesReturned_;
    time_t timeLastSurfaced_;   
    std::string text_;
};