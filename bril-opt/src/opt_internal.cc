#include "opt_internal.hh"
#include <algorithm>
#include <helpers.hh>

json runOpt(const json &j_) {
  auto j = j_;
  if (!j.contains("functions")) {
    printDebug("%s", "there are no functions in the json");
    return j;
  }

  auto func_ = j["functions"];

  for (auto &f_ : func_) {
    if (!f_.contains("instrs")) {
      printDebug("function %s contains no instructions",
                 f_["name"].dump().c_str());
      continue;
    }
    auto instrs = f_["instrs"];

    std::vector<BasicBlock> bb_vector;
    getBasicBlock(instrs, bb_vector);
    for (auto &bb : bb_vector) {
      std::cout << bb.getName() << std::endl;
      for (auto inst_ : bb.getInst()) {
        std::cout << inst_.dump() << std::endl;
      }
    }
  }
  return j;
}

bool getJsonFromFile(const char *filename, json &j) {
  std::ifstream file(filename);
  if (!file) {
    printDebug("%s - %s", filename, "file not present");
    return false;
  }

  std::string file_data((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

  if (file_data.size() == 0) {
    printDebug("%s - %s", filename, "file is empty");
    return false;
  }

  j = json::parse(file_data);

  return true;
}
bool getBasicBlock(const json &instrs, std::vector<BasicBlock> &bb_vector) {
  std::string bb_name{"bb"};
  uint32_t bb_counter = 0;
  std::vector<json> tmp_;
  std::vector<std::string> terminators = {"jmp", "br", "ret"};
  std::string tmp_name{""};
  for (auto &inst_ : instrs) {
    if (inst_.contains("op")) {
      tmp_.push_back(inst_);
      if (std::find(terminators.begin(), terminators.end(),
                    inst_["op"].dump()) != terminators.end()) {
        if (tmp_name.size() == 0) {
          tmp_name = bb_name + std::to_string(bb_counter++);
        }
        BasicBlock bb(tmp_name);
        for (auto &tmp_inst : tmp_) {
          bb.push_inst(tmp_inst);
        }
        tmp_name.clear();
        tmp_.clear();
        bb_vector.emplace_back(bb);
      }
    } else { // A label
      if (tmp_.size() > 0) {
        if (tmp_name.size() == 0) {
          tmp_name = bb_name + std::to_string(bb_counter++);
        }
        BasicBlock bb(tmp_name);
        for (auto &tmp_inst : tmp_) {
          bb.push_inst(tmp_inst);
        }
        tmp_.clear();
        std::cout << "Label:: " << inst_["label"] << std::endl;
        tmp_name = inst_["label"];
        bb_vector.emplace_back(bb);
      }
    }
  }

  if (tmp_.size() > 0) {
    if (tmp_name.size() == 0) {
      tmp_name = bb_name + std::to_string(bb_counter++);
    }
    BasicBlock bb(tmp_name);
    for (auto &tmp_inst : tmp_) {
      bb.push_inst(tmp_inst);
    }
    tmp_.clear();
    tmp_name.clear();
    bb_vector.emplace_back(bb);
  }
  return true;
}