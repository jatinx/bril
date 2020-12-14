#pragma once

#include <helpers.hh>

// Main function to run opt
json runOpt(const json &);

bool getJsonFromFile(const char *filename, json &j);

class BasicBlock {
  std::string name;
  std::vector<json> inst;

public:
  BasicBlock(const std::string &name_) : name(name_) {}
  std::string &getName() { return name; }
  void push_inst(const json &inst_) { inst.push_back(inst_); }
  auto &getInst() { return inst; }
};

bool getBasicBlock(const json &, std::vector<BasicBlock> &);