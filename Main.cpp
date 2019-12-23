/**
 * Main.cpp
 * 2019/12/20 R.Gunji
 */

/* C++ */
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <queue>
#include <regex>
#include <functional>

/* handmade */
#include "CurlProc.hpp"
#include "utility.hpp"
#include "OutputFile.hpp"
#include "Parser.hpp"

namespace fs = std::filesystem;

using std::cout;
using std::endl;

class MyProc {
  private:
    int depth;
    std::string URL;
    std::unordered_map<std::string, std::string> url_to_absolute_path;
    std::unordered_map<std::string, std::string> url_to_relative_path;
    std::unordered_map<std::string, bool> is_parsed;
    std::string absolute_path;
    std::queue<std::string> next_url;
    
    rgpg::CurlProc curl;
    rgpg::OutputFile out;

    std::string check_url_name(std::string const& url) {
      fs::path url_path {url};
      fs::path file_name {url_path.filename()};
      fs::path file_extension {url_path.extension()};

      if (!file_name.empty() && !file_extension.empty() && (file_extension == ".html" || file_extension == ".js" || file_extension == ".css")) {
        return url;
      }

      if (!file_name.empty() && file_extension.empty()) {
        return url + "/index.html";
      }

      // file_name.empty()
      return url + "index.html";
    }

    std::string get_html(std::string const& url) {
      auto res = curl.get_HTML(url);
      return res.memory;
    }

    std::unordered_set<std::string> parse_html(std::string const& contents) {
      return rgpg::Parser::html_to_localize(contents).links;
    }

    void set_url_to_absolute_path(std::unordered_set<std::string> const& links) {
      for (auto&& itr : links) {
        if (rgpg::util::is_alternative_url(itr)) continue;
        std::string url {rgpg::util::is_valid_url(itr) ? itr : URL + itr};
        url_to_relative_path[itr] = check_url_name(absolute_path + std::regex_replace(url, std::regex(R"(:/)"), ""));
        url_to_absolute_path[url] = check_url_name(absolute_path + url);
      }
    }

    void set_next_url_queue() {
      for (auto&& url : url_to_absolute_path) {
        // これは本当は良くない。
        // memberにアクセスするのは関数の結合度が上がる(thisを付けてmemberにアクセスすることをアピール)
        if (!is_parsed[url.first]) this->next_url.push(url.first);
      }
    }

    void rewrite_raw_document(std::string& raw_doc, std::unordered_set<std::string> links) {
      for (auto url : links) {
        // cout << url << endl;
        // cout << url_to_relative_path[url] << endl;
        if (url.front() == '{' || url.front() == '?') continue;
        std::regex re("\"" + url + "\"");
        raw_doc = std::regex_replace(raw_doc, re, "\"" + url_to_relative_path[url] + "\"");
        // cout << url_to_relative_path[url] << endl;
      }
    }

    void output_file(std::string const& u, std::string const& contents) {
      fs::path output_path {url_to_absolute_path[u]};
      fs::path output_file_name {output_path.filename()};
      auto url = u;
      url = std::regex_replace(url, std::regex(R"(:/)"), "");
      fs::path url_path {url};
      out(contents, output_file_name.string());
      
      cout << output_file_name.string() << endl;
      cout << url << endl;
      cout << url_path.remove_filename() << endl;
      
      if (output_file_name == "index.html") {
        fs::create_directories(url);
        fs::rename(output_file_name.string(), url + "/" + output_file_name.string());
      } else {
        fs::create_directories(url_path.remove_filename());
        fs::rename(output_file_name.string(), url_path.remove_filename().string() + output_file_name.string());
      }
    }

    void debug() {
      for (auto itr : url_to_absolute_path) {
        cout << itr.first << endl;
        cout << itr.second << endl;
      }
    }

  public:
    MyProc(int const& depth, std::string URL, std::string absolute_path) 
    : depth(depth), URL(URL), absolute_path(absolute_path) 
    {
      next_url.push(URL);
      url_to_absolute_path[URL] = absolute_path + URL + "/index.html";
    }

    ~MyProc() = default;

    /**
     * Todo? Delete copy, move Constructor.
     */
    
    void go() {
      while (depth > 0) {
        -- depth;
        std::queue<std::string> new_url;
        while (!next_url.empty()) {
          auto url = next_url.front(); next_url.pop();
          cout << "url "  << url << endl;
          is_parsed[url] = true;
          auto raw_doc = get_html(url);
          auto links = parse_html(raw_doc);
          set_url_to_absolute_path(links);
          rewrite_raw_document(raw_doc, links);
          output_file(url, raw_doc);
        }
        set_next_url_queue();
      }
    }
};

int main(int argc, char* argv[]) {
  std::string URL {"https://www.apple.com"};
  std::string absolute_path {"file:///E:/production/HTMLParser/build/"};
  
  if (argc >= 2) {
    URL = argv[1];
  }
  
  MyProc proc(2, URL, absolute_path);
  proc.go();
  return 0;
}
