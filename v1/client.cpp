#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
int main(){
  int sockfd = socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in server_addr;
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  // inet_addr 将字符串表示的ip地址转换为 in_addr_t 结构的地址
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(8888);
  connect(sockfd,(sockaddr*)&server_addr,sizeof(server_addr));
  return 0;
  
}