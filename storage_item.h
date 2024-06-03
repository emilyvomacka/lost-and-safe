#include <string>
#include <ctime>

class Storage {
  public:
    std::string getText();
    int getVersion();
    time_t getDateAdded();
    int getTimesReferenced();

  private:
    std::string text;
    int version;
    time_t dateAdded;   
    int timesReferenced;
};