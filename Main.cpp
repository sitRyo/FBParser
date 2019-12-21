/**
 * Main.cpp
 * 2019/12/20 R.Gunji
 */

/* C++ */
#include <string>

/* handmade */
#include "CurlProc.hpp"
#include "OutputFile.hpp"

int main(int argc, char* argv[]) {
  std::string URL {"https://www.apple.com/"};
  if (argc >= 2) {
    URL = argv[1];
  }

  // curlが初期化
  rgpg::CurlProc proc;
  rgpg::OutputFile output_file;
  auto contents {proc.get_HTML(URL)};
    
  output_file.out(contents.memory, "index.html");

  return 0;
}