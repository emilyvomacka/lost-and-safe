#include "database.h"
#include <__memory/temporary_buffer.h>
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
  returnQuantity_ = std::rand() % 3;
  itemsReturned_ = 0;
  cout << "db initialized, return quantity is " << returnQuantity_ << endl;
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
  if (itemsReturned_ < returnQuantity_) {
    IndexItem result = Database::chooseResult();
  }
  return ""; //result.getText();
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
