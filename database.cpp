#include "database.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <vector> 

using namespace std;

#define RANDOM_FACTOR 0.5f

Database::Database(string& filename) {
  // create new db
  filename_ = filename;
  results_ = initializeQueue();
  returnQuantity_ = std::rand() % 9 + 1;
  itemsReturned_ = 0;
  cout << "db initialized, return quantity is " << returnQuantity_ << endl;
}

struct compareScore {
  bool operator()(IndexItem& a, IndexItem& b) const {
    return a.getScore() < b.getScore();
  }
};

vector<IndexItem> Database::initializeQueue() {
  ifstream f(filename_, ios::binary|ios::in);
  if (f.fail()) { 
    cerr << "Error details: " << strerror(errno) 
        << endl;
  }
  vector<IndexItem> results;
  if (f.is_open()) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(1 - RANDOM_FACTOR, 1 + RANDOM_FACTOR); 

    int id;
    int timesReturned;
    time_t timeLastSurfaced;
    unsigned long textLength;
    
    while (f.peek() != EOF) {
      id = f.tellg();
      // Skipping past version right now as we're on version 1
      f.seekg(sizeof(int), std::ios_base::cur);
      f.read(reinterpret_cast<char*>(&timesReturned), sizeof timesReturned);
      f.read(reinterpret_cast<char*>(&timeLastSurfaced), sizeof timeLastSurfaced);
      f.read(reinterpret_cast<char*>(&textLength), sizeof textLength);

      IndexItem item = IndexItem(id, timesReturned, timeLastSurfaced, distr(gen));  
      results.push_back(item);
      
      f.seekg(textLength, std::ios_base::cur);
    }
    std::make_heap(results.begin(), results.end(), compareScore());
  }
  return results;
}

void Database::store(string& input) {
  StorageItem item = StorageItem(input);
  ofstream f(filename_, ios::binary|ios::app);
  if (!f.is_open()) {
      cerr << "Unable to open file: " << filename_ << endl;
      return;
  }
  serializeStorageItem(item);
}

void Database::serializeStorageItem(StorageItem storageItem) {
  ofstream f(filename_, ios::binary | ios::app);
  if (!f.is_open()) {
      cerr << "Unable to open file: " << filename_ << endl;
      return;
  }
  cout << "serializing without specified index, file pointer at " << f.tellp() << endl;
  f.write(reinterpret_cast<char*>(storageItem.getVersionPointer()), sizeof(int));
  f.write(reinterpret_cast<char*>(storageItem.getTimesReturnedPointer()), sizeof(int));
  f.write(reinterpret_cast<char*>(storageItem.getTimeLastSurfacedPointer()), sizeof(time_t));
  // First write the size of the string for deserialization.
  unsigned long textLength = storageItem.getText().length();
  f.write(reinterpret_cast<char*>(&textLength), sizeof(unsigned long));
  f.write(storageItem.getText().c_str(), textLength);
}

void Database::reserializeStorageItem(StorageItem storageItem, int index) {
  fstream f(filename_, ios::binary|ios::in|ios::out);
  if (!f.is_open()) {
      cerr << "Unable to open file: " << filename_ << endl;
      return;
  }
  f.seekp(index, std::ios_base::beg);
  cout << "serializing with specified index, file pointer at " << f.tellp() << endl;
  // We never change the version, skip past it.
  f.seekg(sizeof(int), std::ios_base::cur);
  // Write the updated timesReturned and timeLastSurfaced vars.
  f.write(reinterpret_cast<char*>(storageItem.getTimesReturnedPointer()), sizeof(int));
  f.write(reinterpret_cast<char*>(storageItem.getTimeLastSurfacedPointer()), sizeof(time_t));
  // We never change the text, so no updates necessary there.
}

string Database::recall() {
  if (itemsReturned_ == returnQuantity_) {
    return "Only " + to_string(returnQuantity_) + " items will be returned today.";
  }
  if (results_.size() == 0) {
    return "Nothing here yet, try adding something?"; 
  }

  IndexItem resultIndex = Database::chooseResult();

  StorageItem resultItem = Database::deserializeFromIndex(resultIndex.getId());
  cout << "recalled item at index " << resultIndex.getId() << endl;
  // Update resultItem so it doesn't resurface as easily next time.
  resultItem.setTimeLastSurfaced(time(nullptr));
  resultItem.setTimesReturned(resultItem.getTimesReturned() + 1);
  cout << "result item has been updated, times returned is now " << resultItem.getTimesReturned() << endl;
  Database::reserializeStorageItem(resultItem, resultIndex.getId());

  return resultItem.getText();
}

IndexItem Database::chooseResult() {
  std::pop_heap(results_.begin(), results_.end(), compareScore());
  IndexItem res = results_.back();
  results_.pop_back();
  itemsReturned_++;
  return res;
} 

StorageItem Database::deserializeFromIndex(int id) {
  ifstream f(filename_, ios::binary|ios::in);
  if (f.fail()) { 
    cerr << "Error details: " << strerror(errno) << endl;
  }
  f.seekg(id, std::ios_base::beg); 
  
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








