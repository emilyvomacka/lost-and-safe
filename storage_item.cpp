#include "storage_item.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;
 
#define VERSION 1;

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

int* StorageItem::getVersionPointer() { return &version_; }

int StorageItem::getTimesReturned() { return timesReturned_; }

int* StorageItem::getTimesReturnedPointer() { return &timesReturned_; }

void StorageItem::setTimesReturned(int timesReturned) {
    timesReturned_ = timesReturned;
}

time_t StorageItem::getTimeLastSurfaced() { return timeLastSurfaced_; }

time_t* StorageItem::getTimeLastSurfacedPointer() { return &timeLastSurfaced_; }

void StorageItem::setTimeLastSurfaced(time_t time) {
    timeLastSurfaced_ = time;
}

string StorageItem::getText() { 
    return text_; 
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