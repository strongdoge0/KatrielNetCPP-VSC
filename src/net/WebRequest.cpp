#include "WebRequest.hpp"

void ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

std::string WebRequest::Get(std::string website, std::string path, std::string username, std::string password) {
  std::string result = "";

  httplib::Client cli(website);
  
  httplib::Headers headers = {};

  cli.set_basic_auth(username, password);
  
  if (auto res = cli.Get("/"+path, headers)) {
    if (res->status == httplib::StatusCode::OK_200) {
      ReplaceAll(res->body, "\\n", "\n");
      result = res->body;
    }
  } else {
    auto err = res.error();
    std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
  }

  return result;
}

std::string WebRequest::Get(std::string website, std::string path, std::string cookie) {
  std::string result = "";

  httplib::Client cli(website);
  
  httplib::Headers headers = {
    {"Cookie", cookie}, //cookie
    //{"Accept", "text/plain"}
    };

  if (auto res = cli.Get("/"+path, headers)) {
    if (res->status == httplib::StatusCode::OK_200) {
      ReplaceAll(res->body, "\\n", "\n");
      result = res->body;
    }
  } else {
    auto err = res.error();
    std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
  }

  return result;
}