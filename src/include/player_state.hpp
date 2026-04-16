#ifndef PLAYER_STATE_HPP
#define PLAYER_STATE_HPP

#include <iostream>
#include <nlohmann/json.hpp>

enum Strategy {
    kDefector = 0,
    kSuspDoormat = 1
};

struct playerState {
	bool cooperate;     // True if prisoner cooperates, false if prisoner defects.
    int totalPayoff;
    int r, s, t, p;     // Payoff matrix
    int count;          // Gurantees state always changes, simulation terminates if state doesn't change
    enum Strategy strategy;
    int id;             // Unique id for this cell, necessary to index moves
    std::map<int,bool> moves; // Maps neighbor cell IDs to their last move
    bool initialMove;
    

	// Default constructor function.
	playerState() : cooperate(false), totalPayoff(0), r(3), s(0), t(5), p(1), count(0), strategy(kDefector) {
        id = rand();
    }
};

// Prints the prisoner's state in an output stream.
std::ostream& operator<<(std::ostream& os, const playerState& x) {
	os << "<" << ((x.cooperate)? 1 : 0) << "," << x.totalPayoff << "," << x.strategy << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const playerState& x, const playerState& y) {
	return x.cooperate != y.cooperate || x.totalPayoff != y.totalPayoff || x.count != y.count;
}

// It parses a JSON file and generates the corresponding playerState object.
void from_json(const nlohmann::json& j, playerState& s) {
	j.at("cooperate").get_to(s.cooperate);
	j.at("strategy").get_to(s.strategy);
    if (s.strategy == kDefector || s.strategy == kSuspDoormat) {
        s.initialMove = false;
    }
}

#endif // PLAYER_STATE_HPP
