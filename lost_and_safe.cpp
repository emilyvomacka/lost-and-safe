#include "storage_item.cpp"
#include "database.cpp"
#include <iostream>

using namespace std;

int main()
{
  cout << "here is: lost and safe" << endl;
  string file = "/Users/emilyvomacka/code/recurse/cpp/lost-and-safe/test_db.bin";
  
  Database db = Database(file);
  string input = "Give up your books and put an end to your worries. Enjoy Central Park in spring";
  db.store(input);

  StorageItem retrievedItem = db.recall();
  cout << "retrieved item: ";
  cout << "version is: " << retrievedItem.getVersion() << endl;
  cout << "times returned: " << retrievedItem.getTimesReturned() << endl;
  cout << "timeLastSurfaced: " << retrievedItem.getTimeLastSurfaced() << endl;
  cout << "text: " << retrievedItem.getText() << endl;
}
