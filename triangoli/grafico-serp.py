# import pandas as pd
import sys, os
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

inputfile = sys.argv[1]
# attenzione: crasha se non ha il file come argomento
if not os.path.exists(inputfile): 
    print(f"Il file {inputfile} non esiste")
    sys.exit(1)

data = np.loadtxt(inputfile)

plt.figure(figsize=(8, 6))
plt.scatter(data[:,0], data[:,1], s=1, c='blue', alpha=0.6)
plt.title('Triangolo di Serpinski')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)

print("Generazione grafico in corso...")
plt.savefig(f"triangolo-{str(datetime.now().timestamp())}.jpg")
plt.show()

# plt.scatter(data[:,0], data[:,1])
# plt.show()