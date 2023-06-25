#include "options.h"
#include "fs.h"
#include "ds.h"

#include "iostream"

int main(int argc, char* argv[]) {

    OptionsParser optionsParser;
    auto options = optionsParser.GetOptions(argc, argv);
    if (!options) {
        return 0;
    }

    FileScanner fileScanner(options.get().excludePaths, options.get().levelScan, options.get().masks, options.get().minFileSize);
    auto groupPath = fileScanner.Scan(options.get().includePaths);

    DuplicateScan dupScanner(options.get().blockSize, options.get().hash);
    auto duplicates = dupScanner.Scan(groupPath);

    for (auto& d : duplicates) {
        for (auto& path : d) {
            std::cout << path << std::endl;
        }
        std::cout << std::endl;
    }
}
