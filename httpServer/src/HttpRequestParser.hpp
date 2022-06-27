#ifndef HTTPSERVER_SRC_HTTPREQUESTPARSER_HPP_
#define HTTPSERVER_SRC_HTTPREQUESTPARSER_HPP_

#include <string>

#include "HttpRequest.hpp"

class HttpRequestParser {
 public:
  HttpRequestParser();
  ~HttpRequestParser();

  HttpRequest* parse(const char* buffer);

 private:
  HttpRequestParser(const HttpRequest& other);
  HttpRequestParser& operator=(const HttpRequest& other);

  void parseRequestLine(const char* buffer);
  void parseHeaderField(const char* buffer);
  void setBody(const char* buffer);
};

#endif  // HTTPSERVER_SRC_HTTPREQUESTPARSER_HPP
