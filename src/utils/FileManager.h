
#include "../headers/Header.h"

class FileManager
{
private:
    FileManager() = default;

public:

    static nlohmann::json parseJson(const Path& filePath) {
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            return {};
        }

        try {
            nlohmann::json parsed = nlohmann::json::parse(file);
            return parsed;
        } catch (nlohmann::json::parse_error& e) {
            std::cerr << "JSON parse error: " << e.what() << std::endl;
            return {};
        }
    }

    static nlohmann::json parseJson(const std::string& path, const Path& basePath = ROOT_PATH) {
        Path filePath = basePath / path;
        return parseJson(filePath);
    }
};
