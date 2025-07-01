#include <iostream>
#include <variant>

struct Start {};
struct Stop {};
struct Pause {};
using Command = std::variant<Start, Stop, Pause>;

void dispatchCommand(const Command& cmd) {
	std::visit([](const auto& command) {
		using T = std::decay_t<decltype(command)>;
		if constexpr (std::is_same_v<T, Start>) {
			std::cout << "Starting..." << std::endl;
		} else if constexpr (std::is_same_v<T, Stop>) {
			std::cout << "Stopping..." << std::endl;
		} else if constexpr (std::is_same_v<T, Pause>) {
			std::cout << "Paused" << std::endl;
		}
	}, cmd);
}

int main() {
	Command startCmd = Start{};
	Command stopCmd = Stop{};
	Command pauseCmd = Pause{};
	dispatchCommand(startCmd);
	dispatchCommand(stopCmd);
	dispatchCommand(pauseCmd);
	return 0;
}