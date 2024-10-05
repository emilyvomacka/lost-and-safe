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
  IndexItem result = Database::chooseResult();
  // TODO
  return ""; //result.getText();
}

IndexItem Database::chooseResult() {
  std::srand(std::time(nullptr));
  int i = std::rand() % results_.size();
  cout << "we have " << results_.size() << " items, returning number " << i << endl;
  return results_.at(i);
}

vector<IndexItem> Database::initializeQueue() {
  ifstream f(filename_, ios::binary|ios::in);
  if (f.fail()) { 
    cerr << "Error details: " << strerror(errno) 
        << endl;
  }
  vector<IndexItem> results;
  if (f.is_open()) {
    while (f.peek() != EOF) {
      int timesReturned;
      time_t timeLastSurfaced;
      unsigned long textLength;
      
      // Skipping past version right now as we're on version 1
      f.seekg(sizeof(int), std::ios_base::cur);
      f.read(reinterpret_cast<char*>(&timesReturned), sizeof timesReturned);
      f.read(reinterpret_cast<char*>(&timeLastSurfaced), sizeof timeLastSurfaced);
      f.read(reinterpret_cast<char*>(&textLength), sizeof textLength);

      IndexItem item = IndexItem(1, timesReturned, timeLastSurfaced);  
      results.push_back(item);
      
      f.seekg(textLength, std::ios_base::cur);
    }
  }
  return results;
}
