/**
 * Utility.hpp
 * 2019/12/20 R.Gunji
 */

#ifndef __INC_UTILITY__
#define __INC_UTILITY__

#include <list>
#include <string>
#include <regex>

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

    /**
     * is_alternative_url
     * @return bool
     * URLがアップルが持つ別言語サイトかどうか判定する。
     * あまりにも用途がアプリケーションによりすぎているのでUtilityに隔離
     */
    auto is_alternative_url(std::string const& url) {
      std::regex re(R"(https://www\.apple\.com)");
      return std::regex_search(url.begin(), url.end(), re);
    }

    /**
     * is_valid_url
     * @return bool
     * URLかどうか調べる。
     * 本当は正規表現でしっかり調べる必要があるが、今は時間がないので先頭がhttpかどうかで判定する。
     */
    auto is_valid_url(std::string const& url) {
      return url.substr(0, 4) == "http";
    }
  }
}

#endif // _INC_UTILITY__