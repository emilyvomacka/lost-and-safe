#include "database.h"
#include <iostream>
#include <optional>
#include <vector> 
#include <fstream>

using namespace std;

struct compareScore {
  bool operator()(IndexItem& a, IndexItem& b) const {
    return a.getScore() > b.getScore();
  }
};

Database::Database(string& filename) {
  // create new db
  filename_ = filename;
  results_ = initializeQueue();
  returnQuantity_ = std::rand() % 9;
  itemsReturned_ = 0;
  cout << "db initialized, return quantity is " << returnQuantity_ << endl;
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

void Database::serializeStorageItem(StorageItem storageItem) {
  ofstream f(filename_, ios::binary | ios::app);
  if (!f.is_open()) {
      cerr << "Unable to open file: " << filename_ << endl;
      return;
  }
  cout << "BEGIN DATABASE SERIALIZE " << f.tellp() << endl;
  f.write(reinterpret_cast<char*>(storageItem.getVersionPointer()), sizeof(int));
  f.write(reinterpret_cast<char*>(storageItem.getTimesReturnedPointer()), sizeof(int));
  f.write(reinterpret_cast<char*>(storageItem.getTimeLastSurfacedPointer()), sizeof(time_t));
  // first write the size of the string for deserialization
  unsigned long textLength = storageItem.getText().length();
  f.write(reinterpret_cast<char*>(&textLength), sizeof(unsigned long));
  f.write(storageItem.getText().c_str(), textLength);
  cout << "END DATABASE SERIALIZE " << endl;
}

void Database::serializeStorageItem(StorageItem storageItem, int index) {
  ofstream f(filename_, ios::binary|ios::out);
  if (!f.is_open()) {
      cerr << "Unable to open file: " << filename_ << endl;
      return;
  }
  f.seekp(index, std::ios_base::beg);
  serializeStorageItem(storageItem);
}

string Database::recall() {
  if (itemsReturned_ == returnQuantity_) {
    return "Only " + to_string(returnQuantity_) + " items will be returned today.";
  }

  IndexItem resultIndex = Database::chooseResult();

  StorageItem resultItem = Database::deserializeFromIndex(resultIndex.getId());
  // set time last seen
  resultItem.setTimeLastSurfaced(time(nullptr));
  // set times returned
  resultItem.setTimesReturned(resultItem.getTimesReturned() + 1);
  // serialize it 


  return resultItem.getText();
}

IndexItem Database::chooseResult() {
  std::pop_heap(results_.begin(), results_.end(), compareScore());
  IndexItem res = results_.back();
  results_.pop_back();
  itemsReturned_++;
  return res;
} 

vector<IndexItem> Database::initializeQueue() {
  ifstream f(filename_, ios::binary|ios::in);
  if (f.fail()) { 
    cerr << "Error details: " << strerror(errno) 
        << endl;
  }
  vector<IndexItem> results;
  if (f.is_open()) {
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

      IndexItem item = IndexItem(id, timesReturned, timeLastSurfaced);  
      results.push_back(item);
      
      f.seekg(textLength, std::ios_base::cur);
    }
    std::make_heap(results.begin(), results.end(), compareScore());
  }
  return results;
}
