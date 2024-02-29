#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
using namespace std;
int main(){
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in server_addr;
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  // inet_addr 将字符串表示的ip地址转换为 in_addr_t 结构的地址
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(8888);


  bind(sockfd,(sockaddr*)&server_addr,sizeof(server_addr));
  cout << "开始监听" << endl;
  listen(sockfd,SOMAXCONN);
  
  // 接受客户端
  // 存储客户端地址的结构
  struct sockaddr_in clientAcceptAddr;
  bzero(&clientAcceptAddr,sizeof(clientAcceptAddr));
  socklen_t clientSockLength = sizeof(clientAcceptAddr);
  int sockClientFd = accept(sockfd,(sockaddr*)&clientAcceptAddr,&clientSockLength);
  cout << "客户端socket文件符：" << sockClientFd;
  cout << "客户端ip：" << inet_ntoa(clientAcceptAddr.sin_addr);
  cout << "客户端端口：" << ntohs(clientAcceptAddr.sin_port);
  cout << endl;
  return 0;
}