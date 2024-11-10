#include "storage_item.h"
#include "database.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <optional>
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  string fileName = string(getenv("HOME")).append("/.lsdb.bin");

  // Parse command line arguments
  if (argc < 2) {
    cout << "Please append store or recall" << endl;
    return -1;
  }

  string subcommand = argv[1];

  if (subcommand == "store") {
    if (argc != 3) {
      cout << "Please try: lsdb store <text>, being sure to enclose the text in single quotes" << endl;
      return -1;
    }
    Database db = Database(fileName);
    string text = argv[2];
    db.store(text);
    cout << "Successfully stored: " << text << endl;
  } else if (subcommand == "recall") {
    if (argc != 2) {
      cout << "Please try: lsdb recall" << endl;
      return -1;
    }
    Database db = Database(fileName);
    if (optional<StorageItem> item = db.recall()) {
      cout << endl << item->getText() << endl << endl;
      time_t time = item->getTimeLastSurfaced();
      cout << "Last seen on: " << put_time(localtime(&time), "%c %Z") << endl;
      cout << "Surfaced " << item->getTimesReturned() << " times previously" << endl << endl;
    }
  } else {
    cout << "Available subcommands: store <text>, recall" << endl;
    return -1;
  }
  return 0;
};
