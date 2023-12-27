#pragma once
#include <istream>
#include <string>

namespace NBS
{
    class SongData
    {
    public:
        SongData(std::istream &stream);

        int length;
        int height;
        std::string name;
        std::string author;
        std::string original_author;
        std::string description;
    };
}
