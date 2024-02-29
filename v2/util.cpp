#include "util.h"
void printError(bool condition,const std::string& errnoMessage){
  if(condition){
    std::cerr << errnoMessage << std::endl;
    exit(EXIT_FAILURE);
  }
}