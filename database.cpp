#include "database.h"
#include <iostream>
using namespace std;

Database::Database(string& filename) {
  // create new db
  filename_ = filename;
}

void Database::store(string& input) {
  StorageItem practiceItem = StorageItem(input);
  // Create an ofstream instance and open the file
  ofstream f(filename_, ios::binary | ios::app);
  if (f.is_open()) {
    practiceItem.serialize(f);
  } else {
      cerr << "Unable to open file: " << filename_ << endl;
  }
  f.close();
}

StorageItem Database::recall() {
  ifstream f(filename_, ios::binary|ios::in);
  if (f.fail()) { 
    cerr << "Error details: " << strerror(errno) 
        << endl; 
  } 
  if (f.is_open()) {
    vector<StorageItem> results;
    while // TKTK file is not at the end
    StorageItem recalled = StorageItem::deserialize(f);
    results.push_back(recalled);
    }
    f.close();
    return database.chooseResult();
  }
  return (StorageItem) NULL;
}