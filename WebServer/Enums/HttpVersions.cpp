#include "HttpVersions.h"

std::string getStringHttpVersions(HttpVersion version) {
    switch (version) {
        case HttpVersion::HTTP_1_0:
            return "HTTP/1.0";
        case HttpVersion::HTTP_1_1:
            return "HTTP/1.1";
        case HttpVersion::HTTP_2_0:
            return "HTTP/2.0";
        case HttpVersion::HTTP_3_0:
            return "HTTP/3.0";
        default:
            return "";
    }
}