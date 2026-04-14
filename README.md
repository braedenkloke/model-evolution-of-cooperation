# Spatialized Prisoner's Dilemma
Model and simulation of the Prisoner's Dilemma as cellular automata in a grid cell space. Implemented with Cell-DEVS and Cadmium.

## Usage
To build the model, run
```
source build.sh
```

To execute an experiment or test, run
```
./bin/prisoners_dilemma config/<config_file>
```

Output is logged to
```
grid_log.csv
```

To visualize the output, upload the files `<config_file>` and `grid_log.csv` to the [DEVS Web Viewer](https://devssim.carleton.ca/cell-devs-viewer/).

For a detailed description of the project, see the [report](Report.pdf).

## Requirements
* [Cadmium v2](https://github.com/Sasisekhar/cadmium_v2) 

## Further Reading
- [The Philosophical Computer: Exploratory Essays in Philosophical Computer Modeling](https://direct.mit.edu/books/monograph/5400/The-Philosophical-ComputerExploratory-Essays-in)
- [The Evolution of Cooperation](https://en.wikipedia.org/wiki/The_Evolution_of_Cooperation)
- [Cadmium and the DEVSsim Server](https://devssim.carleton.ca/): Two tools for discrete-event modeling and simulation.

## License
[MIT](https://choosealicense.com/licenses/mit/)
