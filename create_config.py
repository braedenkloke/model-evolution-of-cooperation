import sys

import io_helper

if __name__ == "__main__":
    if len(sys.argv) == 1:
        print("Error: Missing output file name")
        exit(1)
    if len(sys.argv) == 2: 
        print("Error: Missing n-dimension for n-by-n matrix")
        exit(1)

    out_filename = sys.argv[1]
    n_dimension = sys.argv[2]

    config_fp = io_helper.create_config(out_filename, int(n_dimension))
    print("Config created: " + config_fp)
