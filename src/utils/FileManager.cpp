#include "FileManager.h"

const Path FileManager::ROOT_PATH       = FileSys::current_path().parent_path();
const Path FileManager::ASSETS_PATH     = FileManager::ROOT_PATH / "assets"; // "/" operator from std::filesystem::path
const Path FileManager::SPRITES_PATH    = FileManager::ASSETS_PATH / "sprites";
const Path FileManager::AUDIO_PATH      = FileManager::ASSETS_PATH / "audio";

nlohmann::json FileManager::parseJson(const std::string& path, const Path& basePath) {
    Path filePath = basePath / path;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return nlohmann::json();
    }

    try {
        nlohmann::json parsed = nlohmann::json::parse(file);
        return parsed;
    } catch (nlohmann::json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return nlohmann::json();
    }
}