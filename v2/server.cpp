#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<string>
void printError(bool condition,const std::string& errnoMessage);
int main(){
  int sockFd = socket(AF_INET,SOCK_STREAM,0);
  printError(sockFd == -1,"socket创建失败");
  struct sockaddr_in serverAddr;
  bzero(&serverAddr,sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serverAddr.sin_port = htons(8887);
  
  int flag = bind(sockFd,(sockaddr*)&serverAddr,sizeof(serverAddr));
  printError(flag == -1,"socket bind error");
  flag = listen(sockFd,SOMAXCONN);
  printError(flag == -1,"socket listen errno");

  struct sockaddr_in clientAddr;
  bzero(&clientAddr,sizeof(clientAddr));
  socklen_t clientLength = sizeof(clientAddr);
  int sockClientFd = accept(sockFd,(sockaddr*)& clientAddr,&clientLength);
  printError(sockClientFd == -1,"accept client errno");
  std::cout << "客户端socket文件符：" << sockClientFd;
  std::cout << "客户端ip：" << inet_ntoa(clientAddr.sin_addr);
  std::cout << "客户端端口：" << ntohs(clientAddr.sin_port);
  std::cout << std::endl;

  while(true){
    char buff[1024];
    bzero(&buff,sizeof(buff));
    
    ssize_t read_bytes = read(sockClientFd,buff,sizeof(buff));
    if(read_bytes > 0){
      std::cout << "数据来自客户端socket:" << sockClientFd << std::endl;
      std::cout << buff << std::endl;
      write(sockClientFd,buff,sizeof(buff));
    }else if(read_bytes == 0){
      std::cout << "客户端断开连接" << std::endl;
      close(sockClientFd);
      break;
    }else if(read_bytes == -1){
      close(sockClientFd);
      printError(true,"socket read errno");
    }
  }

  return 0;
}

