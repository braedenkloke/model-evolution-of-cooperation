#!/bin/bash

base_filename='test_validation_iter'
n_dimension=64
max_runs=20
init_run_id=00
prev_id=-1

while getopts "i:f:n:m:" opt; do
  case $opt in
    i) init_run_id="$OPTARG";;
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

    # Create initial config or update existing config
    if (( ${init_run_id#0} == 0 )) && (( ${prev_id#0} < 0)); then 
        python3 create_config.py $config_fp ${n_dimension}
    else
        python3 update_config.py out/${base_filename}_${prev_id}_log.csv config/${base_filename}_${prev_id}_config.json $config_fp
    fi

    # Run simulation
    ./bin/prisoners_dilemma $config_fp
    prev_id=$i
done
