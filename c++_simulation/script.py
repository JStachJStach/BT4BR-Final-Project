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
def grass_start_num_change(change):
    global grass_start_num
    grass_start_num = change
def grid_size_change(change):
    global grid_size
    grid_size = change
def simulation_speed_change(change):
    global simulation_speed
    simulation_speed = change

def start():
    with open("settings.json", "r") as f:
        settings_map = json.load(f)

        settings_map["tiles"]["definitions"]["fox"]["startAmount"] = int(fox_start_num)
        settings_map["tiles"]["definitions"]["rabbit"]["startAmount"] = int(rabbit_start_num)
        if include_grass_bool_obj.get():
            settings_map["tiles"]["definitions"]["grass"]["startAmount"] = int(grass_start_num)
        else:
            settings_map["tiles"]["definitions"]["grass"]["startAmount"] = 0
        settings_map["grid"]["size"] = int(grid_size)
        settings_map["tick"]["duration"] = float(simulation_speed)


    confirm_button.config(state="disabled")
    
    fox_num_scale.config(state="disabled")
    rabbit_num_scale.config(state="disabled")
    include_grass_button.config(state="disabled")
    grass_num_scale.config(state="disabled")
    grid_size_scale.config(state="disabled")
    simulation_speed_scale.config(state="disabled")


    with open("settings.json", "w") as f:
        json.dump(settings_map, f)

    subprocess.Popen(["simulation.exe"])
    time.sleep(0.6)


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
                if(include_grass_bool_obj.get()):
                    grass.append(int(row[1]))
                rabbits.append(int(row[2]))
                foxes.append(int(row[3]))
    axes[0].clear()
    axes[1].clear()

    if foxes[len(foxes)-1] > 900 or rabbits[len(rabbits)-1] > 900 or int(grid_size) >= 140:
        axes[1].set_xlim(right=2000)
        axes[1].set_ylim(top=2000) 
    elif foxes[len(foxes)-1] > 400 or rabbits[len(rabbits)-1] > 400 or int(grid_size) >= 100:
        axes[1].set_xlim(right=1000)
        axes[1].set_ylim(top=1000)
    else:
        axes[1].set_xlim(right=400)
        axes[1].set_ylim(top=400)

    axes[0].plot(time, foxes, color="orange", label="Fox")
    axes[0].plot(time, rabbits, color="grey", label="Rabbit")
    if(include_grass_bool_obj.get()):
        axes[0].plot(time, grass, color="green", label="Grass")
    axes[0].set_xlabel("Time (in seconds)")
    axes[0].set_ylabel("Population")
    axes[0].legend(loc="upper left")


    axes[1].scatter(foxes[-120:], rabbits[-120:], c=time[-120:], cmap="Oranges")
    axes[1].set_xlabel("Fox population")
    axes[1].set_ylabel("Rabbit population")
    fig.subplots_adjust(left=0.2)




root = tk.Tk()
root.title("Settings and plotting")
root.geometry("800x900")

settings_panel= tk.Frame(root)
settings_panel.pack(side="left", anchor="n")

simulation_section_text = tk.Label(settings_panel, text="Simulation:", font=("Georgia", 13, "bold"))
simulation_section_text.pack()

grid_size_scale = tk.Scale(settings_panel,from_=10,to=180, resolution=10, orient="horizontal",command=grid_size_change)
grid_size_scale.set(80)
grid_size_scale.pack()
grid_size_text = tk.Label(settings_panel, text="Grid size", font=("Georgia", 10))
grid_size_text.pack()

simulation_speed_scale = tk.Scale(settings_panel,from_=0.01,to=0.5, resolution=0.01, orient="horizontal",command=simulation_speed_change)
simulation_speed_scale.set(0.1)
simulation_speed_scale.pack()
simulation_speed_text = tk.Label(settings_panel, text="Tick duration (s)", font=("Georgia", 10))
simulation_speed_text.pack()


Objects_section_text = tk.Label(settings_panel, text="Objects:", font=("Georgia", 13, "bold"))
Objects_section_text.pack()

fox_num_scale = tk.Scale(settings_panel,from_=0,to=100,orient="horizontal",command=fox_start_num_change)
fox_num_scale.set(20)
fox_num_scale.pack()
fox_num_scale_text = tk.Label(settings_panel, text="Number of foxes", font=("Georgia", 10))
fox_num_scale_text.pack()


rabbit_num_scale = tk.Scale(settings_panel,from_=0,to=200,orient="horizontal",command=rabbit_start_num_change)
rabbit_num_scale.set(40)
rabbit_num_scale.pack()
rabbit_num_scale_text = tk.Label(settings_panel, text="Number of rabbits", font=("Georgia", 10))
rabbit_num_scale_text.pack()

include_grass_bool_obj = tk.BooleanVar(value=False)
include_grass_button = tk.Checkbutton(settings_panel, variable=include_grass_bool_obj)
include_grass_button.pack()
include_grass_text = tk.Label(settings_panel, text="Include grass", font=("Georgia", 10))
include_grass_text.pack()

grass_num_scale = tk.Scale(settings_panel,from_=1,to=200,orient="horizontal",command=grass_start_num_change)
grass_num_scale.set(40)
grass_num_scale.pack()
grass_num_scale_text = tk.Label(settings_panel, text="Number of grass", font=("Georgia", 10))
grass_num_scale_text.pack()
grass_num_scale_text2 = tk.Label(settings_panel, font=("Georgia", 8))
grass_num_scale_text2.pack()

plt.style.use("fivethirtyeight")
fig, axes = plt.subplots(2, 1)

canvas = FigureCanvasTkAgg(fig, master=root)
canvas_panel = canvas.get_tk_widget()

confirm_button = tk.Button(settings_panel, text="Run simulation!",font=("Georgia", 8), command=start)
confirm_button.pack(pady="20")
root.mainloop()