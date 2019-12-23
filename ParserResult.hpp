/**
 * ParserResult.hpp
 * 2019/12/22 R.Gunji
 */

#ifndef __INC_PARSERRESULT__
#define __INC_PARSERRESULT__

#include <string>
#include <unordered_set>

namespace rgpg {

  enum FILE_TYPE {
    HTML = 0,
    CSS = 1,
  };

  struct ParserResult {
    std::string localized_contents;
    
    // key URL, value indicates either css or html.
    std::unordered_set<std::string> links;
  };
}

#endif // __INC_PARSERRESULT__