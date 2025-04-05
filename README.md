# MediaMano
## Media File Manager (C++)

**Media File Manager** is a lightweight terminal-based application written in modern C++. It allows users to index, manage, and retrieve media files from a specified directory. This utility supports file searching, sorting, deletion, and persistent saving/loading of the file index.

## Features

- Index media files (`.mp3`, `.mp4`, `.jpg`, `.png`, `.wav`) from a given folder
- Search files by name or type
- Delete files from the index by name
- Sort files by name or media type
- Save the indexed data to a file
- Load indexed data from a file
- Stores basic metadata such as file size and date added

## Requirements

- C++17 or higher
- A C++17-compliant compiler (e.g., GCC, Clang, MSVC)
- Compatible with Linux, macOS, and Windows

## Setup and Compilation

### Clone the Repository

```bash
git clone https://github.com/your-username/media-file-manager.git
cd media-file-manager
```

### Compile the Code

```bash
g++ -std=c++17 MediaFileManager.cpp -o media_manager
```

### Run the Program

```bash
./media_manager
```

> Note: The program uses a directory path (`./media`) by default. You can modify the `path` variable in the `main()` function to suit your environment.

## Example Directory Structure

```
media/
├── summer_vacation.mp4
├── party_mix.mp3
├── family_photo.jpg
└── interview.wav
```

## Example Output

```
Indexed: summer_vacation.mp4 (2039487 bytes)
Indexed: party_mix.mp3 (934857 bytes)
Indexed: family_photo.jpg (129384 bytes)

All indexed media files:
- summer_vacation.mp4 | Size: 2039487 bytes | Added: Sat Apr 5 2025
- party_mix.mp3        | Size: 934857 bytes  | Added: Sat Apr 5 2025
- family_photo.jpg     | Size: 129384 bytes  | Added: Sat Apr 5 2025
```

## Project Structure

```
.
├── MediaFileManager.cpp   # Main source file
├── media/                 # Example media directory (user-provided)
├── media_index.txt        # (Optional) File for saving/loading index
└── README.md              # Project documentation
```

## Future Enhancements

- Integration with TagLib or FFmpeg for richer metadata extraction (e.g., duration, artist)
- Real-time monitoring of directory changes
- Graphical user interface using Qt or ImGui
- Thumbnail preview for image files
- REST API or Web interface for remote control

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contributing

Contributions are welcome. If you encounter a bug or have suggestions for improvements, feel free to open an issue or submit a pull request.

## Contact

For questions, support, or collaboration opportunities, please use the GitHub Issues section or reach out directly through your preferred communication method.
