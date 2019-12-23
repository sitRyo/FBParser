/**
 * OutputWrapper.hpp
 * 2019/12/22 R.Gunji
 */

#ifndef __INC_OUTPUT_WRAPPER__
#define __INC_OUTPUT_WRAPPER__

#include <filesystem>
#include <string>
#include "OutputFile.hpp"

namespace rgpg {
  
  class OutputWrapper {
    public:
      OutputWrapper() = default;
      ~OutputWrapper() = default;

      static
      void create_directories(std::string dir_path) {
        std::filesystem::create_directories(dir_path);
      }

      static
      void out (std::string const& file, std::string& contents) {
        OutputFile opf;
        std::filesystem::path target_path {file};
        auto file_name = target_path.filename();
        create_directories(target_path.remove_filename());
        opf(contents, file);
      }
  };
} // namespace rgpg


#endif // __INC_OUTPUT_WRAPPER__