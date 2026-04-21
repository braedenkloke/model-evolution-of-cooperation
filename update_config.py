import sys

import io_helper

if __name__ == "__main__":
    if len(sys.argv) == 1:
        "Error: missing log file path"
        exit(1)
    if len(sys.argv) == 2:
        "Error: missing config file path"
        exit(1)
    if len(sys.argv) == 3:
        "Error: missing output file name"
        exit(1)

    log_fp = sys.argv[1]
    config_fp = sys.argv[2]
    out_filename = sys.argv[3]
    out = io_helper.update_config(log_fp, config_fp, out_filename)
    print("Config updated: " + out)
