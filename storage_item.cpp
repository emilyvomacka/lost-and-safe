#include "storage_item.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;

StorageItem::StorageItem(string& text) {
    version = VERSION;
    timesReturned = 0;
    timeLastSurfaced = time(nullptr);
    text = text;
}

int StorageItem::getVersion() { return version; }

time_t StorageItem::getTimeLastSurfaced() { return timeLastSurfaced; }

int StorageItem::getTimesReturned() { return timesReturned; }

string StorageItem::getText() { return text; }

void StorageItem::serialize(const string& filename) {
    ofstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error: Failed to open file for writing."
            << std::endl;
        return;
    }
    file.write(reinterpret_cast<const char*>(this),
                sizeof(*this));
    file.close();
    cout << "Object serialized successfully." << endl;
}
