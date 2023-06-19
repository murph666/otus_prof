//
// Created by murph on 17.06.23.
//

#ifndef INC_08_HOMEWORK_NAMESPACE_H
#define INC_08_HOMEWORK_NAMESPACE_H
#include <set>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/function.hpp>

using Path = boost::filesystem::path;
using Paths = std::vector<boost::filesystem::path>;
using ScanPath = std::pair<boost::filesystem::path, std::size_t>;

using UniquePaths = std::set<Path>;
using PathGroupedBySize = std::unordered_map< std::size_t, UniquePaths >;

using PathDataRead = std::pair<std::fstream, std::size_t>;
using PathGroupedForRead = std::unordered_map<std::string, PathDataRead> ;
using PathGroupedByDup = std::list<Paths>;

using HashFunc_t = boost::function<std::size_t (char*, std::size_t)>;

#endif //INC_08_HOMEWORK_NAMESPACE_H
