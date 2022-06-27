#ifndef HTTPSERVER_SRC_HTTPREQUEST_HPP_
#define HTTPSERVER_SRC_HTTPREQUEST_HPP_

#include <map>
#include <string>

class HttpRequest {
 public:
  HttpRequest();
  ~HttpRequest();

  // アクセッサー
 private:
  HttpRequest(const HttpRequest& other);
  HttpRequest& operator=(const HttpRequest& other);

  std::string method_;
  std::string uri_;
  std::string version_;
  std::map<std::string, std::string> headerfield_to_value_;
  std::string body_;
};

#endif  // HTTPSERVER_SRC_HTTPREQUEST_HPP
