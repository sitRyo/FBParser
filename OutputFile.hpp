/**
 * Output.hpp
 * 2019/12/21 R.Gunji
 * img, html, plaintxtなどを出力するクラス
 */

#ifndef __INC_OUTPUTFILE__
#define __INC_OUTPUTFILE__

#include <fstream>
#include <iostream>
#include <string>

namespace rgpg {

  class OutputFile {
  private:

    /**
     * TODO file_name の右辺値化 std::forwardを使った完全転送
     */
    bool open(std::string const& file_name, std::fstream &f_stream) const {
      f_stream.open(file_name, std::ios::out);
      if (!f_stream.is_open()) {
        std::cerr << "File can't open\n";
        return false;
      }

      return true;
    } 

    void close(std::fstream &f_stream) const {
      f_stream.close();
    } 
    
    /**
     * TODO file_name の右辺値化 std::forwardを使った完全転送
     */
    bool out(std::string const& contents, std::string const& file_name) const {
      // std::cout << contents << std::endl;
      std::fstream f_stream;
      if (!this->open(file_name, f_stream)) {
        return false;
      }
      f_stream << contents << std::endl;;
      this->close(f_stream);
      return true;
    }

  public:
    OutputFile() {}

    ~OutputFile() {}

    /**
     * TODO Universal forward
     */
    bool operator() (std::string const& contents, std::string const& file_name) const {
      return this->out(contents, file_name);
    }
  };
  
} // namespace rgpg 

#endif // __INC_OUTPUT__