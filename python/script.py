import matplotlib.pyplot as plt
import pandas as pd
import subprocess



#path = "c++_simulation/x64/Debug/simulation.exe"
#subprocess.Popen([path])


for i in range(10):
    df = pd.read_csv("data/raw/data.csv")
    plt.plot(df["lastTickTime"], df["Tile::fox_count"], color="orange")
    plt.plot(df["lastTickTime"], df["Tile::rabbit_count"], color="grey")
    plt.plot(df["lastTickTime"], df["Tile::grass_count"], color="green")
    plt.pause(0.5)
plt.show()
