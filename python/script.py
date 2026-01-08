import matplotlib.pyplot as plt
import pandas as pd
import subprocess
import os

#os.listdir()

#path = "c++_simulation/x64/Debug/simulation.exe"
#subprocess.Popen([path])


print(os.getcwd())


for i in range(10):
    df = pd.read_csv("../data/raw/data.csv")
    plt.plot(df["lastTickTime"], df["Tile::foxCount"], color="orange")
    plt.plot(df["lastTickTime"], df["Tile::rabbitCount"], color="grey")
    plt.plot(df["lastTickTime"], df["Tile::grassCount"], color="green")
    plt.pause(0.5)
plt.show()

