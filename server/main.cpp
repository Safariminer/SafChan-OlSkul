#include <iostream>
#include "windows.h"
 
#pragma comment(lib, "Ws2_32.lib");
 
using namespace std;
 
int err_connection = 1;
 
int main(){
 
 
    SOCKET mysocket, server;
    WORD p;
    sockaddr_in sock_addr, addr;
   
    p = MAKEWORD(2,2);
    WSAStartup(p,&data);                  
 
    mysocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   
    /*if (mysocket == INVALID_SOCKET){
                return 0;
                   }*/
     
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons((u_short)666);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);          
 
    //this is required, check if connected!
    if (bind(mysocket,(SOCKADDR*)(&sock_addr),sizeof(sock_addr))==0){
 
                         listen(mysocket,10);
                         SOCKET server;
                         int len = sizeof(addr);
                         server = accept(mysocket,(struct sockaddr *)&addr,&len);
                         
 
                         //now you can perform read and write:
                         
                         //the best is to introduce a while loop here, but for minimalism i'll avoid it
                         //and to check any time in the loop if there are some errors... btw
                       
                         char packet[1024];
                         ZeroMemory(&packet, strlen(packet));
                         
                         int len_rec = recv(server, packet, strlen(packet), 0);
                         
                         //now you can check if it is a specified command
                         cout<<"Message received: "<<endl<<packet<<endl<<"Size: "<<len_rec<<endl<<endl;
                         
                         char answer[70];
                         ZeroMemory(&answer, strlen(answer));
       
                         strcpy(answer, "Message received");
                         
                         int total_sent = send(server, answer, strlen(answer), 0);
                         
                         cout<<Message sent, bytes totally processed: "<<total_sent<<endl<<endl;
 
                         //let's turn down sockets
                         closesocket(server);
                         closesocket(mysocket);
                         
                         }
 
 
      }
 
 
      cout<<"Error binding"<<endl;
      WSACleanup();
      system.get();
      return 0;
}
