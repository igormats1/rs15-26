#include <iostream>

#include "lexer.h"
#include "parser.h"

using namespace std;


int main(int argc, char *argv[])
{
   while(true)
   {
    if (yyparse()==0)
      cout << "Bravo" << endl;
    cout << "Moj prvi commit :)" << endl;
   }
    return 0;
}
