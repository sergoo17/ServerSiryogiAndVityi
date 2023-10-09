#ifndef HTML_RESPONSE_H
#define HTML_RESPONSE_H


#include <string>
#include <filesystem>
#include "../Response/Response.h"

namespace HTMLResponse {
    std::string build(const std::string& htmlFile, HttpStatus statusCode);
    std::string build(const std::string& htmlFile);
    std::string getFile(const std::string& file);
};


#endif //HTML_RESPONSE_H
