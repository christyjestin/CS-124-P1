import os

dims = [0, 2, 3, 4]
numpoints = [28, 256, 512, 1024, 2048; 4096; 8192; 16384; 32768; 65536; 131072; 262144;]

os.system("make clean")
for dim in dims:
    for n in numpoints:
        os.system("make randmst")
        os.system(f"./randmst 2 {n} {10 if n <= 8192 else 5} {dim} > max_weights.cc")