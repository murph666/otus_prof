//
// Created by murph on 17.06.23.
//

#ifndef INC_08_HOMEWORK_FS_H
#define INC_08_HOMEWORK_FS_H

#include "filter.h"
#include "namespace.h"

#include <vector>
#include <string>
#include <memory>
#include <boost/optional.hpp>

class FileScanner
{
public:
    FileScanner(const Paths& a_Excludes, boost::optional<std::size_t>& a_szLevel, std::vector<std::string> a_Masks, boost::optional<std::size_t>& a_szMinSize);
    ~FileScanner() = default;

    PathGroupedBySize Scan(const Paths& a_Includes);

private:
    std::unique_ptr<DirFilter> CreateDirFilter(boost::optional<std::size_t>& a_szLevel, const Paths& a_Excludes);
    std::unique_ptr<FileFilter> CreateFileFilter(boost::optional<std::size_t>& a_szMinSize, const std::vector<std::string>& a_strMasks);

    PathGroupedBySize FindPath(const Paths& a_Includes);
    void DeleteUniqPath(PathGroupedBySize& a_groupPath);

private:
    std::unique_ptr<DirFilter> m_DirFilter;
    std::unique_ptr<FileFilter> m_FileFilter;
};

#endif //INC_08_HOMEWORK_FS_H
