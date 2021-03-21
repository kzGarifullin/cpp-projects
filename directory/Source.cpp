#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
auto compute_file_size(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_regular_file(path))
	{
		auto file_size = std::filesystem::file_size(path);

		if (file_size != static_cast <uintmax_t> (-1))
		{
			return file_size;
		}
	}

	return static_cast <uintmax_t> (-1);
}

auto compute_directory_size(const std::filesystem::path& path)
{
	uintmax_t size = 0ULL;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (auto const& entry : std::filesystem::recursive_directory_iterator(path))
		{
			if (std::filesystem::is_regular_file(entry.status()) || std::filesystem::is_symlink(entry.status()))
			{
				auto file_size = std::filesystem::file_size(entry);

				if (file_size != static_cast <uintmax_t> (-1))
				{
					size += file_size;
				}
			}
		}
	}

	return size;
}

void view_directory(const std::filesystem::path& path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			auto file_name = entry.path().filename().string();

			std::cout << file_name << std::endl;
			auto ftime = std::filesystem::last_write_time(entry.path());
			//time_t ñftime = std::file_time_type::clock::to_time_t(std::filesystem::last_write_time(entry.path()))
			std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
			std::cout << "File write time is " << std::asctime(std::localtime(&cftime)) << '\n';
		}
	}
}

int main(int argc, char** argv)
{
	system("chcp 1251");

	std::cout << compute_file_size("./Source.cpp") << std::endl;

	std::cout << compute_directory_size(std::filesystem::current_path()) << std::endl;
	std::cout << "//////////////////////";
	//view_directory(std::filesystem::current_path());
	view_directory("C:/Users/user/scikit_learn_data");
	system("pause");

	return EXIT_SUCCESS;
}