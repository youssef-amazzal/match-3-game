#include <filesystem>
#include "../headers/Header.h"

namespace   FileSys = std::filesystem;
using       Path    = FileSys::path;

class FileManager
{
private:
    FileManager() = default;

public:
    static const Path ROOT_PATH;
    static const Path ASSETS_PATH;
    static const Path SPRITES_PATH;
    static const Path AUDIO_PATH;

    static nlohmann::json parseJson(const std::string& path, const Path& basePath = FileManager::ROOT_PATH);
};
