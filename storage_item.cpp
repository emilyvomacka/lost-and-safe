#include "storage_item.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;
extern int VERSION;

StorageItem::StorageItem(string text) {
    version_ = VERSION;
    timesReturned_ = 0;
    timeLastSurfaced_ = time(nullptr);
    text_ = text;
}

StorageItem::StorageItem(int version, int timesReturned, time_t timeLastSurfaced, string text) {
    version_ = version;
    timesReturned_ = timesReturned;
    timeLastSurfaced_ = timeLastSurfaced;
    text_ = text;
}

int StorageItem::getVersion() { return version_; }

int StorageItem::getTimesReturned() { return timesReturned_; }

time_t StorageItem::getTimeLastSurfaced() { return timeLastSurfaced_; }

string StorageItem::getText() { 
    return text_; 
}

void StorageItem::serialize(ofstream& f) {
        cout << "BEGIN SERIALIZE " << f.tellp() << endl;
        f.write(reinterpret_cast<char*>(&version_), sizeof version_);
        f.write(reinterpret_cast<char*>(&timesReturned_), sizeof(int));
        f.write(reinterpret_cast<char*>(&timeLastSurfaced_), sizeof(time_t));
        // first write the size of the string for deserialization
        unsigned long textLength = text_.length();
        f.write(reinterpret_cast<char*>(&textLength), sizeof textLength);
        f.write(text_.c_str(), text_.length());
        cout << "END SERIALIZE " << endl;
    }

StorageItem StorageItem::deserialize(ifstream& f) {
    int version;
    int timesReturned;
    time_t timeLastSurfaced;
    unsigned long textLength;
    
    f.read(reinterpret_cast<char*>(&version), sizeof version);
    f.read(reinterpret_cast<char*>(&timesReturned), sizeof timesReturned);
    f.read(reinterpret_cast<char*>(&timeLastSurfaced), sizeof timeLastSurfaced);
    f.read(reinterpret_cast<char*>(&textLength), sizeof textLength);
    char text[textLength];
    f.read(reinterpret_cast<char*>(text), textLength);
    
    return StorageItem(version, timesReturned, timeLastSurfaced, text);
}