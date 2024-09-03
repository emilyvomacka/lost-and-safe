#include "database.h"
#include <iostream>
#include <vector> 
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
  vector<StorageItem> results;
  if (f.is_open()) {
    StorageItem newItem = StorageItem::deserialize(f);
    results.push_back(newItem);
    f.close();
  }
  return results.back();
  }
