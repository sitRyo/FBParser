/**
 * Parser.hpp
 * 2019/12/22 R.Gunji
 */

#ifndef __INC_PARSER__
#define __INC_PARSER__

#include <string>
#include "ParserResult.hpp"
#include "HTMLParser.hpp"

namespace rgpg {

  class Parser {
    private:
      
    public:
      Parser() = default;
      ~Parser() = default;

      /**
       * TODO 完全転送
       */
      static
      ParserResult html_to_localize(std::string const& contents) {
        std::string fmt = R"(href=".*?"|src=".*?")";
        return HTMLParser::run(contents, fmt);
      }

      /**
       * TODO 完全転送
       */
      static
      ParserResult css_to_localize(std::string& contents) {

      }
  };
}

#endif // __INC_PARSER__