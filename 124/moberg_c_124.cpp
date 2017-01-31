/**
* Calculates the average of all numbers input.
* @author Cameron Moberg
* @version 18 January 2017
*/

typedef unsigned int unit;
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   uint total = 0;
   uint score_counter = 0;

   while ( !cin.eof() )
   {
      cout << "Enter score (ctrl + d to quit): ";
      uint score;
      cin >> score;
      if( !cin.eof() )
      {
         total += score;
         score_counter++;
      }
   }

   if ( score_counter == 0 )
   {
      cout << endl << "No scores were entered" << endl;
   }
   else
   {
      double average = static_cast < double > ( total ) / score_counter;
      cout << endl << "Average: " << setprecision( 2 ) <<
         setiosflags( ios::fixed | ios::showpoint ) << average << endl;
   }

   return 0;
}
