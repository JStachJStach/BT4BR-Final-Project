import matplotlib.pyplot as plt
import pandas as pd

for i in range(10):
    df = pd.read_csv("data/raw/data.csv")
    plt.plot(df["lastTickTime"], df["Tile::grass_count"], color="green")
    plt.plot(df["lastTickTime"], df["Tile::fox_count"], color="orange")
    plt.pause(0.5)
plt.show()
