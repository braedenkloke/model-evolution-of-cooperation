#!/bin/bash

#base_filename='experiment_case_1'
base_filename='experiment_case_2'
n_dimension=64
max_runs=12
init_run_id=00
prev_id=-1

while getopts "i:f:n:m:" opt; do
  case $opt in
    i) init_run_id="$OPTARG" ;;
    f) base_filename="$OPTARG" ;;
	n) n_dimension="$OPTARG" ;;
    m) max_runs="$OPTARG" ;;
	\?) echo "Invalid option: -$OPTARG" ;;
  esac
done

# Build simulator
./build.sh

for i in $(eval echo {$init_run_id..$max_runs}); do
    echo "Starting simulation ${i#0} / ${max_runs} ..."
    config_fp=config/${base_filename}_${i}_config.json

    # Case when starting experiments midway
    if (( ${prev_id#0} < 0)) && ((${init_run_id#0} > 0)); then
        prev_id=$(( ${init_run_id#0} - 1 ))
    fi

    # Create initial config or update existing config
    if (( ${init_run_id#0} == 0 )) && (( ${prev_id#0} < 0)); then 
        python3 create_config.py $config_fp -n ${n_dimension} -s {0..8} -p
    else
        python3 update_config.py out/${base_filename}_${prev_id}_log.csv config/${base_filename}_${prev_id}_config.json $config_fp
    fi

    # Run simulation
    ./bin/prisoners_dilemma $config_fp
    prev_id=$i
done
