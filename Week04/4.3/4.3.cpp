#include <iostream>
#include <optional>

struct Config {
	std::optional<std::string> appName;
	std::optional<int> maxConnections;
};
Config loadConfigFromFile() {
	Config config;
	config.appName = "MyServer";
	return config;
}
void printConfig(const Config& config) {
	if (config.appName) {
		std::cout << "App Name: " << *config.appName << std::endl;
	} else {
		std::cout << "App Name: <Not set>" << std::endl;
	}
	if (config.maxConnections) {
		std::cout << "Max Connections: " << *config.maxConnections << std::endl;
	} else {
		std::cout << "Max Connections: <Not set>" << std::endl;
	}
}

int main() {
	Config config = loadConfigFromFile();
	printConfig(config);
	config.maxConnections = 100;
	printConfig(config);
	config.appName = std::nullopt;
	config.maxConnections = std::nullopt;
	printConfig(config);
	return 0;
}