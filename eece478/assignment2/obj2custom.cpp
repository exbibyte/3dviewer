/**
Bill Liu
#63461081

Info:
Convert .obj file to custom file format
.obj file need to be in vertex and texture coordinate format only (no vertex normals)
This generates custom file format having vertices, face normals, triangles, texture coordinates, and a reference to 1 texture image (texture.ppm)

 */

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

typedef tuple<int,int,int, int, int, float,float,float,float,float,float> tTriangleData;

int main(int argc, char** argv)
{
  fstream input;
  fstream output;

  if(argc<4)
  {
    cout<<"need: <input .obj file> <output file name> <object name>"<<endl;
    return 0;
  }

  input.open (argv[1], std::fstream::in);
  output.open (argv[2], std::fstream::out | std::fstream::trunc);
  
  string current;
  stringstream ss;

  vector<vector<float> > vTexturecoord;
  vector<vector<float> > vVertex;
  vector<vector<float> > vNormal;
  vector<tTriangleData> vTriangle;

  vector<string> vTextureName;
  int objectCount = 0;
  int triangleCount = 0;

  while (getline(input, current)) 
  {    
    ss.flush();

    //ignore comments
    size_t found = current.find("#");
    if(found != std::string::npos)
    {
      continue;
    }

    //ignore object name
    found = current.find("g ");
    if(found != std::string::npos)
    {
      ss << current.substr(found + 2, string::npos)<<endl; 
      string name;
      ss >> name;
      vTextureName.push_back(name);
      objectCount++;
      continue;
    }

    //vertices
    found = current.find("v ");
    if(found != std::string::npos)
    {
      ss<<current.substr(found + 2, string::npos)<<endl; 
      //save vertex to vector
      vector<float> vertex;
      float temp;      
      for(int i = 0; i < 3; i ++)
      {
	ss >> temp;
	vertex.push_back(temp);
      }
      vVertex.push_back(vertex);

      continue;
    }

    //texture coordinates
    found = current.find("vt ");
    if(found != std::string::npos)
    {
      //save texture coordinates to vector
      vector<float> texture;
      ss<<current.substr(found + 3, string::npos)<<endl;
      float texturedata;
      for(int i = 0; i < 3; i ++)
      {
	ss >> texturedata;	
	texture.push_back(texturedata);
      }
      vTexturecoord.push_back(texture);

      continue;
    }

    //triangles
    found = current.find("f ");
    if(found != std::string::npos)
    {     
      string triangle;      
      triangle = current.substr(found + 2, string::npos);

      //format '/' delimited triangle data: vertex/texturecoord
      int vertIndex[3];
      int textIndex[3];
      sscanf(triangle.c_str(),"%d/%d %d/%d %d/%d",&vertIndex[0],&textIndex[0],&vertIndex[1],&textIndex[1],&vertIndex[2],&textIndex[2]);

      //write vertice indexes to output file
      for(int i = 0; i < 3; i++)
      {
	//convert index to 0 based
	vertIndex[i]--;
	textIndex[i]--;
      }

      triangleCount++;

      //compute the triangle normal from vertices
      float vec1[3];
      float vec2[3];

      vector<float> temp1 = vVertex.at(vertIndex[0]);
      vector<float> temp2 = vVertex.at(vertIndex[1]);
      vector<float> temp3 = vVertex.at(vertIndex[2]);
      for(int i = 0; i < 3; i++)
      {
      	vec1[i] = temp2.at(i) - temp1.at(i);
      	vec2[i] = temp3.at(i) - temp1.at(i);
      }

      //cross product
      float norm[3];
      norm[0] = vec1[1]*vec2[2] - vec1[2]*vec2[1];
      norm[1] = vec1[2]*vec2[0] - vec1[0]*vec2[2];
      norm[2] = vec1[0]*vec2[1] - vec1[1]*vec2[0];
      
      //normalize normals and save to vector
      vector<float> normalData;
      float mag = sqrt(pow(norm[0],2) + pow(norm[1],2) + pow(norm[2],2));
      for(int i = 0; i < 3; i++)
      {
      	norm[i] = norm[i]/mag;
      	normalData.push_back(norm[i]);
	if(isnan(norm[i]))
	  cout<<"Warning: NaN in object: "<<objectCount<<" triangle: "<<triangleCount<<" vec1: "<<vec1[i]<<" vec2: "<<vec2[i]<<endl;
      }
      vNormal.push_back(normalData);

      //save triangle to vector
      //vertice indices
      tTriangleData data;
      std::get<0>(data) = vertIndex[0];
      std::get<1>(data) = vertIndex[1];
      std::get<2>(data) = vertIndex[2];
      //normal index (same as triangle index)
      std::get<3>(data) = triangleCount-1;
      //texture index (same as object index)
      std::get<4>(data) = objectCount-1;
      //texture coodinates
      std::get<5>(data) = vTexturecoord.at(textIndex[0]).at(0);
      std::get<6>(data) = vTexturecoord.at(textIndex[0]).at(1);
      std::get<7>(data) = vTexturecoord.at(textIndex[1]).at(0);
      std::get<8>(data) = vTexturecoord.at(textIndex[1]).at(1);
      std::get<9>(data) = vTexturecoord.at(textIndex[2]).at(0);
      std::get<10>(data) = vTexturecoord.at(textIndex[2]).at(1);
      vTriangle.push_back(data);
      continue;
    }
  }

  //write building name and texture file
  output<<"<name>"<<argv[3]<<"</name>"<<endl;
  
  //write texture names
  output<<"<textures>"<<endl;
  for(auto i : vTextureName)
  {
    output<< i <<".ppm"<<endl;
  }
  output<<"</textures>"<<endl;

  //write vertices
  output<<"<vertices>"<<endl;
  for(auto i : vVertex)
  {
    for(auto j : i)  
    {
      output<< j << " ";
    }
    output<<endl;
  }
  output<<"</vertices>"<<endl;  

  //write computed face normals
  output<<"<normals>"<<endl;
  for(auto i : vNormal)
  {
    for(auto j : i)
    {
      output<< j <<" ";
    }
    output<<endl;
  }
  output<<"</normals>"<<endl;

  //write triangles
  output<<"<triangles>"<<endl;
  for(auto i : vTriangle)
  {   
    output<< std::get<0>(i) <<" ";
    output<< std::get<1>(i) <<" ";
    output<< std::get<2>(i) <<" ";
    output<< std::get<3>(i) <<" ";
    output<< std::get<4>(i) <<" ";
    output<< std::get<5>(i) <<" ";
    output<< std::get<6>(i) <<" ";
    output<< std::get<7>(i) <<" ";
    output<< std::get<8>(i) <<" ";
    output<< std::get<9>(i) <<" ";
    output<< std::get<10>(i) <<" ";
    output<<endl;
  }
  output<<"</triangles>"<<endl;

  input.close();
  output.close();

  return 0;
}
