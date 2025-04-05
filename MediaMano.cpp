#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

struct MediaFile {
    std::string name;
    std::string type;
    uintmax_t size;         // in bytes
    std::string addedDate;

    MediaFile(std::string name, std::string type, uintmax_t size)
        : name(name), type(type), size(size) {
        // Get current time as string
        time_t now = time(0);
        addedDate = ctime(&now);
        addedDate.pop_back(); // remove newline
    }
};

class MediaFileManager {
private:
    std::vector<MediaFile> files;

    bool isMediaType(const std::string& ext) {
        return ext == "mp3" || ext == "mp4" || ext == "jpg" || ext == "png" || ext == "wav";
    }

public:
    void indexFromDirectory(const std::string& path) {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                if (!ext.empty() && ext[0] == '.') ext = ext.substr(1); // remove '.'

                if (isMediaType(ext)) {
                    std::string name = entry.path().stem().string();
                    uintmax_t size = entry.file_size();
                    files.emplace_back(name, ext, size);
                    std::cout << "Indexed: " << name << "." << ext << " (" << size << " bytes)\n";
                }
            }
        }
    }

    void listAllFiles() const {
        std::cout << "\nAll indexed media files:\n";
        for (const auto& file : files) {
            std::cout << "- " << file.name << "." << file.type
                      << " | Size: " << file.size << " bytes"
                      << " | Added: " << file.addedDate << "\n";
        }
    }

    void findByType(const std::string& type) const {
        std::cout << "\nFiles with type '" << type << "':\n";
        for (const auto& file : files) {
            if (file.type == type)
                std::cout << "- " << file.name << "." << file.type << "\n";
        }
    }

    void findByName(const std::string& keyword) const {
        std::cout << "\nFiles matching name keyword '" << keyword << "':\n";
        for (const auto& file : files) {
            if (file.name.find(keyword) != std::string::npos)
                std::cout << "- " << file.name << "." << file.type << "\n";
        }
    }

    void deleteByName(const std::string& name) {
        auto originalSize = files.size();
        files.erase(std::remove_if(files.begin(), files.end(), [&](const MediaFile& file) {
            return file.name == name;
        }), files.end());

        if (files.size() < originalSize)
            std::cout << "Deleted entries with name: " << name << "\n";
        else
            std::cout << "No file found with name: " << name << "\n";
    }

    void sortByName() {
        std::sort(files.begin(), files.end(), [](const MediaFile& a, const MediaFile& b) {
            return a.name < b.name;
        });
        std::cout << "Sorted by name.\n";
    }

    void sortByType() {
        std::sort(files.begin(), files.end(), [](const MediaFile& a, const MediaFile& b) {
            return a.type < b.type;
        });
        std::cout << "Sorted by type.\n";
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream out(filename);
        for (const auto& file : files) {
            out << file.name << "," << file.type << "," << file.size << "," << file.addedDate << "\n";
        }
        std::cout << "Index saved to " << filename << "\n";
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream in(filename);
        std::string line;
        files.clear();
        while (std::getline(in, line)) {
            std::istringstream ss(line);
            std::string name, type, sizeStr, date;
            if (std::getline(ss, name, ',') &&
                std::getline(ss, type, ',') &&
                std::getline(ss, sizeStr, ',') &&
                std::getline(ss, date)) {
                files.emplace_back(name, type, std::stoull(sizeStr));
                files.back().addedDate = date;
            }
        }
        std::cout << "Index loaded from " << filename << "\n";
    }
};

// ----------------------
// Example usage
// ----------------------

int main() {
    MediaFileManager manager;

    std::string path = "./media"; // Change this to your actual media folder
    manager.indexFromDirectory(path);

    manager.listAllFiles();
    manager.findByType("mp3");
    manager.findByName("vacation");
    manager.sortByName();
    manager.listAllFiles();
    manager.deleteByName("party_mix");
    manager.saveToFile("media_index.txt");

    // To test loading:
    // manager.loadFromFile("media_index.txt");

    return 0;
}
