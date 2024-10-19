#include "storage_item.h"
#include "database.h"
#include <iostream>
#include <set>
#include <string>
#include <optional>

using namespace std;

// Driver file while prototyping the backend
int main(int argc, char* argv[])
{
  cout << "here is: lost and safe" << endl;
  string fileName = "test_db.bin";

  // Parse command line arguments
  if (argc < 2) {
    cout << "Please append store or recall" << endl;
    return -1;
  }

  string subcommand = argv[1];

  if (subcommand == "store") {
    if (argc != 3) {
      cout << "Please try: lsdb store <text>, being sure to enclose the text in quotes" << endl;
      return -1;
    }
    Database db = Database(fileName);
    string text = argv[2];
    db.store(text);
    cout << "Successfully stored " << text << endl;
  } else if (subcommand == "recall") {
    if (argc != 2) {
      cout << "Please try: lsdb recall" << endl;
      return -1;
    }
    Database db = Database(fileName);
    cout << db.recall() << endl;
  } else {
    cout << "Available subcommands: store <text>, recall" << endl;
    return -1;
  }
  return 0;
};
