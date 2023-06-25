//
// Created by murph on 17.06.23.
//
#include "ds.h"
#include "fstream"

#include "boost/crc.hpp"

DuplicateScan::DuplicateScan(boost::optional<size_t>& arg_szBlockSize, boost::optional<std::string>& arg_strHashAlg)
{
    m_szBlockSize = 1024;
    if (arg_szBlockSize) {
        m_szBlockSize = arg_szBlockSize.get();
    }

    m_hashFunc = CreateHashFunc(arg_strHashAlg);
}

PathGroupedByDup DuplicateScan::Scan(PathGroupedBySize arg_groupPath)
{
    PathGroupedByDup resultPaths;

    for (const auto& group : arg_groupPath) {
        auto findDuplicates = CheckPaths(group.second);
        auto pathGroupedByDup = FormGropByDuplicates(findDuplicates);

        std::copy(pathGroupedByDup.begin(), pathGroupedByDup.end(), std::back_inserter(resultPaths));
    }

    return resultPaths;
}

PathGroupedForRead DuplicateScan::CheckPaths(const UniquePaths& arg_paths)
{
    PathGroupedForRead hashes;

    for (const Path& path : arg_paths) {
        std::string strPath = path.string();
        std::fstream read_stream(strPath, std::fstream::in);
        hashes[strPath] = std::make_pair(std::move(read_stream), 0);
    }

    std::vector<char> buffer(m_szBlockSize);

    bool endFiles = false;
    while (!hashes.empty() && !endFiles) {
        for (auto& elem : hashes) {
            memset(buffer.data(), 0, m_szBlockSize);
            auto& value = elem.second;

            auto readBytes = value.first.readsome(buffer.data(), m_szBlockSize);
            endFiles = static_cast<size_t>(readBytes) < m_szBlockSize;
            value.second = m_hashFunc(buffer.data(), buffer.size());
        }

        auto it = hashes.begin();
        while (it != hashes.end()) {
            size_t szCount = 0;
            size_t curHash = it->second.second;

            std::for_each(hashes.begin(), hashes.end(),
                          [curHash, &szCount](const auto& value)
                          {
                              if (value.second.second == curHash) {
                                  ++szCount;
                              }
                          }
            );

            if (szCount == 1) {
                it = hashes.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    return hashes;
}

PathGroupedByDup DuplicateScan::FormGropByDuplicates(PathGroupedForRead& arg_paths)
{
    PathGroupedByDup result;

    while (!arg_paths.empty()) {
        Paths paths;

        std::size_t curHash = arg_paths.begin()->second.second;
        auto it = arg_paths.begin();
        while (it != arg_paths.end()) {
            if (it->second.second == curHash) {
                paths.emplace_back(it->first);
                it = arg_paths.erase(it);
            }
            else {
                ++it;
            }
        }

        if (!paths.empty()) {
            result.emplace_back(paths);
        }
    }

    return result;
}

HashFunc_t DuplicateScan::CreateHashFunc(boost::optional<std::string>& arg_strHashAlg)
{
    if (arg_strHashAlg) {
        if (arg_strHashAlg.get() == "crc16") {
            return HashFunc<boost::crc_16_type>();
        }
        else if (arg_strHashAlg.get() == "crc32") {
            return HashFunc<boost::crc_32_type>();
        }
    }

    return HashFunc<boost::crc_32_type>();
}



template<typename T>
HashFunc_t DuplicateScan::HashFunc()
{
    return [](char* a_buffer, std::size_t a_szCountBytes)
    {
        T algorithm;
        algorithm.process_bytes(a_buffer, a_szCountBytes);
        return algorithm.checksum();
    };
}