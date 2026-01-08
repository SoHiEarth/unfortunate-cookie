#include <iostream>
#include <filesystem>

enum class OperatingSystem {
  Linux,
  MacOS,
  Windows
};

struct UserSystemConfig {
  std::string home_folder_name;
  OperatingSystem os;
};

UserSystemConfig QueryUserSystem() {
  UserSystemConfig config;

  const char* home_directory = nullptr;
#ifdef _WIN32
  home_directory = std::getenv("USERPROFILE");
#else
  home_directory = std::getenv("HOME");
#endif
  if (home_directory) {
    config.home_folder_name = std::filesystem::path(home_directory).filename();
  }

#ifdef __APPLE__
  config.os = OperatingSystem::MacOS;
#elifdef __linux__
  config.os = OperatingSystem::Linux;
#elifdef _WIN32
  config.os = OperatingSystem::Windows;
#endif

  return config;
}

int main() {
  std::cout << "Give me my cookie! (now/nvm): ";
  std::string user_response;
  getline(std::cin, user_response);
  if (user_response != "now") {
    std::cout << "Alright then, disappointing yourself later won't help!";
    return 0;
  }
  auto config = QueryUserSystem();
  // Read message database based on telemetry
  std::cout << "Ominous message awaits you, " << config.home_folder_name << "." << std::endl; 
}
