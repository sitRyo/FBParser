#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main() {
  path p {"abc/"};
  cout << p.filename() << endl;
  cout << p.extension() << endl;
}