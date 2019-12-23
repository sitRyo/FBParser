#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <filesystem>

using namespace std::filesystem;
using namespace std;

int main() {
  create_directories("a/b/c.txt");
  path p {"a/b/c.txt"};
  cout << p.filename() << endl;
  cout << current_path() << endl;
}