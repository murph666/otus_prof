//
// Created by murph on 17.06.23.
//

#ifndef INC_08_HOMEWORK_MASK_H
#define INC_08_HOMEWORK_MASK_H

#include <string>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

class Mask
{
public:
    explicit Mask(const std::string& a_strMask)
    {
        auto strMask = a_strMask;
        EscapeRegex(strMask);
        m_regex = boost::regex(strMask, boost::regex::icase );
    }

    bool Valid(const std::string& a_strValue)
    {
        return boost::regex_match(a_strValue, m_what, m_regex);
    }

private:
    void EscapeRegex(std::string& m_strRegex)
    {
        boost::replace_all(m_strRegex, ".", "\\.");
        boost::replace_all(m_strRegex, "*", "\\*");
        boost::replace_all(m_strRegex, "?", "\\?");
        boost::replace_all(m_strRegex, "\\?", ".");
        boost::replace_all(m_strRegex, "\\*", ".*");
    }

private:
    boost::regex m_regex;
    boost::smatch m_what;
};

#endif //INC_08_HOMEWORK_MASK_H
