#include "storage_item.h"
#include "database.h"
#include <iostream>
#include <string>
#include <optional>

using namespace std;

enum ParseReturnCode { 
  OK = 0, 
  ERROR = 1,
  HELP = 2,
  VERSION = 3,
};

// Driver file while prototyping the backend
int main(int argc, char* argv[])
{
  cout << "here is: lost and safe" << endl;
  string defaultFile = "../test_db.bin";

  // Parse command line arguments
  //int parseCode = Arguments:: 
  
  Database db = Database(defaultFile);
  string input = "Give up your books and put an end to your worries. Enjoy Central Park in spring";
  db.store(input);

  string retrievedText = db.recall();
  cout << "retrieved item: " << retrievedText;
};


class Arguments {
  
  string filename;
  optional<string> name;

  Arguments() {
    filename = "./test_db.bin";
    name = nullopt;
  }

  ParseReturnCode parse(int argc, char* argv[]) {
    // while (so we can increment by two if flag)

    // if it doesn't begin with --, return ERROR

    // if name, ++ input and assign to name field

    // if filename, ++ input assign to filename

    // if "v", return VERSION

    // if "h", return HELP

    
    return ParseReturnCode::OK;
  }


};

