#include <iostream>
#include "windows.h"
 
#pragma comment(lib, "Ws2_32.lib");
 
using namespace std;
 
int main() {
 
    int port = 666;
    char * ip = "127.0.0.1";
 
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
 
}
