#include "Globals.h"
#include "Filesystem.h"

#include <raylib/raylib.h>

namespace FEngine
{
    bool Filesystem::FileExists(const Path& path)
    {
        return ::FileExists(path.string().c_str());
    }

    void Filesystem::CreateFile(const Path& path)
    {
        std::ofstream ofs(path);
        ofs.close();
    }

    bool Filesystem::RemoveFile(const Path& path)
    {
        return std::filesystem::remove(path);
    }

    void Filesystem::WriteText(const Path& path, const std::string& text)
    {
        std::ofstream file(path, std::ios::app);
        file << text + "\n";
    }

    std::string Filesystem::ReadText(const Path& path)
    {
        if (!FileExists(path))
        {
            return {};
        }

        char* text = LoadFileText(path.string().c_str());
        if (!text)
        {
            return {};
        }

        std::string result(text);
        UnloadFileText(text);
        return result;
    }

    bool Filesystem::WriteData(const Path& path, const std::vector<unsigned char>& data)
    {
        return SaveFileData(path.string().c_str(), (void*)data.data(), static_cast<int>(data.size()));
    }

    std::vector<unsigned char> Filesystem::ReadData(const Path& path)
    {
        int size = 0;
        unsigned char* buffer = LoadFileData(path.string().c_str(), &size);
        if (!buffer)
        {
            return {};
        }

        std::vector<unsigned char> data(buffer, buffer + size);
        UnloadFileData(buffer);
        return data;
    }

    bool Filesystem::DirectoryExists(const Path& path)
    {
        return ::DirectoryExists(path.string().c_str());
    }

    bool Filesystem::CreateDirectory(const Path& path)
    {
        return std::filesystem::create_directory(path);
    }

    bool Filesystem::RemoveDirectory(const Path& path)
    {
        return std::filesystem::remove_all(path) > 0;
    }

    std::vector<Path> Filesystem::ListFiles(const Path& directory, bool recursive)
    {
        std::vector<Path> files;

        if (!DirectoryExists(directory))
        {
            return files;
        }

        if (recursive)
        {
            for (auto& entry : std::filesystem::recursive_directory_iterator(directory))
            {
                if (entry.is_regular_file())
                {
                    files.push_back(entry.path());
                }
            }
        }
        else
        {
            for (auto& entry : std::filesystem::directory_iterator(directory))
            {
                if (entry.is_regular_file())
                {
                    files.push_back(entry.path());
                }
            }
        }

        return files;
    }
}//namespace FEngine