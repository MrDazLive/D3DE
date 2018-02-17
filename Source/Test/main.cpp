#include <iostream>
#include <list>

#ifdef _WIN32
#ifdef _DEBUG
std::string run = std::string("cd /d \"") + OUTPUT_DIRECTORY + "/Debug\" && Test-";
#else
std::string run = std::string("cd /d \"") + OUTPUT_DIRECTORY + "/Release\" && Test-";
#endif
#else
std::string run = "./Test-";
#endif

std::list<const char*> tests {
  "Platform",
  "Types",
  "Core"
};

int main(int argc, char **args) {
  for(auto test : tests) {
    if(system((run + test).c_str()))
      std::cin.ignore();
  }
  std::cin.ignore();
}