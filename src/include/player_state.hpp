#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <iostream>
#include <nlohmann/json.hpp>

enum Strategy {
    kDefector = 0,
    kSuspDoormat = 1,
    kSuspTFT = 2,
    kSuspCooperator = 3,
    kDeceptiveDefector = 4,
    kGullibleDoormat = 5,
    kTFT = 6,
    kCooperator = 7,
    kNull = 8 // No strategy
};

struct playerState {
    int id; // Unique id for this cell
    enum Strategy strategy, bestStrategy;
    std::map<int,bool> moves; // Maps neighbor cell IDs to their last move
    bool initialMove;
    int r, s, t, p; // Payoff matrix
    int totalPayoff;
    
	// Default constructor function.
	playerState() : totalPayoff(0), r(3), s(0), t(5), p(1), strategy(kDefector), bestStrategy(kNull) {
        id = rand();
    }
};

// Prints the prisoner's state in an output stream.
std::ostream& operator<<(std::ostream& os, const playerState& x) {
	os << "<" << x.strategy << "," << x.bestStrategy << "," << x.totalPayoff << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const playerState& x, const playerState& y) {
	return true; // Gurantees state change
}

// It parses a JSON file and generates the corresponding playerState object.
void from_json(const nlohmann::json& j, playerState& s) {
	j.at("strategy").get_to(s.strategy);
    if (s.strategy == kDefector || s.strategy == kSuspDoormat || s.strategy == kSuspTFT || s.strategy == kSuspCooperator) {
        s.initialMove = false;
    } else {
        s.initialMove = true;
    }
    s.bestStrategy = s.strategy;
}

#endif // PLAYER_STATE_HPP
