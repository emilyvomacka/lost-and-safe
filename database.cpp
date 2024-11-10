#include "database.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <random>
#include <string>
#include <vector> 

using namespace std;

#define RANDOM_FACTOR 0.5f

Database::Database(string& filename) {
  filename_ = filename;
  results_ = initializeQueue();
  srand(time(0));
  returnQuantity_ = std::rand() % 5 + 3;
  itemsReturned_ = 0;
}

struct compareScore {
  bool operator()(IndexItem& a, IndexItem& b) const {
    return a.getScore() < b.getScore();
  }
};

vector<IndexItem> Database::initializeQueue() {
  ifstream f(filename_, ios::binary|ios::in);
  vector<IndexItem> results;
  // Only initialize queue if a db file exists to query from.
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
  ofstream f(filename_, ios::binary|ios::app);
  if (!f.is_open()) {
      cerr << "Unable to open file: " << filename_ << endl;
      return;
  }
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
  // We never change the version, skip past it.
  f.seekp(sizeof(int), std::ios_base::cur);
  // Write the updated timesReturned and timeLastSurfaced vars.
  f.write(reinterpret_cast<char*>(storageItem.getTimesReturnedPointer()), sizeof(int));
  f.write(reinterpret_cast<char*>(storageItem.getTimeLastSurfacedPointer()), sizeof(time_t));
  // We never change the text, so no updates necessary there.
}

optional<StorageItem> Database::recall() {
  if (itemsReturned_ == returnQuantity_) {
    cout << "Only " + to_string(returnQuantity_) + " items will be returned today." << endl;
    return nullopt;
  }
  if (results_.size() == 0) {
    cout << "Nothing here yet, try adding something?" << endl;
    return nullopt;
  }

  IndexItem resultIndex = Database::chooseResult();

  StorageItem resultItem = Database::deserializeFromIndex(resultIndex.getId());
  StorageItem copyItem = resultItem;

  // Update resultItem so it doesn't resurface as easily next time.
  resultItem.setTimeLastSurfaced(time(nullptr));
  resultItem.setTimesReturned(resultItem.getTimesReturned() + 1);
  Database::reserializeStorageItem(resultItem, resultIndex.getId());

  return copyItem;
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
  // Add 1 for the null terminator
  char text[textLength + 1];
  f.read(reinterpret_cast<char*>(text), textLength);
  text[textLength] = '\0';
  // Reassign the char[] to a std::string, to avoid potential clobbering!
  string s(text);
  return StorageItem(version, timesReturned, timeLastSurfaced, s);
}
