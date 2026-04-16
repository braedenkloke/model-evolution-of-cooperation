#ifndef PLAYER_CELL_HPP
#define PLAYER_CELL_HPP

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
        // Play the Prisoner's Dilemma with each neighbor, 
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
        state.count += 1;
		return state;
	}

	[[nodiscard]] double outputDelay(const playerState& state) const override {
		return 1.;
	}
};

#endif // PLAYER_CELL_HPP
