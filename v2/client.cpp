#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include "util.h"
int main(){
  // 创建socket, 填写服务端地址,连接服务端
  int socketFd = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in serverAddr;
  bzero(&serverAddr,sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddr.sin_port = htons(8887);
  connect(socketFd,(sockaddr*)& serverAddr,sizeof(serverAddr));
  while (true)
  {
    char buff[1024];
    std::cin >> buff;
    ssize_t writeBytes = write(socketFd,buff,sizeof(buff));
    if(writeBytes == -1){
      printError(true,"write errno");
      break;
    }
    bzero(&buff,sizeof(buff));
    ssize_t readBytes = read(socketFd,buff,sizeof(buff));
    if(readBytes > 0){
      std::cout << "数据来自服务端:" << std::endl;
      std::cout << buff << std::endl;
    }else if(readBytes == 0){
      std::cout << "服务端断开连接" << std::endl;
      break;
    }else if(readBytes == -1){
      close(socketFd);
      printError(true,"socket read errno");
    }
  }
  

  return 0;
}