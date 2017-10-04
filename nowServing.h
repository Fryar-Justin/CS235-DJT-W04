/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Devin Cenatiempo
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

//#include "deque.h"     // for DEQUE
#include <string>

using namespace std;

// the interactive nowServing program
void nowServing();

class Request
{
private:
   string course;
   string name;
   int minutes;
   bool emergency;
public:
   //constructors
   Request() {course = ""; name = ""; minutes = 0; emergency = 0; }
   Request( string course, string name, int minutes, bool emergency )
   { this->course = course; this->name = name; this->minutes = minutes; this->emergency = emergency; }
   //getters
   string getCourse() { return course; }
   string getName() { return name; }
   int getMinute() { return minutes; }
   bool isEmergency() { return emergency; }
   //setters
   void subtractMinute() { minutes--; }
};


#endif // NOW_SERVING_H

