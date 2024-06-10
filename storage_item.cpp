#include "storage_item.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;
extern int VERSION;

StorageItem::StorageItem(string textInput) {
    version = VERSION;
    timesReturned = 0;
    timeLastSurfaced = time(nullptr);
    text = textInput;
}

int StorageItem::getVersion() { return version; }

int StorageItem::getTimesReturned() { return timesReturned; }

time_t StorageItem::getTimeLastSurfaced() { return timeLastSurfaced; }

string StorageItem::getText() { 
    return text; 
}

void StorageItem::serialize(const string& filename) {
    // Create an ofstream instance and open the file
    ofstream f(filename, ios::binary | ios::app);

    // Check if the file was opened successfully
    if (f.is_open()) {
        // Test text
        f.write("Helloworld!", 11);
        // Write the version number
        int version = getVersion();
        cout << "version is " << version << endl;
        cout << "size is " << sizeof version << endl;
        f.write(reinterpret_cast<char*>(&version), sizeof version);
        f.flush();
    //     f.write(reinterpret_cast<char*>(timesReturned), sizeof(int));
    //     f.write(reinterpret_cast<char*>(timeLastSurfaced), sizeof(time_t));
    //     // first write the size of the string for deserialization
    //     int textLength = getText().length();
    //     cout << "text length is " << textLength << endl;
    //     f.write(reinterpret_cast<char*>(textLength), sizeof(unsigned long));
    //     f.write(getText().c_str(), textLength);
    //     // Close the file
        f.close();
    // } else {
    //     // If the file could not be opened, print an error message
    //     cerr << "Unable to open file: " << filename << endl;
    }
}
