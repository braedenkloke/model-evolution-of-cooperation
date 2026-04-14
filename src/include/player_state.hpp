#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <iostream>
#include <nlohmann/json.hpp>

struct playerState {
	bool cooperate; // True if prisoner cooperates, false if prisoner defects.
    int total_payoff;
    int r, s, t, p; // Payoff matrix

	// Default constructor function.
	playerState() : cooperate(false), total_payoff(0), r(3), s(0), t(5), p(1) {}
};

// Prints the prisoner's state in an output stream.
std::ostream& operator<<(std::ostream& os, const playerState& x) {
	os << "<" << ((x.cooperate)? 1 : 0) << "," << x.total_payoff << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const playerState& x, const playerState& y) {
	return x.total_payoff != y.total_payoff;
}

// It parses a JSON file and generates the corresponding playerState object.
void from_json(const nlohmann::json& j, playerState& s) {
	j.at("cooperate").get_to(s.cooperate);
}

#endif // PLAYER_STATE_HPP
