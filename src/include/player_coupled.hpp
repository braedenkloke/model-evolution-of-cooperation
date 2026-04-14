#ifndef PLAYER_COUPLED_HPP
#define PLAYER_COUPLED_HPP

#include <cadmium/modeling/celldevs/grid/coupled.hpp>

std::shared_ptr<GridCell<playerState, double>> addPlayerCell(
        const coordinates & cellId, 
        const std::shared_ptr<const GridCellConfig<playerState, double>>& cellConfig
    ) {
	auto cellModel = cellConfig->cellModel;

	if (cellModel == "prisoners_dilemma") {
		return std::make_shared<PlayerCell>(cellId, cellConfig);
	} else {
		throw std::bad_typeid();
	}
}

#endif // PLAYER_COUPLED_HPP
