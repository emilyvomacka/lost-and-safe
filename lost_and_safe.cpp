#include "storage_item.h"
#include "database.h"
#include <iostream>

using namespace std;

// Driver file while prototyping the backend
int main()
{
  cout << "here is: lost and safe" << endl;
  string file = "/Users/emilyvomacka/code/recurse/cpp/lost-and-safe/test_db.bin";
  
  Database db = Database(file);
  string input = "Give up your books and put an end to your worries. Enjoy Central Park in spring";
  db.store(input);

  string retrievedText = db.recall();
  cout << "retrieved item: " << retrievedText;
  // cout << "version is: " << retrievedItem.getVersion() << endl;
  // cout << "times returned: " << retrievedItem.getTimesReturned() << endl;
  // cout << "timeLastSurfaced: " << retrievedItem.getTimeLastSurfaced() << endl;
  // cout << "text: " << retrievedItem.getText() << endl;
}
