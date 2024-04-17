#pragma once

// 3rd party includes
#include <raylib.h>
#include <flecs.h>


# define JSON_DIAGNOSTICS 1
#include "nlohmann/json.hpp"
using json = nlohmann::json;

// C++ includes
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <filesystem>
namespace   FileSys = std::filesystem;
using       Path    = FileSys::path;