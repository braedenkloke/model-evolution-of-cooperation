import json

def create_config():
    json.dumps(['foo', {'bar': ('baz', None, 1.0, 2)}])
    with open('config/.txt', 'r') as handle:
        parsed = json.load(handle)

if __name__ == "__main__":
    create_config()
