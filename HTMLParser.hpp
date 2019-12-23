/**
 * HTMLParser.hpp
 * 2019/12/22 R.Gunji
 */

#ifndef __INC_HTMLPARSER__
#define __INC_HTMLPARSER__

#include <string>
#include <regex>
#include <iterator>
#include <iostream>
#include <functional>
#include "ParserResult.hpp"

namespace rgpg {

  using std::cout;
  using std::endl;

  class HTMLParser {
    private:
      
    public:
      HTMLParser() = default;
      ~HTMLParser() = default;

      static 
      std::string get_tag_prefix(std::string const& str) {
        std::regex re_href {R"(href)"};
        std::regex re_src {R"(src)"};

        if (std::regex_search(str.begin(), str.end(), re_href)) {
          return "href";
        }

        if (std::regex_search(str.begin(), str.end(), re_src)) {
          return "src";
        }
      }

      static
      std::string extract_url(std::string const& str, std::string const& prefix) {
        std::string substr = str.substr(prefix.size() + 2);
        substr.pop_back();
        return substr;
      }

      static
      bool is_valid_url(std::string const& url) {
        if (url.front() == '#' ||
            std::regex_search(url.begin(), url.end(), std::regex(R"(href="https//www.\apple\.com")"))) 
            return false;

        return true;
      }

      static
      ParserResult extract(std::string const& contents, std::regex const& re) {
        ParserResult pr {};

        std::sregex_iterator sre_itr {std::sregex_iterator(std::begin(contents), std::end(contents), re)};
        std::sregex_iterator end;

        std::for_each(sre_itr, end, [&](std::smatch const sm) {
          auto url = extract_url(sm.str(), get_tag_prefix(sm.str()));
          if (is_valid_url(url)) pr.links.insert(url);
        });

        pr.localized_contents = contents;
        return pr;
      }

      static
      ParserResult run(std::string const& contents, std::string const& fmt) {
        std::regex re {fmt};
        auto pr = extract(contents, re);
        
        return pr;
      }
  };
}

#endif // __INC_HTMLPARSER__