#include "HTMLResponse.h"
#include <fstream>
#include <iostream>


std::string HTMLResponse::build(const std::string& htmlFile, HttpStatus statusCode) {
    std::string content = getFile(htmlFile);
    return Response::build(content, statusCode);
}

std::string HTMLResponse::build(const std::string& htmlFile) {
    std::string content = getFile(htmlFile);
    return Response::build(content);
}

std::string HTMLResponse::getFile(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::logic_error("Error find file: " + fileName);
    }
    std::string content;
    std::streamsize size = file.tellg();
    content.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(&content[0], size);
    file.close();
    return content;
}