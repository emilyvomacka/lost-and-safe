#include "storage_item.cpp"
#include <iostream>

using namespace std;

int main()
{
  cout << "here is: lost and safe" << endl;
  string input = "Give up your books and put an end to your worries. Enjoy Central Park in spring";
  StorageItem practiceItem = StorageItem(input);
  cout << "version: " << practiceItem.getVersion() << endl;
  cout << "timesReturned " << practiceItem.getTimesReturned() << endl;
  cout << "timeLastSurfaced: " << practiceItem.getTimeLastSurfaced() << endl;
  cout << "text: " << practiceItem.getText() << endl;

  string file = "/Users/emilyvomacka/code/recurse/cpp/lost-and-safe/test_db.bin";
  
  practiceItem.serialize(file);
  StorageItem retrievedItem = StorageItem::deserialize(file);
  cout << "retrieved item: ";
  cout << "version is: " << retrievedItem.getVersion() << endl;
  cout << "times returned: " << retrievedItem.getTimesReturned() << endl;
  cout << "timeLastSurfaced: " << retrievedItem.getTimeLastSurfaced() << endl;
  cout << "text: " << retrievedItem.getText() << endl;
}