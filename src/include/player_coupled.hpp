#ifndef PLAYER_COUPLED_HPP
#define PLAYER_COUPLED_HPP

#include <cadmium/modeling/celldevs/asymm/coupled.hpp>

std::shared_ptr<AsymmCell<playerState, double>> addPlayerCell(
        const std::string& cellId, 
        const std::shared_ptr<const AsymmCellConfig<playerState, double>>& cellConfig
    ) {
	auto cellModel = cellConfig->cellModel;

	if (cellModel == "prisoners_dilemma") {
		return std::make_shared<PlayerCell>(cellId, cellConfig);
	} else {
		throw std::bad_typeid();
	}
}

#endif // PLAYER_COUPLED_HPP
