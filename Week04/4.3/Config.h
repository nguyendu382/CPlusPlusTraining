#pragma once
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

