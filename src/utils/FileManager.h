#pragma once
#include "../headers/Header.h"

class FileManager
{
    FileManager() = default;

public:

    static void createFileIfNotExists(const std::filesystem::path& filePath) {
        // Check if the parent directory exists
        if (!std::filesystem::exists(filePath.parent_path())) {
            // Create the directory and all parent directories if necessary
            std::filesystem::create_directories(filePath.parent_path());
        }

        // Check if the file exists
        if (!std::filesystem::exists(filePath)) {
            // Create and immediately close the file to generate it on the filesystem
            std::ofstream{filePath};
        }
    }

    static void writeJson(const Path& filePath, const nlohmann::json& data) {
        // Create the file if it doesn't exist
        createFileIfNotExists(filePath);

        std::ofstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            return;
        }

        file << data.dump(4);
    }


    static nlohmann::json readJson(const Path& filePath) {
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

    static nlohmann::json readJson(const std::string& path, const Path& basePath = ROOT_PATH) {
        Path filePath = basePath / path;
        return readJson(filePath);
    }
};
