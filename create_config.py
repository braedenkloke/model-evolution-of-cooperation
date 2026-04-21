import argparse

import io_helper

if __name__ == "__main__":
    cli = argparse.ArgumentParser()
    cli.add_argument(
        'out_filename'
    )
    cli.add_argument(
        '-n',
        type=int,
        default=64
    )
    cli.add_argument(
        '-s', 
        '--strategies',
        nargs='*',
        type=int,
        default=[0, 1, 2, 3, 4, 5, 6, 7]
    )
    args = cli.parse_args()

    config_fp = io_helper.create_config(args.out_filename, args.n, args.strategies)
    print("Config created: " + config_fp)
