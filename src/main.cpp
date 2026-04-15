#include <cassert>

#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>

#include "include/player_cell.hpp"
#include "include/player_coupled.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;

int main(int argc, char ** argv) {
    std::string configDir = "config/";
    std::string outDir = "out/";
    std::string configFileSuffix = "_config.json";
    std::string logFileSuffix = "_log.csv";

    // Parse arguments
	if (argc < 2) {
		std::cout << "Program used with wrong parameters. The program must be invoked as follows:";
		std::cout << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 200)]" << std::endl;
		return -1;
	}
	std::string configFilePath = argv[1];
	double simTime = (argc > 2)? std::stod(argv[2]) : 200;

    // Create simulation log filename; replace config/<filename>_config.json with out/<filename>_log.csv
    assert(configFilePath.find(configDir) >= 0);
    assert(configFilePath.find(configFileSuffix) >= 0);
    std::string outFilePath = configFilePath;
    outFilePath.replace(0, configDir.length(), outDir);
    outFilePath.replace(outFilePath.length() - configFileSuffix.length(), 
                        configFileSuffix.length(), 
                        logFileSuffix
    );

    // Build model
	auto model = std::make_shared<AsymmCellDEVSCoupled<playerState, double>>(
        "prisoners_dilemma", 
        addPlayerCell, 
        configFilePath
    );
	model->buildModel();
	
    // Configure and run simulation
	auto rootCoordinator = RootCoordinator(model);
	rootCoordinator.setLogger<CSVLogger>(outFilePath, ";");
	rootCoordinator.start();
	rootCoordinator.simulate(simTime);
	rootCoordinator.stop();

    std::cout << "Simulation logs: " << outFilePath << "\n";
}
