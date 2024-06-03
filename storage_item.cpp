#include "storage_item.h"

namespace L
{
    class Storage {
        std::string text;
        int version;
        time_t dateAdded;   
        int timesReferenced;
    };
}