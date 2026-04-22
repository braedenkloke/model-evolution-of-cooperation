# The Evolution of Cooperation
Model and simulation of the [Prisoner's Dilemma](https://en.wikipedia.org/wiki/Prisoner's_dilemma) as cellular automata in an asymmetric cell-space.

## Usage
To build the model, run
```
source build.sh
```

To execute an experiment or test, run
```
./bin/prisoners_dilemma config/<filename>_config.json
```

Output is logged to
```
out/<filename>_log.csv
```

The scripts are:
* `create_config.py`: Creates a configuration compatible with the Cell-DEVS Web Viewer.
* `run_experiment.sh`: Creates a configuration and runs a set number of experiments.
* `run_tests.sh`: Runs units tests.
* `run_validation.sh`: Runs validation test.
* `update_config.py`: Given a log and a configuration file, updates the configuration file with the best strategies from the log.

To visualize the output, upload the files `<filename>_config.json` and `<filename>_log.csv` to the [Cell-DEVS Web Viewer](https://devssim.carleton.ca/cell-devs-viewer/).

For a detailed description of the project, see the [report](Report.pdf). Experimental results and animations mentioned in the report can be found in [experiments](/experiments).

## Requirements
* [Cadmium v2](https://github.com/Sasisekhar/cadmium_v2) 

## Further Reading
- [The Philosophical Computer: Exploratory Essays in Philosophical Computer Modeling](https://direct.mit.edu/books/monograph/5400/The-Philosophical-ComputerExploratory-Essays-in)
- [The Evolution of Cooperation](https://en.wikipedia.org/wiki/The_Evolution_of_Cooperation)
- [Asymmetric Cell-DEVS models with the Cadmium Simulator](https://www.sciencedirect.com/science/article/pii/S1569190X22001198)
- [Cadmium and the DEVSsim Server](https://devssim.carleton.ca/)

## License
[MIT](https://choosealicense.com/licenses/mit/)
