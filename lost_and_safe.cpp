#include "storage_item.cpp"
#include <iostream>

using namespace std;

int main()
{
  cout << "here is: lost and safe" << endl;
  string input = "Give up your books and put an end to your worries. Enjoy Central Park in spring";
  StorageItem practice = StorageItem(input);
  cout << "version: " << practice.getVersion() << endl;
  cout << "timeLastSurfaced: " << practice.getTimeLastSurfaced() << endl;
  cout << "text: " << practice.getText() << endl;
}