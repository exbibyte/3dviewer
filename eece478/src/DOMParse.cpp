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
  std::get<TDOMMATCHER_TYPE>(MatchAnimation) = "animation";
  std::get<TDOMMATCHER_STARTTAG>(MatchAnimation) = "<animation>";
  std::get<TDOMMATCHER_ENDTAG>(MatchAnimation) = "</animation>";

  tDOMMatcher MatchTime;
  std::get<TDOMMATCHER_TYPE>(MatchTime) = "time";
  std::get<TDOMMATCHER_STARTTAG>(MatchTime) = "<time>";
  std::get<TDOMMATCHER_ENDTAG>(MatchTime) = "</time>";

  tDOMMatcher MatchAction;
  std::get<TDOMMATCHER_TYPE>(MatchAction) = "action";
  std::get<TDOMMATCHER_STARTTAG>(MatchAction) = "<action>";
  std::get<TDOMMATCHER_ENDTAG>(MatchAction) = "</action>";

  tDOMMatcher MatchName;
  std::get<TDOMMATCHER_TYPE>(MatchName) = "name";
  std::get<TDOMMATCHER_STARTTAG>(MatchName) = "<name>";
  std::get<TDOMMATCHER_ENDTAG>(MatchName) = "</name>";

  tDOMMatcher MatchCurve;
  std::get<TDOMMATCHER_TYPE>(MatchCurve) = "curve";
  std::get<TDOMMATCHER_STARTTAG>(MatchCurve) = "<curve>";
  std::get<TDOMMATCHER_ENDTAG>(MatchCurve) = "</curve>";

  tDOMMatcher MatchData;
  std::get<TDOMMATCHER_TYPE>(MatchData) = "data";
  std::get<TDOMMATCHER_STARTTAG>(MatchData) = "<data>";
  std::get<TDOMMATCHER_ENDTAG>(MatchData) = "</data>";

  tDOMMatcher MatchTranslation;
  std::get<TDOMMATCHER_TYPE>(MatchTranslation) = "translation";
  std::get<TDOMMATCHER_STARTTAG>(MatchTranslation) = "<translation>";
  std::get<TDOMMATCHER_ENDTAG>(MatchTranslation) = "</translation>";

  tDOMMatcher MatchScale;
  std::get<TDOMMATCHER_TYPE>(MatchScale) = "scale";
  std::get<TDOMMATCHER_STARTTAG>(MatchScale) = "<scale>";
  std::get<TDOMMATCHER_ENDTAG>(MatchScale) = "</scale>";

  tDOMMatcher MatchRotation;
  std::get<TDOMMATCHER_TYPE>(MatchRotation) = "rotation";
  std::get<TDOMMATCHER_STARTTAG>(MatchRotation) = "<rotation>";
  std::get<TDOMMATCHER_ENDTAG>(MatchRotation) = "</rotation>";

  tDOMMatcher MatchSubject;
  std::get<TDOMMATCHER_TYPE>(MatchSubject) = "subject";
  std::get<TDOMMATCHER_STARTTAG>(MatchSubject) = "<subject>";
  std::get<TDOMMATCHER_ENDTAG>(MatchSubject) = "</subject>";

  tDOMMatcher MatchExtra;
  std::get<TDOMMATCHER_TYPE>(MatchExtra) = "extra";
  std::get<TDOMMATCHER_STARTTAG>(MatchExtra) = "<extra>";
  std::get<TDOMMATCHER_ENDTAG>(MatchExtra) = "</extra>";

  tDOMMatcher MatchControlpoint;
  std::get<TDOMMATCHER_TYPE>(MatchControlpoint) = "controlpoint";
  std::get<TDOMMATCHER_STARTTAG>(MatchControlpoint) = "<controlpoint>";
  std::get<TDOMMATCHER_ENDTAG>(MatchControlpoint) = "</controlpoint>";

  tDOMMatcher MatchLight_Ambient;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Ambient) = "light_ambient";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Ambient) = "<light_ambient>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Ambient) = "</light_ambient>";

  tDOMMatcher MatchLight_Specular;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Specular) = "light_specular";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Specular) = "<light_specular>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Specular) = "</light_specular>";

  tDOMMatcher MatchLight_Diffuse;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Diffuse) = "light_diffuse";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Diffuse) = "<light_diffuse>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Diffuse) = "</light_diffuse>";

  tDOMMatcher MatchLight_Position;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Position) = "light_position";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Position) = "<light_position>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Position) = "</light_position>";

  tDOMMatcher MatchLight_Direction;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Direction) = "light_direction";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Direction) = "<light_direction>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Direction) = "</light_direction>";

  tDOMMatcher MatchLight_Exponent;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Exponent) = "light_exponent";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Exponent) = "<light_exponent>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Exponent) = "</light_exponent>";

  tDOMMatcher MatchLight_Cutoff;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Cutoff) = "light_cutoff";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Cutoff) = "<light_cutoff>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Cutoff) = "</light_cutoff>";

  tDOMMatcher MatchLighting;
  std::get<TDOMMATCHER_TYPE>(MatchLighting) = "lighting";
  std::get<TDOMMATCHER_STARTTAG>(MatchLighting) = "<lighting>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLighting) = "</lighting>";

  tDOMMatcher MatchLight_Turnon;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Turnon) = "light_turnon";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Turnon) = "<light_turnon>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Turnon) = "</light_turnon>";

  tDOMMatcher MatchLight_Turnoff;
  std::get<TDOMMATCHER_TYPE>(MatchLight_Turnoff) = "light_turnoff";
  std::get<TDOMMATCHER_STARTTAG>(MatchLight_Turnoff) = "<light_turnoff>";
  std::get<TDOMMATCHER_ENDTAG>(MatchLight_Turnoff) = "</light_turnoff>";

  vDOMMatcher.push_back(MatchAnimation);
  vDOMMatcher.push_back(MatchTime);
  vDOMMatcher.push_back(MatchAction);
  vDOMMatcher.push_back(MatchName);
  vDOMMatcher.push_back(MatchCurve);
  vDOMMatcher.push_back(MatchData);
  vDOMMatcher.push_back(MatchTranslation);
  vDOMMatcher.push_back(MatchScale);
  vDOMMatcher.push_back(MatchRotation);
  vDOMMatcher.push_back(MatchSubject);
  vDOMMatcher.push_back(MatchExtra);
  vDOMMatcher.push_back(MatchControlpoint);
  vDOMMatcher.push_back(MatchLight_Ambient);
  vDOMMatcher.push_back(MatchLight_Specular);
  vDOMMatcher.push_back(MatchLight_Diffuse);
  vDOMMatcher.push_back(MatchLight_Position);
  vDOMMatcher.push_back(MatchLight_Direction);
  vDOMMatcher.push_back(MatchLight_Exponent);
  vDOMMatcher.push_back(MatchLight_Cutoff);
  vDOMMatcher.push_back(MatchLighting);
  vDOMMatcher.push_back(MatchLight_Turnon);
  vDOMMatcher.push_back(MatchLight_Turnoff);
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

  int occurrencesStartOld = occurrencesStart;
  int occurrencesEndOld = occurrencesEnd;

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
      }
    }while(FoundStartTag != std::string::npos);


    //see if DOM is invalid and return
    if(occurrencesEndOld == occurrencesEnd && occurrencesStartOld == occurrencesStart)
    {
      return;
    }

    occurrencesStartOld = occurrencesStart;
    occurrencesEndOld = occurrencesEnd;
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
