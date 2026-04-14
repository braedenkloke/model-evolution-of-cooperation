#ifndef PLAYER_CELL_HPP
#define PLAYER_CELL_HPP

#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "player_state.hpp"

using namespace cadmium::celldevs;

class PlayerCell : public GridCell<playerState, double> {

	public:
	PlayerCell(const std::vector<int>& id, 
           const std::shared_ptr<const GridCellConfig<playerState, double>>& config
    ): GridCell<playerState, double>(id, config) { }

	[[nodiscard]] playerState localComputation(
        playerState state,
        const std::unordered_map<std::vector<int>, NeighborData<playerState, double>>& neighborhood
    ) const override {
        // Play the Prisoner's Dilemma with each neighbor, 
        // Prisoner's are assumed to be neighbors of themselves
		for (const auto& [neighborId, neighborData]: neighborhood) {
			auto nState = neighborData.state;
            if (state.cooperate == true && nState->cooperate == true) {
                state.total_payoff += state.r; // Reward
            } else if (state.cooperate == true && nState->cooperate == false) {
                state.total_payoff += state.s; // Sucker's payoff
            } else if (state.cooperate == false && nState->cooperate == true) {
                state.total_payoff += state.t; // Temptation payoff
            } else {
                state.total_payoff += state.p; // Punishment
            }
        }

        // Remove payoff gained from this Prisoner playing against itself
        if (state.cooperate) {
            state.total_payoff -= state.r; // Reward
        } else {
            state.total_payoff -= state.p; // Punishment
        }
		return state;
	}

	[[nodiscard]] double outputDelay(const playerState& state) const override {
		return 1.;
	}
};

#endif // PLAYER_CELL_HPP
