#include "Utils.h"

#include <windows.h>

std::string Utils::getExecutablePath()
{
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);

    std::string exePath(path);
    size_t pos = exePath.find_last_of("\\/");
    return (std::string::npos == pos) ? "" : exePath.substr(0, pos);
}
