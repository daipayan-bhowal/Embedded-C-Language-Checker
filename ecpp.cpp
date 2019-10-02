/****** Embedded C++ Guidelines Checker written in C++11 *******/
/***Follow Language Specification TR.18015 ****/
/******* Copyright reserved by Daipayan  *************/

#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream>
//#if __cplusplus > 199711L
    #include <chrono>
//#endif
using namespace std;
#define DEBUG 0
/*namespace input_data
{ 
    vector<string> line_str;
    vector<int> line_no;
}*/
void inline fetch_str_fromfile_singleline(string &filename,string &content)
{
    ifstream fptr(filename.c_str(),std::ifstream::in);
    string fetch_str;
    while(fptr >> fetch_str)
    {
        content += fetch_str;
        content += " ";
    }

    return;
}
inline void is_embedded_cpp(string file)
{
//#if __cplusplus > 199711L
    using namespace std::chrono;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
//#endif
    string tok_str;
    string str_filecontent; 
    fetch_str_fromfile_singleline(file,str_filecontent);
    stringstream strstream2(str_filecontent);
    int sz = 0;
    std::size_t size;
    while(getline(strstream2, tok_str, ' ') || getline(strstream2, tok_str, '\n'))
    {
       sz += tok_str.length();
#if DEBUG
       cout << tok_str << endl;
 #endif
       if(tok_str == "template")
       {
           cout <<__LINE__ << ":error: No template feature supported in Embedded C++" << endl;
           exit(0);
       } 
       else if(tok_str == "using")
       {
           cout <<__LINE__ << ":error: No 'using' keyword exist in Embedded C++" << endl;
           exit(0);
       } 
       else if(tok_str == "namespace")
       {
           cout <<__LINE__ << ":error: No namespace exist in Embedded C++" << endl;
           exit(0);
       }
       else if((size=tok_str.find("std::")) > 0 )
       {
           if(size != std::string::npos)
           cout <<__LINE__ << ":error: No namespace std exist all are in global scope in Embedded C++" << endl;
       }
       else if(tok_str.compare("try") || tok_str.compare("throw") || ((size=tok_str.find("catch")) > 0 && size != std::string::npos) )
       {
           cout <<__LINE__ << ":error: No exceptional handling exist in Embedded C++" << endl;
       }
       else if(tok_str.compare("typename") || tok_str.compare("<typename"))
       {
           cout <<__LINE__ << ":error: Templates not supported so no 'typename' in Embedded C++" << endl;
       }
       else if((size=tok_str.find("typeid")) || (size=tok_str.find("const_cast")) || (size=tok_str.find("reinterpret_cast")) || (size=tok_str.find("dynamic_cast")) || (size=tok_str.find("static_cast")) )
       {
          if(size != std::string::npos)
           cout <<__LINE__ << ":error: No RTTI  supported in Embedded C++" << endl;
       }
       else if(tok_str.compare("export"))
       {
           cout <<__LINE__ << ":error: export not supported in Embedded C++" << endl;
       }
       else if(tok_str.compare("mutable"))
       {
           cout <<__LINE__ << ":error: mutable not supported in Embedded C++" << endl;
       }
       else if(tok_str.compare("wchar_t"))
       {
           cout <<__LINE__ << ":error: mutable not supported in Embedded C++" << endl;
       }
    }
//#if __cplusplus > 199711L
    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed Time:"<< elapsed_seconds.count();
//#endif
}   
int main()
{
  is_embedded_cpp("emb.cpp");

}
