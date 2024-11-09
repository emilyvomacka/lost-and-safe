#include "index_item.h"
#include "storage_item.h"
#include "optional"
#include <vector>

class Database {
  public:
    Database(std::string& filename);

    void store(std::string& input);

    std::optional<StorageItem> recall();

  private:
    std::string filename_;
    std::vector<IndexItem> results_;
    int returnQuantity_;
    int itemsReturned_;

    std::vector<IndexItem> initializeQueue();
    IndexItem chooseResult();
    StorageItem deserializeFromIndex(int index);
    void serializeStorageItem(StorageItem storageItem);
    void reserializeStorageItem(StorageItem storageItem, int index);
};
