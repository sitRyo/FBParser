/**
 * CURLResponse.hpp
 * 2019/12/21 R.Gunji
 * CURLのレスポンスを格納する構造体
 */

#ifndef __INC_CURLRESPONCE__
#define __INC_CURLRESPONCE__

#include <string>

namespace rgpg {
  
  struct CURLResponse {
    std::string memory;
    size_t size;
  };
  
} // namespace rgpg

#endif // __INC_CURLRESPONCE__