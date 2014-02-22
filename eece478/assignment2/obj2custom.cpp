#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  fstream input;
  fstream output;
  
  input.open (argv[1], std::fstream::in);
  output.open (argv[2], std::fstream::out | std::fstream::trunc);
  
  string current;
  stringstream ss;

  while (getline(input, current)) 
  {    
    size_t found = current.find("#");
    if(found == std::string::npos)
    {
    }

    found = current.find("v ");
    if(found != std::string::npos)
    {
      cout<<"found v"<<endl;
      output<<current.substr(found + 2, string::npos)<<endl;
    }

    found = current.find("vn ");
    if(found != std::string::npos)
    {
      cout<<"found vn"<<endl;      
      output<<current.substr(found + 3, string::npos)<<endl;
    }

    found = current.find("vt ");
    if(found != std::string::npos)
    {
      cout<<"found vt"<<endl;
      output<<current.substr(found + 3, string::npos)<<endl;
    }

    found = current.find("f ");
    if(found != std::string::npos)
    {
      cout<<"found f"<<endl;
      output<<current.substr(found + 2, string::npos)<<endl;
    }

  }

  input.close();
  output.close();

  return 0;
}
