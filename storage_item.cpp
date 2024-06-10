#include "storage_item.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;

StorageItem::StorageItem(string textInput) {
    text = textInput;
    version = VERSION;
    timesReturned = 0;
    timeLastSurfaced = time(nullptr);   
}

int StorageItem::getVersion() { return version; }

time_t StorageItem::getTimeLastSurfaced() { return timeLastSurfaced; }

int StorageItem::getTimesReturned() { return timesReturned; }

string StorageItem::getText() { 
    return text; 
}

void StorageItem::serialize(const string& filename) {
    // Create an ofstream instance and open the file
    ofstream file(filename, ios::binary);

    // Check if the file was opened successfully
    if (file.is_open()) {
        // Write the version number
        file.write("Helloworld!\n", 13);
        // Close the file
        file.close();
    } else {
        // If the file could not be opened, print an error message
        cerr << "Unable to open file: " << filename << endl;
    }
}
