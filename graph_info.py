import os
import sys
from datetime import datetime

dims = [0, 2, 3, 4]
numpoints = [128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144]

if __name__ == "__main__":
    assert len(sys.argv) == 2
    dim = int(sys.argv[1])
    assert dim in dims
    for n in numpoints:
        print(n, dim)
        start_time = datetime.now()
        print("start:" + start_time.strftime("%H:%M:%S"))

        os.system("make clean")
        os.system("make randmst")
        os.system(f"./randmst 2 {n} {10 if n <= 8192 else 5} {dim} > graph_info_{dim}.cc")

        end_time = datetime.now()
        print("end: ", end_time.strftime("%H:%M:%S"))
        print("total time: ", end_time - start_time)