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

using namespace std;

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

  int stage = 0;

  vector<vector<float> > vTexturecoord;
  vector<vector<float> > vVertex;
  vector<vector<float> > vNormal;

  //write building name and texture file

  output<<"<name>"<<argv[3]<<"</name>"<<endl;
  output<<"<textures>"<<argv[3]<<".ppm</textures>"<<endl;

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
      continue;
    }

    //vertices
    found = current.find("v ");
    if(found != std::string::npos)
    {
      if(stage == 0)
      {
	output<<"<vertices>"<<endl;
      }
      
      stage = 1;

      ss<<current.substr(found + 2, string::npos)<<endl;
      
      //write vertex to output file and add to vector
      vector<float> vertex;
      for(int i = 0; i < 3; i ++)
      {
	float temp;
	ss >> temp;
	vertex.push_back(temp);
	output<<temp<<" ";
      }
      output<<endl;
      vVertex.push_back(vertex);

      continue;
    }

    //texture coordinates
    found = current.find("vt ");
    if(found != std::string::npos)
    {
      if(stage == 1)
      {
	output<<"</vertices>"<<endl;
      }
      stage = 2;

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

    found = current.find("f ");
    if(found != std::string::npos)
    {
      if(stage == 2)
      {
	output<<"<triangles>"<<endl;
      }
      stage = 3;

      // cout<<"found f"<<endl;
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
	vertIndex[i] = vertIndex[i] - 1;
    	output<<vertIndex[i]<<" ";
      }

      //write normal index per triangle face
      output<<triangleCount<<" ";
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
      
      //normalize normals
      vector<float> normalData;
      float mag = sqrt(pow(norm[0],2) + pow(norm[1],2) + pow(norm[2],2));
      for(int i = 0; i < 3; i++)
      {
      	norm[i] = norm[i]/mag;
      	//save vertex to vector
      	normalData.push_back(norm[i]);
      }
      vNormal.push_back(normalData);

      //write texture ppm id = 0 since only 1 texture file
      output<<0<<" ";

      //write texture coordinate indexes
      for(int i = 0; i < 3; i++)
      {
	//convert to 0 based index
	textIndex[i]--;
	output<<vTexturecoord.at(textIndex[i]).at(0)<<" ";
	output<<vTexturecoord.at(textIndex[i]).at(1)<<" ";
      }
      
      output<<endl;

      continue;
    }
  }

  output<<"</triangles>"<<endl;

  //write computed face normals
  output<<"<normals>"<<endl;
  for(auto i : vNormal)
  {
    for(auto j : i)
    {
      output << j <<" ";
    }
    output<<endl;
  }
  output<<"</normals>"<<endl;
  
  input.close();
  output.close();

  return 0;
}
