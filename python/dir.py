import os

def scan_dir(dir):
    for filename in os.listdir(dir):
        if filename[0] == '.':
            continue

        path = os.path.join(dir, filename)
        if os.path.isdir(path):
            print(path)
            scan_dir(path)

scan_dir('/home/bs/Pictures')
