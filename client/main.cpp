// based on http://www.rohitab.com/discuss/topic/39554-minimalistic-c-chat-program/
#include <iostream>
#include <fstream>
#include <algorithm>
#include "windows.h"
 
#pragma comment(lib, "Ws2_32.lib");
 
using namespace std;
 
int main() {
    // std::ifstream is RAII, i.e. no need to call close
 int port;
    char * ip;
    std::ifstream cFile ("info.cfg");
    if (cFile.is_open())
    {
        std::string line;
        while(getline(cFile, line)){
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                                 line.end());
            if(line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            std::cout << name << " " << value << '\n';
         if(name == "ip"){
          ip = value;
         }
         else if(name == "port"){
          port = value;
         }
         
         if(ip == ""){
          std::cout << "IP is missing from config!" << std::endl;
          goto exitProgram;
         }
         if(port == 0){std::cout << "Port is missing from config! Continuing anyways" << std::endl;}
         
        }
     
        
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
    }
    
 
    WSADATA data;
    SOCKET mysocket;
    WORD p;
    p = MAKEWORD(2,2);
    WSAStartup(p,&data);
   
 
   
   
    SOCKADDR_IN target; //Socket address information
 
    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (port); //Port to connect on
    target.sin_addr.s_addr = inet_addr (ip); //Target IP
 
    mysocket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
 
    //required
    if (connect(mysocket, (sockaddr*)&target, sizeof(target)) != SOCKET_ERROR){
 
             cout<<"Connected!"<<endl;
 
             char * hello = "Hello server!"<<endl;
 
             int len = send(mysocket, hello, strlen(hello), 0);
         
             cout<<"Message sent, byte totally processed: "<<len<<endl<<endl;
 
             char answer[60];
             ZeroMemory(&answer, strlen(answer));
 
             int total_rec = recv(mysocket, answer, strlen(answer), 0);
 
             cout<<"Message received:"<<answer<<endl<<"Size: "<<total_rec<<endl;
 
             closesocket(mysocket);
     
     }else{
               cout<<"Error connecting..."<<endl;
     }
 
      WSACleanup();
 exitProgram:
 return 0;
}
