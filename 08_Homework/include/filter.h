//
// Created by murph on 17.06.23.
//

#ifndef INC_08_HOMEWORK_FILTER_H
#define INC_08_HOMEWORK_FILTER_H

#include "namespace.h"
#include "mask.h"

#include <memory>

class DirFilter
{
public:
    virtual std::shared_ptr<DirFilter>& SetNext(const std::shared_ptr<DirFilter>& a_dirFilter) = 0;
    virtual bool IsValid(const ScanPath& a_path) = 0;
};

class FileFilter
{
public:
    virtual std::shared_ptr<FileFilter>& SetNext(const std::shared_ptr<FileFilter>& a_dirFilter) = 0;
    virtual bool IsValid(const Path& a_path) = 0;
};


class BaseDirFilter : public DirFilter
{
public:
    BaseDirFilter()
    { }

    std::shared_ptr<DirFilter>& SetNext(const std::shared_ptr<DirFilter>& a_dirFilter) override
    {
        this->nextDirFilter = a_dirFilter;
        return nextDirFilter;
    }

    bool IsValid(const ScanPath& a_path) override
    {
        if ( nextDirFilter ) {
            return nextDirFilter->IsValid(a_path);
        }

        return true;
    }

private:
    std::shared_ptr<DirFilter> nextDirFilter;
};

class LevelDirFilter : public BaseDirFilter
{
public:
    LevelDirFilter(std::size_t a_szLevel)
            : BaseDirFilter()
            , m_szLevel(a_szLevel)
    { }

    bool IsValid(const ScanPath& a_path) override
    {
        if (a_path.second >= m_szLevel) {;
            return false;
        }
        return BaseDirFilter::IsValid(a_path);
    }

private:
    std::size_t m_szLevel;
};

class ExcludeDirFilter : public BaseDirFilter
{
public:
    ExcludeDirFilter(const Paths& a_excludePaths)
            : BaseDirFilter()
            , m_excludePaths(a_excludePaths)
    { }

    bool IsValid(const ScanPath& a_path) override
    {
        if (!m_excludePaths.empty()) {
            auto path = a_path.first;
            auto it = std::find_if(m_excludePaths.begin(), m_excludePaths.end(),
                                   [path](const boost::filesystem::path& exclude_path) {
                                       return path == exclude_path;
                                   }
            );

            if (it != m_excludePaths.end()) {
                return false;
            }
        }

        return BaseDirFilter::IsValid(a_path);
    }

private:
    Paths m_excludePaths;
};


class BaseFileFilter : public FileFilter
{
public:
    BaseFileFilter()
    { }

    std::shared_ptr<FileFilter>& SetNext(const std::shared_ptr<FileFilter>& a_fileFilter) override
    {
        this->nextFileFilter = a_fileFilter;
        return nextFileFilter;
    }

    bool IsValid(const Path& a_path) override
    {
        if ( nextFileFilter ) {
            return nextFileFilter->IsValid(a_path);
        }
        return true;
    }

private:
    std::shared_ptr<FileFilter> nextFileFilter;
};

class SizeFileFilter : public BaseFileFilter
{
public:
    SizeFileFilter(std::size_t a_szSize)
            : BaseFileFilter()
            , m_szSize(a_szSize)
    { }

    bool IsValid(const Path& a_path) override
    {
        if (boost::filesystem::file_size(a_path) < m_szSize) {;
            return false;
        }
        return BaseFileFilter::IsValid(a_path);
    }

private:
    std::size_t m_szSize;
};

class MasksFileFilter : public BaseFileFilter
{
public:
    MasksFileFilter(const std::vector<std::string>& a_vstrMasks)
            : BaseFileFilter()
    {
        for (auto& mask : a_vstrMasks) {
            m_masks.emplace_back(Mask(mask));
        }
    }

    bool IsValid(const Path& a_path) override
    {
        if (!m_masks.empty()) {
            auto filename = a_path.filename().string();
            return std::any_of(m_masks.begin(), m_masks.end(),
                               [filename](Mask& mask) {
                                   return mask.Valid(filename);
                               }
            );
        }
        return BaseFileFilter::IsValid(a_path);
    }

private:
    std::vector<Mask> m_masks;
};

#endif //INC_08_HOMEWORK_FILTER_H
