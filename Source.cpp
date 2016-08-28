#include <string>
#include <iostream>
#include <direct.h>
#include <algorithm>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

int clean_caches();

int main()
{
	return clean_caches();
	return 0;
}

void synchronize_1_by_1(const std::string & from, const std::string & to, const std::string & direpath);

int clean_caches()
{
	return 0;
}

void synchronize_1_by_1(const std::string & from, const std::string & to, const std::string & direpath)
{
	WIN32_FIND_DATA file_data;
	HANDLE file_hand = FindFirstFile("*", &file_data);

	do
	{
		if (file_hand == INVALID_HANDLE_VALUE) continue;
		// A file or a folder is found.

		if (file_data.cFileName == std::string(".") || file_data.cFileName == std::string("..")) continue;
		// It's not "." nor ".."

		std::string foundpath = direpath + "\\" + file_data.cFileName;

		// It's a folder.
		if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			std::string new_folder(foundpath);
			new_folder.replace(new_folder.find(from), from.size(), to);
			if (PathIsDirectory(new_folder.c_str()) == FALSE)
			{
				_mkdir(new_folder.c_str());
			}

			// Do recursive process.
			synchronize_1_by_1(from, to, foundpath);
		}
		// It's a file.
		else
		{
			std::string new_file(foundpath);
			new_file.replace(new_file.find(from), from.size(), to);
			if (PathFileExists(new_file.c_str()) == FALSE)
			{
				std::cout << "copying from " << foundpath << " to " << new_file;
				CopyFile(foundpath.c_str(), new_file.c_str(), TRUE);
			}
		}
	} while (FindNextFile(file_hand, &file_data));

	FindClose(file_hand);   //検索に使用したデータを破棄
}