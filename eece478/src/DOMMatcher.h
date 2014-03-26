#ifndef DOMMATCHER_H
#define DOMMATCHER_H

#include <tuple>

#define TDOMMATCHER_TYPE 0
#define TDOMMATCHER_STARTTAG 1
#define TDOMMATCHER_ENDTAG 2

using namespace std;

typedef tuple<string,string,string> tDOMMatcher;

#endif
