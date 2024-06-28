#include "storage_item.h"

class Database {
  public:
    Database(std::string& filename);

    void store(std::string& input);

    StorageItem recall();

  private:
    std::string filename_;
    StorageItem chooseResult();
};