import csv
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import os


def UseDataFromFile(fileName, commonU, commonV, ticks):

    foxes = []
    rabbits = []
    with open (fileName) as f:
        csvRead = iter(csv.reader(f))
        next(csvRead)
        for row in csvRead:
            if len(row) == 4:
                rabbits.append(int(row[2]))
                foxes.append(int(row[3]))

    foxesDiff=np.diff(foxes)
    foxes.pop()
    rabbitsDiff=np.diff(rabbits)
    rabbits.pop()

    foxesDiscrete=[]
    rabbitsDiscrete=[]
    for i in foxes:
        listOfDifferences = []
        for j in ticks:
            listOfDifferences.append(abs(i-j))
        foxesDiscrete.append(ticks[listOfDifferences.index(min(listOfDifferences))])
    for i in rabbits:
        listOfDifferences = []
        for j in ticks:
            listOfDifferences.append(abs(i-j))
        rabbitsDiscrete.append(ticks[listOfDifferences.index(min(listOfDifferences))])


    ticks_vec = np.zeros(len(ticks))
    U, V = np.meshgrid(ticks_vec, ticks_vec)
    foxVectorsInPlace = []
    rabbitVectorsInPlace = []

    for i in range(len(ticks)):
        foxRow = []
        rabbitRow = []
        for j in range(len(ticks)):
            foxRow.append([])
            rabbitRow.append([])
        foxVectorsInPlace.append(foxRow)
        rabbitVectorsInPlace.append(rabbitRow)

    for step in range(len(foxesDiscrete)):
        row = list(ticks).index(rabbitsDiscrete[step])
        column = list(ticks).index(foxesDiscrete[step])
        foxVectorsInPlace[row][column].append(foxesDiff[step])
        rabbitVectorsInPlace[row][column].append(rabbitsDiff[step])
        foxVectorsSum=0
        rabbitVectorsSum=0
        for v in foxVectorsInPlace[row][column]:
            foxVectorsSum += v
        for v in rabbitVectorsInPlace[row][column]:
            rabbitVectorsSum += v
        if len(foxVectorsInPlace[row][column]) != 0 and len(rabbitVectorsInPlace[row][column]) !=0:
            U[row][column] = foxVectorsSum/len(foxVectorsInPlace[row][column])
            V[row][column] = rabbitVectorsSum/len(rabbitVectorsInPlace[row][column])
    commonU += U
    commonV += V
    return commonU, commonV



ticks = np.arange(0, 1000, 25)
X, Y = np.meshgrid(ticks, ticks)
ticks_vec = np.zeros(len(ticks))
U, V = np.meshgrid(ticks_vec, ticks_vec)
folder = "data/dataLotkaVolterra"
for file in os.listdir(folder):
    U, V = UseDataFromFile(folder+"/"+file, U, V, ticks)
L = np.sqrt(U**2 + V**2)
L[L == 0] = 1
U /= L
V /= L
quiverPlot = plt.quiver(X,Y,U,V,L,norm=colors.LogNorm(vmin=L.min(), vmax=L.max()))
plt.axis([-1, 1001, -1, 1001])
plt.xlabel("Fox population")
plt.ylabel("Rabbit population")
plt.colorbar(quiverPlot, label="Avarage population change")
plt.show()