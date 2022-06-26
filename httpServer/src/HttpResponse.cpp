#include "HttpResponse.hpp"

HttpResponse::HttpResponse()
    : version_("1.1"),
      status_code_(HTTP_OK),
      reason_phrase_(getReasonForStatus(status_code_)) {}

HttpResponse::~HttpResponse() {}

void HttpResponse::setBody(const std::string& body) {
  body_ = body;
  size_t body_size = body_.size();
  std::ostringstream oss;
  oss << body_size << std::flush;
  content_length_ = oss.str();
}

std::string HttpResponse::toString() const {
  std::ostringstream oss;

  oss << "HTTP/" << version_ << " " << status_code_ << " " << reason_phrase_
      << "\r\n"
      << "Content-Length: " << content_length_ << "\r\n\r\n"
      << body_ << "\r\n";
  return oss.str();
}

const std::string& HttpResponse::getReasonForStatus(HttpStatus status) {
  switch (status) {
    case HTTP_OK:
      return kHttpReasonOk;
    case HTTP_NO_CONTENT:
      return kHttpReasonNoContent;
    case HTTP_PARTIAL_CONTENT:
      return kHttpReasonPartialContent;
    case HTTP_MOVED_PERMANENTLY:
      return kHttpReasonMovedPermanently;
    case HTTP_FOUND:
      return kHttpReasonFound;
    case HTTP_SEE_OTHER:
      return kHttpReasonSeeOther;
    case HTTP_NOT_MODIFIED:
      return kHttpReasonNotModified;
    case HTTP_TEMPORARY_REDIRECT:
      return kHttpReasonTemporaryRedirect;
    case HTTP_BAD_REQUEST:
      return kHttpReasonBadRequest;
    case HTTP_UNAUTHORIZED:
      return kHttpReasonUnauthorized;
    case HTTP_FORBIDDEN:
      return kHttpReasonForbidden;
    case HTTP_NOT_FOUND:
      return kHttpReasonNotFound;
    case HTTP_INTERNAL_SERVER_ERROR:
      return kHttpReasonInternalServerError;
    case HTTP_SERVICE_UNAVAILABLE:
      return kHttpReasonServiceUnavailable;
    default:
      return kHttpReasonUnknown;
  }
}

const std::string HttpResponse::kHttpReasonOk = "OK";
const std::string HttpResponse::kHttpReasonNoContent = "No Content";
const std::string HttpResponse::kHttpReasonPartialContent = "Partial Content";
const std::string HttpResponse::kHttpReasonMovedPermanently =
    "Moved Permanently";
const std::string HttpResponse::kHttpReasonFound = "Found";
const std::string HttpResponse::kHttpReasonSeeOther = "See Other";
const std::string HttpResponse::kHttpReasonNotModified = "Not Modified";
const std::string HttpResponse::kHttpReasonTemporaryRedirect =
    "Temporary Redirect";
const std::string HttpResponse::kHttpReasonBadRequest = "Bad Request";
const std::string HttpResponse::kHttpReasonUnauthorized = "Unauthorized";
const std::string HttpResponse::kHttpReasonForbidden = "Forbidden";
const std::string HttpResponse::kHttpReasonNotFound = "Not Found";
const std::string HttpResponse::kHttpReasonInternalServerError =
    "Internal Server Error";
const std::string HttpResponse::kHttpReasonServiceUnavailable =
    "Service Unavailable";
const std::string HttpResponse::kHttpReasonUnknown = "Hum..Unexecpted Error:(";
