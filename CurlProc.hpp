/**
 * CurlProc.hpp
 * 2019/12/20 R.Gunji
 */ 

#ifndef __INC_CURL_PROC__
#define __INC_CURL_PROC__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <list>
#include <string_view>

#include "CURLResponse.hpp"

namespace rgpg {
  
  /**
   * CurlProc class
   * CURLを実行する。
   */
  class CurlProc {
    CURL *curl {};

    struct MemoryStruct {
      char *memory;
      size_t size;
    };

    public:

      /**
       * Constructor
       * curlのinitのみを行う。
       */
      CurlProc() {
        curl = curl_easy_init();
        if (!curl) {
          std::cerr << "couldn't init curl\n";
          exit(0);
        }
      }

      /**
       * WriteMemoryCallback
       * CURLリクエストを取得し、その内容を返す。
       */
      static
      size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
        size_t realsize {size * nmemb};
        struct MemoryStruct *mem {(struct MemoryStruct *) userp};

        char *ptr = (char*) realloc(mem->memory, mem->size + realsize + 1);
        if(ptr == NULL) {
          printf("not enough memory (realloc returned NULL)\n");
          return 0;
        }

        mem->memory = ptr;
        memcpy(&(mem->memory[mem->size]), contents, realsize);
        mem->size += realsize;
        // insert NULL char.
        mem->memory[mem->size] = 0;

        return realsize;
      }

      /**
       * get_HTML
       */
      CURLResponse get_HTML(std::string URL) {
        CURLResponse c_res {};
        MemoryStruct chunk {};

        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        // curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&c_res.ret_code);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        
        CURLcode ret {curl_easy_perform(curl)};

        if (ret != CURLE_OK) {
          std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(ret) << "\n";
        } else {
          c_res.memory.assign(chunk.memory, chunk.size);
          c_res.size = chunk.size;
        }

        // curlハンドルを使いまわすために設定
        // おそらくこれで別のURLを入れても取得できる？
        // NOTE これでAppleと情報工学科のトップページの取得はできた。他の設定がどうかは理解していないがとりあえずこれでOKとしてみる。
        curl_easy_reset(curl);
        
        return c_res;
      }

      ~CurlProc() {
        curl_easy_cleanup(curl);
      }
  };
}

#endif // __INC_CURL_PROC_