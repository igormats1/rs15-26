#include <iostream>

#include "lexer.h"
#include "parser.h"

using namespace std;

/*prvi commit - michael*/

int main(int argc, char *argv[])
{
   while(true)
   {
    if (yyparse()==0)
      cout << "Bravo" << endl;
   }
    return 0;
}
