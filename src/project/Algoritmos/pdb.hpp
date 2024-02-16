#pragma once

#include <vector>
#include <cassert>
#include <string>

#include<cmath>


enum class PDB_MODE {ADD, MAX, MANHATTAN};


struct PDB_INFO {
  abstraction_t* abst;
  state_map_t* pdb;

  PDB_INFO(){}

  PDB_INFO(std::string abst, std::string pdb){
    this->abst = read_abstraction_from_file(abst.c_str());
    FILE *pdb_file = fopen(pdb.c_str(), "r");
    assert(pdb_file != NULL);
    this->pdb = read_state_map(pdb_file);
    fclose(pdb_file);
  }
};


struct PDB {
  std::vector<PDB_INFO> pdbs;
  PDB_MODE mode;

  PDB(){}

  PDB(std::vector<std::string> names,PDB_MODE mode){
    for (auto name: names){
      PDB_INFO info{name+".abst",name+".pdb"};
      this->pdbs.push_back(info);
    }
    this->mode=mode;
  }

  int h_Manhattan(state_t current){
    int n = 0;
    for (size_t i = 0; i < NUMVARS; i++)
    {
      int value = current.vars[i];
      int d = value - i;
      n += pow(d / NUMVARS,2) + pow(d % NUMVARS,2);
    }

    return n;
    
  }

  int h(state_t current_state){
    int *pdb_value;
    int value = 0;
    int temp;
    for(auto pdb_info : this->pdbs)
    {
      if (this->mode == PDB_MODE ::MANHATTAN){
        value = h_Manhattan(current_state);
        break;
      }
      state_t abst_state;
      abstract_state(pdb_info.abst, &current_state, &abst_state);
      pdb_value = state_map_get(pdb_info.pdb, &abst_state);
      assert(pdb_value != 0);
      temp = *pdb_value;
      switch (this->mode)
      {
      case PDB_MODE::ADD:
        value += temp;
        break;
      case PDB_MODE::MAX:
        value = value >= temp ? value : temp;
        break;
      case PDB_MODE::MANHATTAN:
        value = h_Manhattan(abst_state);
        break;
      default:
        break;
      }
    }
    return value;
  }

};