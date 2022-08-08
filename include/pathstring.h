#include <cstdlib>
#include <iostream>
#include <string>

using std::cerr;
using std::endl;
using std::getenv;
using std::string;

const char *ENV_VAR = "PATH_DECODE";

std::string extract(std::string name_dir) {
  const char *tmp = getenv(ENV_VAR);
  string env_var(tmp ? tmp : "");
  if (env_var.empty()) {
    cerr << "[ERROR] No such variable found!" << endl;
    exit(EXIT_FAILURE);
  }

  return env_var + name_dir;
}
