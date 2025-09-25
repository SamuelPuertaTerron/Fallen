#pragma once

namespace FEngine
{
    using Path = std::filesystem::path;

    class Filesystem
    {
    public:
        // File operations
        static bool FileExists(const Path& path);
        static void CreateFile(const Path& path);
        static bool RemoveFile(const Path& path);

        static void WriteText(const Path& path, const std::string& text);
        static std::string ReadText(const Path& path);

        static bool WriteData(const Path& path, const std::vector<unsigned char>& data);
        static std::vector<unsigned char> ReadData(const Path& path);

        // Directory operations
        static bool DirectoryExists(const Path& path);
        static bool CreateDirectory(const Path& path);
        static bool RemoveDirectory(const Path& path);

        static std::vector<Path> ListFiles(const Path& directory, bool recursive = false);
    };
}//namespace FEngine