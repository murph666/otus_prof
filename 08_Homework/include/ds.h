//
// Created by murph on 17.06.23.
//

#ifndef INC_08_HOMEWORK_DS_H
#define INC_08_HOMEWORK_DS_H

#include "namespace.h"

#include <boost/optional.hpp>
#include <boost/function.hpp>



class DuplicateScan
{
public:
    DuplicateScan(boost::optional<std::size_t>& arg_szBlockSize, boost::optional<std::string>& arg_strHashAlg);

    PathGroupedByDup Scan(PathGroupedBySize arg_groupPath);

private:
    PathGroupedForRead CheckPaths(const UniquePaths& arg_paths);
    PathGroupedByDup FormGropByDuplicates(PathGroupedForRead& arg_paths);

    static HashFunc_t CreateHashFunc(boost::optional<std::string>& arg_strHashAlg);

    template<typename T>
    static HashFunc_t HashFunc();

private:
    std::size_t m_szBlockSize;
    HashFunc_t m_hashFunc;
};

#endif //INC_08_HOMEWORK_DS_H
