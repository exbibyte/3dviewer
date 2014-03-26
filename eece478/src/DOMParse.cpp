#include "DOMParse.h"
#include "DOMNode.h"
#include "DOMMatcher.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

DOMParse::DOMParse()
{
  //initialize DOM types to find
  tDOMMatcher MatchAnimation;
  std::get<TDOMMATCHER_TYPE>(MatchAnimation) = "ANIMATION";
  std::get<TDOMMATCHER_STARTTAG>(MatchAnimation) = "<animation>";
  std::get<TDOMMATCHER_ENDTAG>(MatchAnimation) = "</animation>";

  tDOMMatcher MatchCurve;
  std::get<TDOMMATCHER_TYPE>(MatchCurve) = "CURVEINDEX";
  std::get<TDOMMATCHER_STARTTAG>(MatchCurve) = "<curveindex>";
  std::get<TDOMMATCHER_ENDTAG>(MatchCurve) = "</curveindex>";

  tDOMMatcher MatchModel;
  std::get<TDOMMATCHER_TYPE>(MatchModel) = "MODELINDEX";
  std::get<TDOMMATCHER_STARTTAG>(MatchModel) = "<modelindex>";
  std::get<TDOMMATCHER_ENDTAG>(MatchModel) = "</modelindex>";

  tDOMMatcher MatchTime;
  std::get<TDOMMATCHER_TYPE>(MatchTime) = "TIMEINDEX";
  std::get<TDOMMATCHER_STARTTAG>(MatchTime) = "<timeindex>";
  std::get<TDOMMATCHER_ENDTAG>(MatchTime) = "</timeindex>";

  tDOMMatcher MatchAction;
  std::get<TDOMMATCHER_TYPE>(MatchAction) = "ACTION";
  std::get<TDOMMATCHER_STARTTAG>(MatchAction) = "<action>";
  std::get<TDOMMATCHER_ENDTAG>(MatchAction) = "</action>";

  vDOMMatcher.push_back(MatchAnimation);
  vDOMMatcher.push_back(MatchCurve);
  vDOMMatcher.push_back(MatchModel);
  vDOMMatcher.push_back(MatchTime);
  vDOMMatcher.push_back(MatchAction);
}

DOMNode * DOMParse::GetDOM(string path)
/**
Parses DOM and returns root
*/
{
  DOMNode * root = new DOMNode;

  ifstream ifs;
  stringstream Ss;

  //open model file
  ifs.open(path.c_str(), ifstream::in);
  if(!ifs.is_open())
  {
    cout<<"error opening file: "<<path<<endl;
    return NULL;
  }

  string line;
  int LineNum = 0;

  //remove parsed lines with #comments
  while (getline(ifs, line)) 
  {    
    size_t found = line.find("#");
    if(found == std::string::npos){
      Ss<<line<<" "; // save remaining lines to a single lined buffer and add space to ensure data separation
    }
  }

  line = Ss.str();

  //parse
  this->NestedDOM(root, line);

  //null if empty
  if(root->Children.size() == 0)
  {
    cout<<"empty parse file"<<endl;
    return NULL;
  }

  return root;

}

void DOMParse::NestedDOM(DOMNode * parent, string line)
{
  if(this->vDOMMatcher.empty())
    return;

  int LineNum = 0;
 
  string linetemp = line;

  size_t SmallestFoundStartTag = 999999;
  
  tDOMMatcher CurrentMatcher = this->vDOMMatcher.at(0);

  //try to find the tag that appears first
  for(auto i : this->vDOMMatcher)
  {  
    string TempStartTag = std::get<TDOMMATCHER_STARTTAG>(i);

    size_t TempFoundStartTag = linetemp.find(TempStartTag);

    if(TempFoundStartTag != std::string::npos)  
    {
      if(TempFoundStartTag < SmallestFoundStartTag)
      {
	SmallestFoundStartTag = TempFoundStartTag;
	CurrentMatcher = i;
      }
    }
  }

  if(SmallestFoundStartTag == 999999)
    return;

  if(linetemp == "")
    return;

  string Type = std::get<TDOMMATCHER_TYPE>(CurrentMatcher);    
  string starttag = std::get<TDOMMATCHER_STARTTAG>(CurrentMatcher);
  string endtag = std::get<TDOMMATCHER_ENDTAG>(CurrentMatcher);
    
  size_t FoundStartTag;
  size_t FoundEndTag;

  size_t SavedFoundStartTag = std::string::npos;
  size_t SavedFoundEndTag;

  //save the number of occurances of start tag before 1st end tag
  int occurrencesStart = 0;
  int occurrencesEnd = 0;
  size_t start = 0;
  size_t end = 0;

  //match number of start tags to number of end tags
  while (occurrencesStart != occurrencesEnd || occurrencesEnd == 0) 
  {
    //find end tag first
    FoundEndTag = linetemp.find(endtag, end);    
    if(FoundEndTag != std::string::npos)
    {
      end = FoundEndTag + endtag.length();
      occurrencesEnd++;
      SavedFoundEndTag = FoundEndTag;
    }

    occurrencesStart = 0;
    start = 0;

    //find start tag
    do
    {
      FoundStartTag = linetemp.substr(0, SavedFoundEndTag).find(starttag,start); 
      if(FoundStartTag != std::string::npos)
      {
	occurrencesStart++;
	start = FoundStartTag + starttag.length();

	// cout<<start<<","<<end<<endl;
	// cout<<"occurences: "<<occurrencesStart<<", "<<occurrencesEnd<<endl;

      }
    }while(FoundStartTag != std::string::npos);
  }

  //get 1st start tag
  SavedFoundStartTag = linetemp.substr(0, SavedFoundEndTag).find(starttag); 

  //find <tags> and </tags> defined in DOMMatcher
  if(SavedFoundStartTag != std::string::npos)
  {
    if(SavedFoundEndTag != std::string::npos)
    {
      //when found begin and end tags, extract string
      string SubString = linetemp.substr(SavedFoundStartTag + starttag.length(),SavedFoundEndTag-(SavedFoundStartTag + starttag.length()));

      //creates a DOM object and attach to parent node
      DOMNode * NewNode = new DOMNode;
      parent->AddChild(NewNode);
      NewNode->Data = SubString;
      NewNode->Type = Type;
      
      //search for nested DOM
      this->NestedDOM(NewNode, SubString);
      
      //continue search on remaining string before it
      string unsearchedbefore = linetemp.substr(0, SavedFoundStartTag);
      this->NestedDOM(parent, unsearchedbefore);
      
      //continue search on remaining string after it
      string unsearchedafter = linetemp.substr(SavedFoundEndTag + endtag.length(), std::string::npos);
      this->NestedDOM(parent, unsearchedafter);
    } 
  }
  return;
}
