import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import pandas as pd
import subprocess
import time
import csv






path = "simulation.exe"
subprocess.Popen([path])


fig, axes = plt.subplots(2,1)
fig.set_size_inches(5.5, 8.5)
axes[0].clear()
axes[1].clear()

time.sleep(0.5)

def plotting(i):
    time = []
    grass = []
    rabbits = []
    foxes = []
    with open("data/data.csv") as f:
        csv_read = iter(csv.reader(f))
        next(csv_read)
        for row in csv_read:
            time.append(float(row[0]))
            #grass.append(int(row[1]))
            rabbits.append(int(row[2]))
            foxes.append(int(row[3]))
        time.pop(0)
        #grass.pop(0)
        foxes.pop(0)
        rabbits.pop(0)

    axes[0].clear()
    axes[1].clear()
    axes[1].set_xlim(right=1000)
    axes[1].set_ylim(top=1000)

    axes[0].plot(time, foxes, color="orange")
    axes[0].plot(time, rabbits, color="grey")

    axes[1].scatter(foxes, rabbits, c=time, cmap="Greys")

animation_object = animation.FuncAnimation(fig, plotting, interval=100)
plt.show()
