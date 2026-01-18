import sys
import matplotlib.pyplot as plt
import numpy as np

# 1. Controllo file di input per evitare crash
if len(sys.argv) < 2:
    print("Errore: Trascina il file .txt sullo script o passalo come argomento!")
    sys.exit(1)

inputfile = sys.argv[1]
data = np.loadtxt(inputfile)

# Supponiamo che:
# data[0:3] siano i vertici A, B, C
# data[3] sia il punto H (piede dell'altezza)
A, B, C = data[0], data[1], data[2]
H = data[3]

plt.figure(figsize=(8, 6))

# --- DISEGNO IL TRIANGOLO ---
# Devo chiudere il triangolo tornando al primo punto (A -> B -> C -> A)
triangolo_x = [A[0], B[0], C[0], A[0]]
triangolo_y = [A[1], B[1], C[1], A[1]]
plt.plot(triangolo_x, triangolo_y, c='blue', label='Lati')

# --- DISEGNO L'ALTEZZA ---
# Supponiamo che l'altezza parta dal vertice C e arrivi in H
plt.plot([C[0], H[0]], [C[1], H[1]], c='red', linestyle='--', label='Altezza')

# --- DISEGNO I PUNTI ---
plt.scatter(data[:,0], data[:,1], c='black', zorder=5)

plt.title('Triangolo e Altezza')
plt.legend()
plt.grid(True)
plt.axis('equal') # Importante per non vedere il triangolo deformato

print("Generazione grafico in corso...")
plt.show()

