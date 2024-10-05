#include "index_item.h"
#include "storage_item.h"
#include <vector>

class Database {
  public:
    Database(std::string& filename);

    void store(std::string& input);

    std::string recall();

  private:
    std::string filename_;
    std::vector<IndexItem> results_;

    std::vector<IndexItem> initializeQueue();
    IndexItem chooseResult();
};