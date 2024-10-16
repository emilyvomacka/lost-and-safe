#include "storage_item.h"
#include "database.h"
#include <iostream>
#include <string>
#include <optional>

using namespace std;

// Driver file while prototyping the backend
int main(int argc, char* argv[])
{
  cout << "here is: lost and safe" << endl;
  string fileName = "test_db.bin";

  // Parse command line arguments
  if (argc > 1) {
    fileName = argv[1];
  } 
  
  Database db = Database(fileName);
  string input = "Give up your books and put an end to your worries. Enjoy Central Park in spring";
  db.store(input);

  string retrievedText = db.recall();
  cout << "retrieved item: " << retrievedText;
};
