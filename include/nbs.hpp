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
        float tempo;
        bool autosave;
        int autosave_duration;
        int time_signature;
        int minutes_spent;
        int left_clicks;
        int right_clicks;
        int blocks_added;
        int blocks_removed;
        std::string midi_file_name;
    };
}
