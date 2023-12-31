#include <nbs.hpp>
#include <cstdint>
#include <string>
#include <stdexcept>

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
    if (length == 0)
    {
        throw std::runtime_error("Non-classic NBS files are not supported."); // TODO: Implement non-classic NBS files
    }

    height = read_short(stream);
    name = read_pstring(stream);
    author = read_pstring(stream);
    original_author = read_pstring(stream);
    description = read_pstring(stream);
    tempo = read_short(stream) / 100.0f;
    autosave = read_byte(stream);
    autosave_duration = read_byte(stream);
    time_signature = read_byte(stream);
    minutes_spent = read_int(stream);
    left_clicks = read_int(stream);
    right_clicks = read_int(stream);
    blocks_added = read_int(stream);
    blocks_removed = read_int(stream);
    midi_file_name = read_pstring(stream);

    layers.resize(height + 1);
    for (Layer &layer : layers)
    {
        layer.notes.resize(length + 1);
    }

    for(int tick = -1;;)
    {
        int tjumps = read_short(stream);
        if (tjumps == 0)
        {
            break;
        }
        tick += tjumps;

        for (int layer = -1;;)
        {
            int ljumps = read_short(stream);
            if (ljumps == 0)
            {
                break;
            }
            layer += ljumps;

            int instrument = read_byte(stream);
            int key = read_byte(stream);

            // Learned the weird way: length and layer count cannot be trusted
            if (layers.size() <= layer)
                layers.resize(layer + 1);
            if (layers[layer].notes.size() <= tick)
                layers[layer].notes.resize(tick + 1);

            layers[layer].notes[tick].instrument = instrument;
        }
    }
};
