import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import subprocess
import time
import csv
import tkinter as tk
import json


def fox_start_num_change(change):
    global fox_start_num
    fox_start_num = change
def rabbit_start_num_change(change):
    global rabbit_start_num
    rabbit_start_num = change

def start():
    with open("settings.json", "r") as f:
        settings_map = json.load(f)
        
        settings_map["tiles"]["definitions"]["fox"]["startAmount"] = int(fox_start_num)
        settings_map["tiles"]["definitions"]["rabbit"]["startAmount"] = int(rabbit_start_num)

    with open("settings.json", "w") as f:
        json.dump(settings_map, f)
        
    subprocess.Popen(["simulation.exe"])

    fox_num_scale.config(state="disabled")
    rabbit_num_scale.config(state="disabled")

    canvas_panel.pack(side="right", fill="both", expand=True)
    global animation_object
    animation_object = animation.FuncAnimation(fig, plotting, interval=100)

def plotting(i):
    time = []
    grass = []
    rabbits = []
    foxes = []
    with open("data/data.csv") as f:
        csv_read = iter(csv.reader(f))
        next(csv_read)
        for row in csv_read:
            if len(row) == 4:
                time.append(float(row[0]))
                #grass.append(int(row[1]))
                rabbits.append(int(row[2]))
                foxes.append(int(row[3]))
    axes[0].clear()
    axes[1].clear()
    
    if foxes[len(foxes)-1] > 400 or rabbits[len(rabbits)-1] > 400:
        axes[1].set_xlim(right=1000)
        axes[1].set_ylim(top=1000)
    else:
        axes[1].set_xlim(right=400)
        axes[1].set_ylim(top=400)

    axes[0].plot(time, foxes, color="orange")
    axes[0].plot(time, rabbits, color="grey")


    axes[1].scatter(foxes[-80:], rabbits[-80:], c=time[-80:], cmap="Greys")




root = tk.Tk()
root.title("Settings and plotting")
root.geometry("800x900")

settings_panel= tk.Frame(root)
settings_panel.pack(side="left", anchor="n")

fox_num_scale = tk.Scale(settings_panel,from_=0,to=100,orient="horizontal",command=fox_start_num_change)
fox_num_scale.set(20)
fox_num_scale.pack()
fox_num_scale_text = tk.Label(settings_panel, text="Number of foxes", font=("Georgia", 10))
fox_num_scale_text.pack()


rabbit_num_scale = tk.Scale(settings_panel,from_=0,to=200,orient="horizontal",command=rabbit_start_num_change)
rabbit_num_scale.set(40)
rabbit_num_scale.pack(pady="10")
rabbit_num_scale_text = tk.Label(settings_panel, text="Number of rabbits", font=("Georgia", 10))
rabbit_num_scale_text.pack()

fig, axes = plt.subplots(2, 1)


canvas = FigureCanvasTkAgg(fig, master=root)
canvas_panel = canvas.get_tk_widget()



confirm_button = tk.Button(settings_panel, text="Confirm settings",font=("Georgia", 8), command=start)
confirm_button.pack(pady="20")
root.mainloop()


