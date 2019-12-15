#include <iostream>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <sstream>
#include <array>
using namespace std;

constexpr int TOTAL_DEMOCRATS = 267;
constexpr int TOTAL_REPUBLICANS = 168;
constexpr double IS_DEMOCRAT_PROBABILITY = (double)TOTAL_DEMOCRATS / (TOTAL_DEMOCRATS + TOTAL_REPUBLICANS);     // P(democrat)
constexpr double IS_REPUBLICAN_PROBABILITY = (double)TOTAL_REPUBLICANS / (TOTAL_DEMOCRATS + TOTAL_REPUBLICANS); // P(republican)
const string INPUT_FILE{"house-votes-84.data"};
constexpr int ATTRIBUTE_COUNT = 16;

const array<string, ATTRIBUTE_COUNT> attributes = {
    "HANDICAPPED_INFANTS",
    "WATER_PROJECT_COST_SHARING",
    "ADOPTION_OF_THE_BUDGET_RESOLUTION",
    "PHYSICIAN_FEE_FREEZE",
    "EL_SALVADOR_AID",
    "RELIGIOUS_GROUPS_IN_SCHOOLS",
    "ANTI_SATELLITE_TEST_BAN",
    "AID_TO_NICARAGUAN_CONTRAS",
    "MX_MISSILE",
    "IMMIGRATION",
    "SYNFUELS_CORPORATION_CUTBACK",
    "EDUCATION_SPENDING",
    "SUPERFUND_RIGHT_TO_SUE",
    "CRIME",
    "DUTY_FREE_EXPORTS",
    "EXPORT_ADMINISTRATION_ACT_SOUTH_AFRICA",
};

enum class Class
{
    DEMOCRAT,
    REPUBLICAN
};

enum class AttributeValue
{
    YES,
    NO,
    INDETERMINATE,
};

using AttributeIndex = int;
using Count = int;

AttributeIndex attributeStringToIndex(const string &attribute)
{
    for (int i = 0; i < attributes.size(); ++i)
    {
        if (attributes[i] == attribute)
            return i;
    }

    cerr << "attributeStringToIndex(): Invalid string for attribute! -> [" << attribute << "]" << endl;
    throw "Invalid string for attribute!";
}

AttributeValue attributeStringToEnum(const string &attribute)
{
    if (attribute == "y")
    {
        return AttributeValue::YES;
    }
    else if (attribute == "n")
    {
        return AttributeValue::NO;
    }
    else if (attribute == "?")
    {
        return AttributeValue::INDETERMINATE;
    }
    else
    {
        cerr << "attributeStringToEnum(): Invalid string for attribute! -> [" << attribute << "]" << endl;
        throw "Invalid string for attribute!";
    }
}

Class classStringToEnum(string classStr)
{
    if (classStr == "democrat")
    {
        return Class::DEMOCRAT;
    }
    else if (classStr == "republican")
    {
        return Class::REPUBLICAN;
    }
    else
    {
        cerr << "classStringToEnum(): Invalid string for class! -> " << classStr << endl;
        throw "Invalid string for class!";
    }
}

// With this map, given a class, we can get the count of entries which have a specific value for some attribute
// For example: the number of democrats (class) which have value 'y' for the attribute "WATER_PROJECT_COST_SHARING" (index 1)
// We can get it like this:
// map[Class::Democrats][attributeStringToIndex("WATER_PROJECT_COST_SHARING")][AttributeValue::YES]
// All of this is needed in order to compute the probabilities P(Xi=v|Ck)
unordered_map<Class,
              unordered_map<AttributeIndex,
                            unordered_map<AttributeValue, Count>>>
createStatisticsMapFromStream(istream& is)
{
    unordered_map<Class,
                  unordered_map<AttributeIndex,
                                unordered_map<AttributeValue, Count>>>
        classesCnt;

    // Initialize map with zeros for all
    for (int attributeIndex = 0; attributeIndex < ATTRIBUTE_COUNT; attributeIndex++)
    {
        classesCnt[Class::DEMOCRAT][attributeIndex][AttributeValue::YES] = 0;
        classesCnt[Class::DEMOCRAT][attributeIndex][AttributeValue::NO] = 0;
        classesCnt[Class::DEMOCRAT][attributeIndex][AttributeValue::INDETERMINATE] = 0;

        classesCnt[Class::REPUBLICAN][attributeIndex][AttributeValue::YES] = 0;
        classesCnt[Class::REPUBLICAN][attributeIndex][AttributeValue::NO] = 0;
        classesCnt[Class::REPUBLICAN][attributeIndex][AttributeValue::INDETERMINATE] = 0;
    }

    string line;
    while (getline(is, line))
    {
        istringstream iss{line};
        string classString;
        while (getline(iss, classString, ','))
        {
            auto classEnum = classStringToEnum(classString);
            for (int attributeIndex = 0; attributeIndex < ATTRIBUTE_COUNT; attributeIndex++)
            {
                string attribute;
                getline(iss, attribute, ',');
                auto attributeValue = attributeStringToEnum(attribute);
                classesCnt[classEnum][attributeIndex][attributeValue]++;
            }
        }
    }

    return classesCnt;
}