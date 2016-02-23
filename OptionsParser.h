#include <map>
#include <string>
#include <vector>


class OptionsParser
{
    std::map<std::string, std::string> namedArguments;
    std::vector<std::string> unNamedArguments;

public:

    OptionsParser(int ac, char **argv);

    bool checkOptions(std::string optionName);

    bool tryGetInt(std::string optionName, int & value);

    bool tryGetFloat(std::string optionName, float & value);

    std::vector<std::string> const & getUnnamedArguments();
};
