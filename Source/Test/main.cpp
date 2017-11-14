#include <iostream>
#include <list>

std::list<const char*> tests {
  "./Types-Test",
  "./Core-Test"
};

int main(int argc, char **args) {
  for(auto test : tests) {
    if(system(test))
      std::cin.ignore();
  }
}