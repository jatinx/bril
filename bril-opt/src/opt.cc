/*Optimizer for BRIL
  Input is file of JSON
  Output is JSON as String
 */

#include "opt_internal.hh"
#include <helpers.hh>
#include <iostream>

using json = nlohmann::json;

int main(int argc, char **argv) {
  if (argc < 2 || argc > 2)
    errorAndCrash("opt needs just one arg, file name");

  json original;
  if (!getJsonFromFile(argv[1], original))
    errorAndCrash("file doesnt exist or empty");

  auto new_ast = runOpt(original);

  std::string final = new_ast.dump();
  std::cout << final << std::endl;

  return 0;
}