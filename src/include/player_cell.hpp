#ifndef PLAYER_CELL_HPP
#define PLAYER_CELL_HPP

#include <cassert>

#include <cadmium/modeling/celldevs/asymm/cell.hpp>
#include <cadmium/modeling/celldevs/asymm/config.hpp>
#include "player_state.hpp"

using namespace cadmium::celldevs;

class PlayerCell : public AsymmCell<playerState, double> {

	public:
	PlayerCell(const std::string& id, 
               const std::shared_ptr<const AsymmCellConfig<playerState, double>>& config
    ): AsymmCell<playerState, double>(id, config) { }

	[[nodiscard]] playerState localComputation(
        playerState state,
        const std::unordered_map<std::string, NeighborData<playerState, double>>& neighborhood
    ) const override {
        // Play the Prisoner's Dilemma with each neighbor
		for (const auto& [neighborId, neighborData]: neighborhood) {
            bool a, b;
			auto nState = neighborData.state;
            assert(nState->strategy != kNull);

            // Player A gets next move to make against Player B
            if (state.moves.contains(nState->id)) {
                a = state.moves[nState->id];
            } else {
                a = state.initialMove;
            } 

            // Player B gets next move to make against Player A
            if (nState->moves.contains(state.id)) {
                auto nMoves = nState->moves;
                b = nMoves[state.id];
            } else {
                b = nState->initialMove;
            }

            if (a == true && b == true) {
                state.totalPayoff += state.r; // Reward payoff
            } else if (a == true && b == false) {
                state.totalPayoff += state.s; // Sucker's payoff
            } else if (a == false && b == true) {
                state.totalPayoff += state.t; // Temptation payoff
            } else {
                state.totalPayoff += state.p; // Punishment payoff
            }

            // Plan next move based on opponent's move
            bool opponentCooperates = b;
            bool reaction = true;
            if (state.strategy == kDefector || state.strategy == kDeceptiveDefector) {
                reaction = false;
            } else if (state.strategy == kSuspDoormat || state.strategy == kGullibleDoormat) {
                if (opponentCooperates) {
                    reaction = false;
                } 
            } else if (state.strategy == kSuspTFT || state.strategy == kTFT) {
                if (!opponentCooperates) {
                    reaction = false;
                } 
            } 
            state.moves[nState->id] = reaction;
        }

        // After playing each neighbor, determine best strategy among them
        int max = state.totalPayoff;
        for (const auto& [nId, nData]: neighborhood) {
            auto nState = nData.state;
            if (nState->totalPayoff > max) {
                max = nState->totalPayoff;
                state.bestStrategy = nState->strategy;
            }
        }
		return state;
	}

	[[nodiscard]] double outputDelay(const playerState& state) const override {
		return 1.;
	}
};

#endif // PLAYER_CELL_HPP
