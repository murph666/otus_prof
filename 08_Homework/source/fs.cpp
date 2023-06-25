//
// Created by murph on 17.06.23.
//
#include <iostream>
#include "fs.h"

FileScanner::FileScanner(const Paths& arg_Excludes,
                         boost::optional<std::size_t>& arg_szLevel,
                         std::vector<std::string> arg_masks,
                         boost::optional<std::size_t>& arg_szMinSize)
{
    m_DirFilter = CreateDirFilter(arg_szLevel, arg_Excludes);
    m_FileFilter = CreateFileFilter(arg_szMinSize, arg_masks);
}

PathGroupedBySize FileScanner::Scan(const Paths& arg_Includes)
{
    PathGroupedBySize groupPath = FindPath(arg_Includes);
    DeleteUniqPath(groupPath);

    return groupPath;
}

PathGroupedBySize FileScanner::FindPath(const Paths& arg_includes)
{
    PathGroupedBySize resultPaths;

    try {
        for (auto& incPath : arg_includes) {
            if (boost::filesystem::exists(incPath) && boost::filesystem::is_directory(incPath)) {
                boost::filesystem::recursive_directory_iterator iter(incPath), end;
                while (iter != end) {
                    ScanPath scanPath = std::make_pair(iter->path(), iter.depth());
                    if (boost::filesystem::is_directory(iter->path()) && !m_DirFilter->IsValid(scanPath)) {
                        iter.disable_recursion_pending();
                    }
                    else {
                        if ( boost::filesystem::is_regular_file(iter->path()) ) {
                            Path path = iter->path();
                            auto status = boost::filesystem::symlink_status(iter->path());
                            if (status.type() == boost::filesystem::file_type::symlink_file) {
                                auto realPath = boost::filesystem::read_symlink(iter->path());
                                auto parentPath = iter->path().parent_path();
                                path = boost::filesystem::canonical(realPath, parentPath);
                            }

                            if (m_FileFilter->IsValid(path) ) {
                                std::size_t szSize = boost::filesystem::file_size(path);
                                auto& uniquePaths = resultPaths[szSize];
                                uniquePaths.insert(path);
                            }
                        }
                    }

                    boost::system::error_code ec;
                    iter.increment(ec);
                    if (ec) {
                        std::cerr << "Error while accessing: " << iter->path().string() << " :: " << ec.message() << '\n';
                    }
                }
            }
        }
    }
    catch (const std::system_error& ex) {
        std::cerr << "Error: " << ex.what();
    }

    return resultPaths;
}

void FileScanner::DeleteUniqPath(PathGroupedBySize& arg_groupPath)
{
    auto it = arg_groupPath.begin();

    while(it != arg_groupPath.end()) {
        if (it->second.size() < 2) {
            it = arg_groupPath.erase(it);
        }
        else {
            ++it;
        }
    }
}

std::unique_ptr<DirFilter> FileScanner::CreateDirFilter(boost::optional<std::size_t>& arg_szLevel, const Paths& arg_Excludes)
{
    std::size_t szLevel = 0;
    if (arg_szLevel) {
        szLevel = arg_szLevel.get();
    }
    auto levelFilter = std::make_unique<LevelDirFilter>(szLevel);
    auto excludeFilter = std::make_shared<ExcludeDirFilter>(arg_Excludes);
    levelFilter->SetNext(excludeFilter);
    return levelFilter;
}

std::unique_ptr<FileFilter> FileScanner::CreateFileFilter(boost::optional<std::size_t>& arg_szMinSize,
                                                          const std::vector<std::string>& arg_strMasks)
{
    std::size_t szMinSize = 1;
    if (arg_szMinSize) {
        szMinSize = arg_szMinSize.get();
    }
    auto sizeFilter = std::make_unique<SizeFileFilter>(szMinSize);
    auto masksFilter = std::make_shared<MasksFileFilter>(arg_strMasks);
    sizeFilter->SetNext(masksFilter);
    return sizeFilter;
}
