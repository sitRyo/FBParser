/**
 * Main.cpp
 * 2019/12/20 R.Gunji
 */

/* C++ */
#include <string>

/* handmade */
#include "CurlProc.hpp"

int main(int argc, char* argv[]) {
  std::string URL {"https://www.apple.com/jp/"};
  if (argc >= 2) {
    URL = argv[1];
  }

  // curlが初期化
  rgpg::CurlProc proc;
  auto contents {proc.get_HTML(URL)};

  std::cout << contents.memory << std::endl;

  return 0;
}