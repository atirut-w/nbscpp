#include <nbs.hpp>
#include <cstdint>
#include <string>

int8_t read_byte(std::istream &stream)
{
    int8_t value;
    stream.read(reinterpret_cast<char *>(&value), sizeof(value));
    return value;
};

int16_t read_short(std::istream &stream)
{
    int16_t value;
    stream.read(reinterpret_cast<char *>(&value), sizeof(value));
    return value;
};

int32_t read_int(std::istream &stream)
{
    int32_t value;
    stream.read(reinterpret_cast<char *>(&value), sizeof(value));
    return value;
};

std::string read_pstring(std::istream &stream)
{
    int8_t length = read_int(stream);
    std::string value;
    value.resize(length);
    stream.read(value.data(), length);
    return value;
};

NBS::SongData::SongData(std::istream &stream)
{
    length = read_short(stream);
    height = read_short(stream);
    name = read_pstring(stream);
    author = read_pstring(stream);
    original_author = read_pstring(stream);
    description = read_pstring(stream);
};
