/**
 * Utility.hpp
 * 2019/12/20 R.Gunji
 */

#ifndef __INC_UTILITY__
#define __INC_UTILITY__

#include <list>
#include <string>

namespace rgpg {
  namespace util {
    
    /**
     * split
     * @return std::list<std::string>
     * 文字列を分割する。
     * NOTE string_viewを使えないかと思ったけど、参照を持つだけかつイミュータブルなので後で書き換えられなさそうなので今回はパス。
     */
    auto split(std::string str, std::string delim) {
      std::list<std::string> ret;
      int cutAt;
      while ((cutAt = str.find_first_of(delim)) != str.npos) {
        if (cutAt > 0) {
          ret.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
      }

      return ret;
    }

    
  }
}

/**
 * 
 */ 

#endif // _INC_UTILITY__