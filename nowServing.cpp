/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;
using namespace custom;

void display(Request current){
   //Currently serving Sam for class CS124. Time left: 1
   //Emergency for Steve for class CS124. Time left: 2
   if (current.isEmergency())
      cout << "\tEmergency for ";
   else
      cout << "\tCurrently serving ";
   cout << current.getName() << " for class "
   << current.getCourse() << ". Time left: "
   << current.getMinute() << endl;
}

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   string course;
   string name;
   int minutes;
   string instruction;
   int time = 0;
   
   deque <Request> labLine(4);
   Request current;
   
   try
   {
      do
      {
         cout << "<" << time << "> " ;
         cin  >> instruction;
         if (instruction == "none")
         {
            // no input, 1 minute passes
         }
         else if (instruction == "finished")
         {
            break;
         }
         else if (instruction == "!!")
         {
            //need to add validation/error handling
            cin >> course;
            cin >> name;
            cin >> minutes;
            // add new request to the back of the deque
            labLine.push_front(Request(course, name, minutes, 1));
         }
         else
         {
            cin >> name;
            cin >> minutes;
            // add new request to the back of the deque
            labLine.push_back(Request(instruction, name, minutes, 0));
         }
         if ( current.getMinute() == 0 && !labLine.empty() )
         {
            current = labLine.front();
            labLine.pop_front();
         }
         if (current.getMinute())
         {
            display(current);
            current.subtractMinute();
         }
         time++;
      }
      while (instruction != "finished");
   }
   catch (const char * error)
   {
      cout << error << endl;
   }
   
   // end
   cout << "End of simulation\n";
}


