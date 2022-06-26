#ifndef HTTPSERVER_SRC_HTTPRESPONSE_HPP_
#define HTTPSERVER_SRC_HTTPRESPONSE_HPP_

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

class HttpResponse {
  // HTTPの教科書に載ってたもの。提出するときは対応したものだけにする？
  enum HttpStatus {
    HTTP_OK = 200,
    HTTP_NO_CONTENT = 204,
    HTTP_PARTIAL_CONTENT = 206,
    HTTP_MOVED_PERMANENTLY = 301,
    HTTP_FOUND = 302,
    HTTP_SEE_OTHER = 303,
    HTTP_NOT_MODIFIED = 304,
    HTTP_TEMPORARY_REDIRECT = 307,
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_INTERNAL_SERVER_ERROR = 500,
    HTTP_SERVICE_UNAVAILABLE = 503,
  };

 public:
  // デフォルトはHTTP/1.1 200 OK
  HttpResponse();
  // HttpResponse(const std::string&  version, const std::string &);
  ~HttpResponse();

  // void setVersion();
  // void setStatusCode();
  // void appendHeaderField();
  void setBody(const std::string& body);
  std::string toString() const;

 private:
  // とりあえずコピーしない想定
  HttpResponse(const HttpResponse& other);
  HttpResponse& operator=(const HttpResponse& other);

  static const std::string& getReasonForStatus(HttpStatus status);

  std::string version_;
  HttpStatus status_code_;
  std::string reason_phrase_;
  std::string content_length_;
  std::string body_;

  static const std::string kHttpReasonOk;
  static const std::string kHttpReasonNoContent;
  static const std::string kHttpReasonPartialContent;
  static const std::string kHttpReasonMovedPermanently;
  static const std::string kHttpReasonFound;
  static const std::string kHttpReasonSeeOther;
  static const std::string kHttpReasonNotModified;
  static const std::string kHttpReasonTemporaryRedirect;
  static const std::string kHttpReasonBadRequest;
  static const std::string kHttpReasonUnauthorized;
  static const std::string kHttpReasonForbidden;
  static const std::string kHttpReasonNotFound;
  static const std::string kHttpReasonInternalServerError;
  static const std::string kHttpReasonServiceUnavailable;
  static const std::string kHttpReasonUnknown;
};

#endif  // HTTPSERVER_SRC_HTTPRESPONSE_HPP_
