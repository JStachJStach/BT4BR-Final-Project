import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import pandas as pd
import subprocess
import time
import csv
path = "simulation.exe"
subprocess.Popen([path])


fig = plt.figure()
ax = fig.add_subplot(1,1,1)
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
    ax.clear()
    ax.plot(time, foxes, color="orange")
    ax.plot(time, rabbits, color="grey")

animation_object = animation.FuncAnimation(fig, plotting, interval=100)
plt.show()


