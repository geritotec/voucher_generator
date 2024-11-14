#include "crow.h"
#include "crow/middlewares/cors.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

void replaceKeyWithValue(std::string& html, const std::string& key, const std::string& value) {
    size_t pos = 0;
    while ((pos = html.find(key, pos)) != std::string::npos) {
        html.replace(pos, key.length(), value);
        pos += value.length();
    }
}

std::string replaceInHtmlContent(const std::string& filename, const std::unordered_map<std::string, std::string>& replacements) {
    // Leer el html
    std::ifstream inputFile(filename);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string htmlContent = buffer.str();

    // Reemplazar el texto
    for (const auto& [key, value] : replacements) {
        replaceKeyWithValue(htmlContent, key, value);
    }

    return htmlContent;
}

int main() {
    crow::App<crow::CORSHandler> app;

    CROW_ROUTE(app, "/generate-voucher").methods("POST"_method)([](const crow::request& req) {
        // Parsear la request
        auto jsonData = crow::json::load(req.body);
        if (!jsonData) {
            return crow::response(400, "Invalid JSON format");
        }

        // Mapa de reemplazos
        std::unordered_map<std::string, std::string> replacements = {
            {"{{reservationId}}", jsonData["reservationId"].s()},
            {"{{hotelName}}", jsonData["hotelName"].s()},
            {"{{customerId}}", jsonData["customerId"].s()},
            {"{{startDate}}", jsonData["startDate"].s()},
            {"{{endDate}}", jsonData["endDate"].s()},
            {"{{amountOfNights}}", jsonData["amountOfNights"].s()},
            {"{{amountPax}}", jsonData["amountPax"].s()},
            {"{{plan}}", jsonData["plan"].s()},
            {"{{description}}", jsonData["description"].s()},
            {"{{priceTable}}", jsonData["priceTable"].s()},
            {"{{createdAt}}", jsonData["createdAt"].s()}
        };

        std::string modifiedHtml = replaceInHtmlContent("voucher_template.html", replacements);

        // Mandar la respuesta como HTML
        crow::response res;
        res.code = 200;
        res.set_header("Content-Type", "text/html");
        res.body = modifiedHtml;

        return res;
    });

    app.port(8080).multithreaded().run();
    return 0;
}
