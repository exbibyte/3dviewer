#include "TrajectoryParse.h"
#include "CurveData.h"
#include "ModelData.h"

#include <vector>
#include <iostream>

TrajectoryParse::TrajectoryParse()
{

}

TrajectoryParse::~TrajectoryParse()
{

}

vector<CurvePath *> TrajectoryParse::GetTrajectories(string path)
/**
Parses and returns a camera path
*/
{
  vector<CurvePath *> vpCurvePath;

  ifstream ifs;
  stringstream Ss;

  //open model file
  ifs.open(path.c_str(), ifstream::in);
  if(!ifs.is_open())
  {
    cout<<"error opening file: "<<path<<endl;
    return vpCurvePath;
  }

  //creates containers for basic model data
  CurveData * cCurveData = new CurveData();

  //prepares to extract data using loop
  this->vModelData.push_back(cCurveData);

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

  this->bEmpty = true;

  //find <tags> and </tags> defined in ModelData and extract string to ModelData
  line.clear();
  while (getline(Ss, line)) 
  { 
    for(auto i : vModelData)
    {
      bool foundall = false;
      string linetemp = line;
      do{
	
	size_t FoundStartTag = linetemp.find(i->mBeginTag);
	if(FoundStartTag != std::string::npos)
	{
	  size_t FoundEndTag = linetemp.find(i->mEndTag);
	  if(FoundEndTag != std::string::npos)
	  {
	    //when found begin and end tags, extract string
	    string SubString = linetemp.substr(FoundStartTag + i->mBeginTag.length(),FoundEndTag-(FoundStartTag + i->mBeginTag.length()));
	  
	    //continue search on rest of string
	    linetemp = linetemp.substr(FoundEndTag + i->mEndTag.length(), std::string::npos);

	    i->SetData(SubString); // call derived ModelData classes to format and save data

	    //creates a curve and initialize path
	    CurvePath * NewCurvePath = new CurvePath();
	    this->InitializeCurve(NewCurvePath, cCurveData);
	    i->ClearData();

	    vpCurvePath.push_back(NewCurvePath);  

	    NewCurvePath = NULL;

	    this->bEmpty = false;
	  }
	}
	else
	{
	  foundall = true;
	}
      }while(foundall == false);
    }
  }

  //if can't find tags, return
  if(this->bEmpty)
  {
    cout<<"empty curve file"<<endl;
    return vpCurvePath;
  }

  //null pointers
  cCurveData = NULL;
  vModelData.clear();

  return vpCurvePath;
}

void TrajectoryParse::InitializeCurve(CurvePath * pCurve, CurveData * pCurveData)
{
  for(auto i : pCurveData->vCurveControl)
  {
    int steps = std::get<TCURVECONTROL_STEP>(i);
    
    float ctrlpoint1[3];
    float ctrlpoint2[3];
    float ctrlpoint3[3];
    float ctrlpoint4[3];
    
    ctrlpoint1[0] = std::get<TCURVECONTROL_PT1_X>(i);
    ctrlpoint1[1] = std::get<TCURVECONTROL_PT1_Y>(i);
    ctrlpoint1[2] = std::get<TCURVECONTROL_PT1_Z>(i);

    ctrlpoint2[0] = std::get<TCURVECONTROL_PT2_X>(i);
    ctrlpoint2[1] = std::get<TCURVECONTROL_PT2_Y>(i);
    ctrlpoint2[2] = std::get<TCURVECONTROL_PT2_Z>(i);

    ctrlpoint3[0] = std::get<TCURVECONTROL_PT3_X>(i);
    ctrlpoint3[1] = std::get<TCURVECONTROL_PT3_Y>(i);
    ctrlpoint3[2] = std::get<TCURVECONTROL_PT3_Z>(i);

    ctrlpoint4[0] = std::get<TCURVECONTROL_PT4_X>(i);
    ctrlpoint4[1] = std::get<TCURVECONTROL_PT4_Y>(i);
    ctrlpoint4[2] = std::get<TCURVECONTROL_PT4_Z>(i);

    pCurve->AddCurve(steps, ctrlpoint1, ctrlpoint2, ctrlpoint3, ctrlpoint4);
  }
}
