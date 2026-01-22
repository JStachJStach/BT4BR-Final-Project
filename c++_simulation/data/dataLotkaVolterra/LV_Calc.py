import csv
import glob

# Global variables for dataset pooling
rabbit_x = []
rabbit_y = []

fox_x = []
fox_y = []

# Get all csv files
for file_name_str in glob.glob("*.csv"):

    time = []
    rabbits = []
    foxes = []
    
    with open(file_name_str, 'r') as f:
        csv_read = iter(csv.reader(f))
        next(csv_read)
        for row in csv_read:
            time.append(float(row[0]))
            rabbits.append(int(row[2]))
            foxes.append(int(row[3]))



 
    # Calculate change and set up datasets for linear regression
    for i in range(0, len(time)-1):
        if rabbits[i] == 0 or foxes[i] == 0:
            continue
        dt = abs(time[i+1] - time[i])
        y_rabbit = (rabbits[i+1] - rabbits[i]) / (rabbits[i] * dt)
        y_fox    = (foxes[i+1] - foxes[i]) / (foxes[i] * dt)

        rabbit_x.append(foxes[i])
        rabbit_y.append(y_rabbit)

        fox_x.append(rabbits[i])
        fox_y.append(y_fox)

import numpy as np
import matplotlib.pyplot as plt

coef = np.polyfit(rabbit_x,rabbit_y,1)
poly1d_fn = np.poly1d(coef) 

ss_res = np.sum((rabbit_y - poly1d_fn(rabbit_x))**2)
ss_tot = np.sum((rabbit_y - np.mean(rabbit_y))**2)

r2 = 1 - ss_res / ss_tot


plt.plot(rabbit_x,rabbit_y, 'g.', rabbit_x, poly1d_fn(rabbit_x), '--k') #'--k'=black dashed line, 's.' = green dot marker

slope, intercept = coef

alpha = intercept
beta  = -slope

plt.xlabel("Fox Population")
plt.ylabel("Change in rabbit population")
plt.text(
    0.05, 0.95,
    f"$R^2 = {r2:.3f}$",
    transform=plt.gca().transAxes,
    verticalalignment='top' 
)

plt.text(
    0.05, 0.85,
    f"$\\alpha = {alpha:.5f}$",
    transform=plt.gca().transAxes,
    verticalalignment='top'  
)

plt.text(
    0.05, 0.75,
    f"$\\beta = {beta:.5f}$",
    transform=plt.gca().transAxes,
    verticalalignment='top'  
)
plt.savefig("Rabbit_LV.png")
plt.close()


print("alpha =", round(alpha,5))
print("beta  =", round(beta,5))

coef = np.polyfit(fox_x,fox_y,1)
poly1d_fn = np.poly1d(coef) 

slope, intercept = coef

gamma = -intercept
delta  = slope

ss_res = np.sum((fox_y - poly1d_fn(fox_x))**2)
ss_tot = np.sum((fox_y - np.mean(fox_y))**2)

r2 = 1 - ss_res / ss_tot
plt.plot(fox_x,fox_y, 'r.', fox_x, poly1d_fn(fox_x), '--k') #'--k'=black dashed line, 'r.' = red dot marker

plt.xlabel("Rabbit Population")
plt.ylabel("Change in fox population")
plt.text(
    0.05, 0.95,
    f"$R^2 = {r2:.3f}$",
    transform=plt.gca().transAxes,
    verticalalignment='top'
)
plt.text(
    0.05, 0.85,
    f"$\\gamma = {gamma:.5f}$",
    transform=plt.gca().transAxes,
    verticalalignment='top'  
)

plt.text(
    0.05, 0.75,
    f"$\\delta = {delta:.5f}$",
    transform=plt.gca().transAxes,
    verticalalignment='top'  
)
plt.savefig("Fox_LV.png")
plt.close()

print("delta =", round(delta,5))
print("gamma  =", round(gamma,5))