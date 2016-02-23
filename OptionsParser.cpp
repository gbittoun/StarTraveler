#include <iostream>

#include "OptionsParser.h"


bool startsWith(std::string str1, std::string str2)
{
    auto it1 = str1.begin();
    auto it2 = str2.begin();

    while (it1 != str1.end() && it2 != str2.end())
    {
        if (*it1 != *it2)
            return false;

        ++it1, ++it2;
    }

    return true;
}

OptionsParser::OptionsParser(int ac, char **argv)
{
    for (int i = 1 ; i < ac ; ++i)
    {
        std::string arg(argv[i]);

        if (startsWith(arg, "--"))
        {
            arg.erase(0, 2);
        }
        else if (startsWith(arg, "-"))
        {
            arg.erase(0, 1);
        }
        else
        {
            unNamedArguments.push_back(arg);
            continue;
        }

        if (i + 1 < ac)
            namedArguments[arg] = std::string(argv[i + 1]);
        else
            namedArguments[arg];
    }
}

bool OptionsParser::checkOptions(std::string optionName)
{
    return namedArguments.find(optionName) != namedArguments.end();
}

bool OptionsParser::tryGetInt(std::string optionName, int & value)
{
    if (namedArguments.find(optionName) != namedArguments.end())
    {
        try
        {
            value = std::stoi(namedArguments[optionName]);
            return true;
        }
        catch (std::exception & e)
        {
            std::cerr << "Invalid conversion to int for parameter `" << optionName << "`" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    return false;
}

bool OptionsParser::tryGetFloat(std::string optionName, float & value)
{
    if (namedArguments.find(optionName) != namedArguments.end())
    {
        try
        {
            value = std::stof(namedArguments[optionName]);
            return true;
        }
        catch (std::exception & e)
        {
            std::cerr << "Invalid conversion to float for parameter `" << optionName << "`" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    return false;
}

std::vector<std::string> const & OptionsParser::getUnnamedArguments()
{
    return unNamedArguments;
}
