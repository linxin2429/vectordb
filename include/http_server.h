#pragma once

#include <httplib.h>
#include <rapidjson/document.h>
#include <string>
#include "faiss_index.h"
#include "index_factory.h"
class HttpServer {
    enum class CheckType {
        INSERT,
        SEARCH,
    };
   public:
    HttpServer(const std::string& host, int port);
    void start();

   private:
    void searchHandler(const httplib::Request& req, httplib::Response& res);
    void insertHandler(const httplib::Request& req, httplib::Response& res);
    void setJsonResponse(const rapidjson::Document& json_response,
                         httplib::Response& res);
    void setErrorJsonResponse(httplib::Response& res, int error_code,
                              const std::string& errorMsg);
    bool isRequestValid(const rapidjson::Document& json_request,
                        CheckType check_type);
    vectordb::IndexFactory::IndexType getIndexTypeFromRequest(
        const rapidjson::Document& json_request);
    httplib::Server server;
    std::string host;
    int port;
};