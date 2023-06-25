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
    FileScanner(const Paths& arg_Excludes, boost::optional<std::size_t>& arg_szLevel, std::vector<std::string> arg_masks, boost::optional<std::size_t>& arg_szMinSize);
    ~FileScanner() = default;

    PathGroupedBySize Scan(const Paths& arg_Includes);

private:
    std::unique_ptr<DirFilter> CreateDirFilter(boost::optional<std::size_t>& arg_szLevel, const Paths& arg_Excludes);
    std::unique_ptr<FileFilter> CreateFileFilter(boost::optional<std::size_t>& arg_szMinSize, const std::vector<std::string>& arg_strMasks);

    PathGroupedBySize FindPath(const Paths& arg_includes);
    void DeleteUniqPath(PathGroupedBySize& arg_groupPath);

private:
    std::unique_ptr<DirFilter> m_DirFilter;
    std::unique_ptr<FileFilter> m_FileFilter;
};

#endif //INC_08_HOMEWORK_FS_H
