#include "IDA.hpp"
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include<string.h>


int main(int argc, char const *argv[])
{
  std::vector<std::string> names{"pd"};
  PDB_MODE select;
  if (strcmp(argv[2], "ADD")==0){
    select = PDB_MODE :: ADD;
  }
  else if (strcmp(argv[2], "MAX")==0){
    select = PDB_MODE :: MAX;
  }
  else if (strcmp(argv[2], "MANHATTAN")==0){
    select = PDB_MODE :: MANHATTAN;
  }
  else{
    printf("Parametro invalido\n");
    return -1;
  }
  printf("Corriendo IDA*...\n");
  PDB pdb{names,select};
  state_t state;
  read_state(argv[1], &state);
  ida_search(state,pdb);
  return 0;
}