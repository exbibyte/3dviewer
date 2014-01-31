#ifndef QUERY_MATCHER_H
#define QUERY_MATCHER_H

#include <algorithm>

template<class A, class B>
class QueryMatcher
{
 private:
  bool (*fCompareB)(void*, void*);
  int (*fCompareAB)(void*, void*);
 public:
  QueryMatcher();
  void GetMatch(A*& Find, B*& Search, B*& Match, B*& NoMatch);
  void SetCompare(bool (*function)(void*, void*), int (*function)(void*, void*));
};

template<class A, class B>
QueryMatcher<A, B>::QueryMatcher()
{
  this->fCompare = NULL;
}

template<class A, class B>
void QueryMatcher<A, B>::GetMatch(A*& Find, B*& Search, B*& Match, B*& NoMatch)
/**
returns elements of type B which matches the type A element provided
items of type B that do not match are also returned
*/
{
  //sort items of type B by some order
  std::sort(Search->begin(), Search->end(), fCompare); 

  for(auto i : Search)
  {
    if(CompareAB(Find,Search) == EQUAL)
    {
      Match.add(i);
    }
    else
    {
      NoMatch.add(i);
    }
  }
}

template<class A, class B>
  void QueryMatcher<A, B>::SetCompare(bool (*fCompB)(void*, void*), int (*fCompAB)(void*, void*))
/**
Set the comparison functions prior to performing a match
*/
{
  this->fCompareB = fCompB;
  this->fCompareAB = fCompAB;
}

#endif
