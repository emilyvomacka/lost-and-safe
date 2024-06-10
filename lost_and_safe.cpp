#include "storage_item.cpp"
#include <iostream>

using namespace std;

int main()
{
  cout << "here is: lost and safe" << endl;
  string input = "Give up your books and put an end to your worries. Enjoy Central Park in spring";
  StorageItem practiceItem = StorageItem(input);
  cout << "version: " << practiceItem.getVersion() << endl;
  cout << "timeLastSurfaced: " << practiceItem.getTimeLastSurfaced() << endl;
  cout << "text: " << practiceItem.getText() << endl;

  string file = "./test_db.bin";
  practiceItem.serialize(file);
}