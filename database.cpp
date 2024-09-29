#include "database.h"
#include <iostream>
#include <vector> 
#include <fstream>

using namespace std;

Database::Database(string& filename) {
  // create new db
  filename_ = filename;
  results_ = initializeQueue();
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

string Database::recall() {
  // TODO
  StorageItem result = Database::chooseResult();
  return result.getText();
}

StorageItem Database::chooseResult() {
  std::srand(std::time(nullptr));
  int i = std::rand() % results_.size();
  cout << "we have " << results_.size() << " items, returning number " << i << endl;
  return results_.at(i);
}

vector<StorageItem> Database::initializeQueue() {
  ifstream f(filename_, ios::binary|ios::in);
  if (f.fail()) { 
    cerr << "Error details: " << strerror(errno) 
        << endl;
  }
  vector<StorageItem> results;
  if (f.is_open()) {
    int i = 0;
    while (f.peek() != EOF) {
      StorageItem newItem = StorageItem::deserialize(f);
      results.push_back(newItem);
      cout << "read item number " << i << endl;
      i++;
    }
  }
  return results;
}
