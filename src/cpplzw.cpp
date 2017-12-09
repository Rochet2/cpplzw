#include <string>
#include <vector>
#include <unordered_map>
#include <utility> // std::make_pair
#include <functional> // std::hash
#include <cstddef> // std::size_t

// range of byte values used in compression output.
// if min = 0 then the compression output can contain null characters in the middle of the string
static constexpr int min = 1;
static constexpr int max = 255;

struct Hash {
    inline std::size_t operator () (std::vector<char> const & str) const
    {
        return std::hash<std::string>()(std::string(str.cbegin(), str.cend()));
    }
};

typedef std::unordered_map<std::vector<char>, std::pair<char, char>, Hash> Dictionary;

static void dictAdd(std::vector<char> const & str, Dictionary& dict, int& a, int& b)
{
    if (a >= max + 1)
    {
        a = min;
        ++b;
        if (b >= max + 1)
        {
            dict.clear();
            b = min + 1;
        }
    }
    dict[str] = std::make_pair(a, b);
    ++a;
}

std::string compress(std::string const & input)
{
    Dictionary dict;
    int a = min;
    int b = min + 1;

    std::vector<char> result;
    result.push_back('c');
    std::vector<char> word;
    for (const char & c : input) {
        std::vector<char> wc = word;
        wc.push_back(c);
        if (!(wc.size() == 1 || dict.find(wc) != dict.end()))
        {
            if (word.size() == 1)
            {
                result.push_back(word.at(0));
                result.push_back(static_cast<char>(min));
            }
            else
            {
                auto& temp = dict[word];
                result.push_back(temp.first);
                result.push_back(temp.second);
            }
            dictAdd(wc, dict, a, b);
            word.clear();
            word.push_back(c);
        }
        else
            word = wc;
    }
    if (word.size() == 1)
    {
        result.push_back(word.at(0));
        result.push_back(static_cast<char>(min));
    }
    else
    {
        auto& temp = dict[word];
        result.push_back(temp.first);
        result.push_back(temp.second);
    }
    if (input.size() <= result.size())
        return 'u' + input;
    return std::string(result.cbegin(), result.cend());
}
