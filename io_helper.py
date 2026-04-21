import json
import sys
import random
import csv

# Wong, Bang. 2011. Points of view: Color Blindness. Color palette optimized for color-blind individuals
BLACK = [0, 0, 0]
ORANGE = [230, 159, 0]
SKY_BLUE = [86, 180, 233]
BLUISH_GREEN = [0, 158, 115]
YELLOW = [240, 228, 66]
BLUE = [0, 114, 178]
VERMILLION = [213, 94, 0]
REDDISH_PURPLE = [204, 121, 167]
WHITE = [255, 255, 255]

# I/O constants
CONFIG_FILE_SUFFIX = "_config.json"
CONFIG_DIR = "config/"
CONFIG_TEMPLATE = { 
        "scenario": {
            "shape": [4, 4],
            "origin": [0, 0]
        },
        "cells": {
            "default": {
                "delay": "inertial",
                "model": "prisoners_dilemma",
            }
        },
        "viewer": [
            {
                "colors": [
                    BLUE, REDDISH_PURPLE, ORANGE, BLUISH_GREEN, SKY_BLUE,
                    BLACK, YELLOW, VERMILLION, WHITE
                ],
                "breaks": [-0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5],
                "field": "strategy"
            },
            {
                "colors": [
                    BLUE, REDDISH_PURPLE, ORANGE, BLUISH_GREEN, SKY_BLUE,
                    BLACK, YELLOW, VERMILLION, WHITE
              ],
                "breaks": [-0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5],
                "field": "bestStrategy"
            },
            {
                "colors": [ [255, 255, 255], [225, 225, 225], [200, 200, 200], [175, 175, 175],
                          [150, 150, 150], [125, 125, 125], [100, 100, 100], [75, 75, 75],
                          [50, 50, 50],  [25, 25, 25] ],
                "breaks": [0, 400, 800, 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000],
                "field": "totalPayoff"
            } 
        ]
    }

def create_config(out_filename: str, n_dimension: int):
    """
    Creates a config file for an n-by-n matrix cell space.

    Parameters:
    ===========
    out_filename: Filename for the output config file.
    n_dimension: N dimension for the n-by-n matrix.

    Return:
    =======
    Filepath to created config.
    """
    # Cell-space matrix dimensions
    m = n_dimension # Rows
    n = n_dimension # Columns

    # Build initial config
    config = CONFIG_TEMPLATE
    scenario = config["scenario"]
    shape = [m, n]
    scenario["shape"] = shape

    # Populate with cells
    cells = config["cells"]
    for i in range(m):
        for j in range(n):
            cell_id = f"({i},{j})"
            neighborhood = get_neighborhood(i, j, m, n)
            strategy = random_strategy()
            cell = { cell_id: {
                    "state": { "strategy": strategy },
                    "neighborhood": neighborhood
                }
            }
            cells.update(cell)

    config_fp = build_config_filepath(out_filename)
    with open(config_fp, 'w') as f:
        json.dump(config, f, indent=2)

    return config_fp

def get_neighborhood(x, y, m, n, type = "von_neumann", r = 1):
    """
    Returns the neighborhood for a given cell (x,y) in an m-by-n matrix cell space.

    Parameters:
    ===========
    x: Central cell X coordinate
    y: Central cell Y coordinate
    m: Number of rows in the cell space
    n: Number of columns in the cell space
    type: Neighborhood type (Defaults to a Von Neumann neighborhood)
    r: Manhattan distance (Defaults to 1)

    Return:
    =======
    Neighborhood for a cell.
    """
    neighborhood = dict()
    if type == "von_neumann" and r == 1:
        for i in range(r * 2 + 1):
            d_x = x - r + i
            if d_x < 0:
                d_x = m - 1
            elif d_x >= m:
                d_x = 0
            neighborhood.update( {f"({d_x},{y})": 1.0} )

            d_y = y - r + i
            if d_y < 0:
                d_y = n - 1
            elif d_y >= n:
                d_y = 0
            neighborhood.update( {f"({x},{d_y})": 1.0} )

    return neighborhood

def random_strategy():
    return random.randrange(0,8)

def build_config_filepath(filename):
    """
    Builds a config filepath for a given filename formatted as: 
      config/<filename>_config.json
    """
    config_fp = filename.lower()
    config_fp = config_fp.replace(" ", "_")
    if CONFIG_DIR not in config_fp:
        config_fp = CONFIG_DIR + config_fp
    if CONFIG_FILE_SUFFIX not in config_fp:
        config_fp = config_fp + CONFIG_FILE_SUFFIX

    return config_fp

def update_config(log_fp, config_fp, out_filename):
    log_delimiter = ";"
    cell_name_index = 2
    cell_state_index = 4
    best_strategy_index = 1
    best_strategy_by_cell_name = dict()

    
    # Read log; get best strategies for each cell
    with open(log_fp, newline="") as log:
        log_reader = csv.reader(log, delimiter=log_delimiter)

        # Drop headers
        num_headers = 2
        for i in range(num_headers):
            next(log_reader)

        for log_entry in log_reader:
            cell_name = log_entry[cell_name_index]
            cell_state = log_entry[cell_state_index]
            cell_state = cell_state.strip("<>")
            cell_state = cell_state.split(",")
            best_strategy = int(cell_state[best_strategy_index])
            best_strategy_by_cell_name.update({cell_name: best_strategy})
            
    # Update config
    with open(config_fp, "r") as f:
        config = json.load(f)
        cells = config["cells"]
        for cell_name, strategy in best_strategy_by_cell_name.items():
            if cells.get(cell_name) != None:
                cells[cell_name]["state"]["strategy"] = strategy

    out_fp = build_config_filepath(out_filename)
    assert (config_fp != out_fp)
    with open(out_fp, "w") as f:
        json.dump(config, f, indent=2)

    return out_fp
