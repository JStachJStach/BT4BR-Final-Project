import signal
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import subprocess
import signal
import time
import csv
import os
import locale
os.environ["LC_NUMERIC"] = "C"
locale.setlocale(locale.LC_NUMERIC, "C")
import json
import tkinter as tk

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
def sparsity_val_change(change):
    global sparsity_val
    sparsity_val = change
def grass_growth_change(change):
    global grass_growth
    grass_growth = change
def rabbit_reproduction_rate_change(change):
    global rabbit_reproduction_rate
    rabbit_reproduction_rate = change
def fox_reproduction_rate_change(change):
    global fox_reproduction_rate
    fox_reproduction_rate = change

def start():
    global simulation_process
    try:

        old = simulation_process
        os.killpg(old.pid, signal.SIGKILL)
        old.wait()
        simulation_process.terminate() #for windows
        print("success")
    except Exception as e:
        print(repr(e))
        confirm_button.config(text="Rerun simulation")
    with open("settings.json", "r") as f:
        settings_map = json.load(f)

        settings_map["tiles"]["definitions"]["fox"]["startAmount"] = int(fox_start_num)
        settings_map["tiles"]["definitions"]["rabbit"]["startAmount"] = int(rabbit_start_num)
        settings_map["animals"]["grass"]["satPerTick"] = int(grass_growth)
        if include_grass_bool_obj.get():
            settings_map["tiles"]["definitions"]["grass"]["startAmount"] = int(grass_start_num)
            settings_map["animals"]["rabbit"]["satPerTick"] = -2
        else:
            settings_map["tiles"]["definitions"]["grass"]["startAmount"] = 0
            settings_map["animals"]["rabbit"]["satPerTick"] = 3

        settings_map["grid"]["size"] = int(grid_size)
        settings_map["tick"]["duration"] = float(simulation_speed)
        settings_map["tiles"]["sparsity"] = int(sparsity_val)
        settings_map["animals"]["fox"]["reproductionSat"] = 20-int(fox_reproduction_rate)###############################################
        settings_map["animals"]["fox"]["maxSat"] = (20-int(fox_reproduction_rate))*2####################################################
        settings_map["animals"]["rabbit"]["reproductionSat"] = 70-int(rabbit_reproduction_rate)#########################################
        settings_map["animals"]["rabbit"]["maxSat"] = (70-int(rabbit_reproduction_rate))*2##############################################
        
    with open("settings.json", "w") as f:
        json.dump(settings_map, f)

    try:
        simulation_process = subprocess.Popen(["simulation.exe"],  start_new_session=True)
    except:
        simulation_process = subprocess.Popen(["./simulation"], start_new_session=True)

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
                grass.append(int(row[1]))
                rabbits.append(int(row[2]))
                foxes.append(int(row[3]))

    axes[0][0].clear()
    axes[0][1].clear()
    axes[1][0].clear()
    axes[1][1].clear()
    
    try:
        if foxes[-1] > 900 or rabbits[-1] > 900 or int(grid_size) >= 150:
            axes[1][0].set_xlim(right=2000)
            axes[1][0].set_ylim(top=2000) 
        elif foxes[-1] > 400 or rabbits[-1] > 400 or int(grid_size) >= 100:
            axes[1][0].set_xlim(right=1000)
            axes[1][0].set_ylim(top=1000)
        else:
            axes[1][0].set_xlim(right=400)
            axes[1][0].set_ylim(top=400)
    except:
        print("")
    
    axes[0][0].plot(time[-1200:], foxes[-1200:], color="orange", label="Fox",linewidth=2)
    axes[0][0].plot(time[-1200:], rabbits[-1200:], color="grey", label="Rabbit",linewidth=2)
    if(include_grass_bool_obj.get()):
        axes[0][0].plot(time[-1200:], grass[-1200:], color="green", label="Grass",linewidth=2)
    axes[0][0].set_xlabel("Time (in seconds)")
    axes[0][0].set_ylabel("Population")
    axes[0][0].legend(loc="upper left")

    axes[1][0].scatter(foxes[-120:], rabbits[-120:], c=time[-120:], cmap="Oranges")
    axes[1][0].set_xlabel("Fox population")
    axes[1][0].set_ylabel("Rabbit population")


    if not include_grass_bool_obj.get():
        axes[0][1].axis("off")
        axes[1][1].axis("off")
    else:
        axes[0][1].axis("on")
        axes[1][1].axis("on")
        axes[0][1].scatter(foxes[-120:], grass[-120:], c=time[-120:], cmap="Greens")
        axes[0][1].set_xlabel("Fox population")
        axes[0][1].set_ylabel("Grass amount")
        try:
            if grass[-1] > 2000 or foxes[-1] > 2000 or int(grid_size) >= 150:
                axes[0][1].set_xlim(right=3000)
                axes[0][1].set_ylim(top=6000) 
            elif grass[-1] > 1000 or foxes[-1] > 500 or int(grid_size) >= 100:
                axes[0][1].set_xlim(right=1500)
                axes[0][1].set_ylim(top=3000)
            else:
                axes[0][1].set_xlim(right=400)
                axes[0][1].set_ylim(top=800)
        except:
            print("")
        axes[1][1].scatter(rabbits[-120:], grass[-120:], c=time[-120:], cmap="Greys")
        axes[1][1].set_xlabel("Rabbit population")
        axes[1][1].set_ylabel("Grass amount")
        try:
            if rabbits[-1] > 2000 or grass[-1] > 2000 or int(grid_size) >= 150:
                axes[1][1].set_xlim(right=3000)
                axes[1][1].set_ylim(top=6000) 
            elif rabbits[-1] > 1000 or grass[-1] > 500 or int(grid_size) >= 100:
                axes[1][1].set_xlim(right=1500)
                axes[1][1].set_ylim(top=3000)
            else:
                axes[1][1].set_xlim(right=400)
                axes[1][1].set_ylim(top=800)
        except:
            print("")




root = tk.Tk()
root.title("Settings and plotting")
root.geometry("1200x900")

settings_panel= tk.Frame(root)
settings_panel.pack(side="left", anchor="n")

simulation_section_text = tk.Label(settings_panel, text="Simulation:", font=("Georgia", 15, "bold"))
simulation_section_text.pack()

grid_size_scale = tk.Scale(settings_panel,from_=10,to=180, resolution=10, orient="horizontal",command=grid_size_change)
grid_size_scale.set(140)
grid_size_scale.pack()
grid_size_text = tk.Label(settings_panel, text="Grid size", font=("Georgia", 12))
grid_size_text.pack()

simulation_speed_scale = tk.Scale(settings_panel,from_=0.01,to=0.5, resolution=0.01, orient="horizontal",command=simulation_speed_change)
simulation_speed_scale.set(0.02)
simulation_speed_scale.pack()
simulation_speed_text = tk.Label(settings_panel, text="Tick duration (s)", font=("Georgia", 12))
simulation_speed_text.pack()


Objects_section_text = tk.Label(settings_panel, text="Start params:", font=("Georgia", 15, "bold"))
Objects_section_text.pack()

fox_num_scale = tk.Scale(settings_panel,from_=0,to=100,orient="horizontal",command=fox_start_num_change)
fox_num_scale.set(70)
fox_num_scale.pack()
fox_num_scale_text = tk.Label(settings_panel, text="Number of foxes", font=("Georgia", 12))
fox_num_scale_text.pack()


rabbit_num_scale = tk.Scale(settings_panel,from_=0,to=200,orient="horizontal",command=rabbit_start_num_change)
rabbit_num_scale.set(140)
rabbit_num_scale.pack()
rabbit_num_scale_text = tk.Label(settings_panel, text="Number of rabbits", font=("Georgia", 12))
rabbit_num_scale_text.pack()

grass_num_scale = tk.Scale(settings_panel,from_=1,to=200,orient="horizontal",command=grass_start_num_change)
grass_num_scale.set(40)
grass_num_scale.pack()
grass_num_scale_text = tk.Label(settings_panel, text="Number of grass", font=("Georgia", 12))
grass_num_scale_text.pack()

include_grass_bool_obj = tk.BooleanVar(value=False)
include_grass_button = tk.Checkbutton(settings_panel, variable=include_grass_bool_obj)
include_grass_button.pack()
include_grass_text = tk.Label(settings_panel, text="Include grass", font=("Georgia", 12))
include_grass_text.pack()
include_grass_text2 = tk.Label(settings_panel, text="Including grass cause\nrabbits to require it\nfor reproduction", font=("Georgia", 10))
include_grass_text2.pack()

Objects_section_text = tk.Label(settings_panel, text="Rules:", font=("Georgia", 15, "bold"))
Objects_section_text.pack()


sparsity_val_scale = tk.Scale(settings_panel,from_=3,to=10,orient="horizontal",command=sparsity_val_change)
sparsity_val_scale.set(5)
sparsity_val_scale.pack()
sparsity_val_scale_text = tk.Label(settings_panel, text="Density", font=("Georgia", 12))
sparsity_val_scale_text.pack()

fox_reproduction_rate_scale = tk.Scale(settings_panel,from_=5, to=15,orient="horizontal",command=fox_reproduction_rate_change)
fox_reproduction_rate_scale.set(10)
fox_reproduction_rate_scale.pack()
fox_reproduction_rate_scale_text = tk.Label(settings_panel,text="Fox reproduction rate", font=("Georgia", 12))
fox_reproduction_rate_scale_text.pack()

rabbit_reproduction_rate_scale = tk.Scale(settings_panel,from_=5, to=50,orient="horizontal",command=rabbit_reproduction_rate_change)
rabbit_reproduction_rate_scale.set(35)
rabbit_reproduction_rate_scale.pack()
rabbit_reproduction_rate_scale_text = tk.Label(settings_panel,text="Rabbit reproduction rate", font=("Georgia", 12))
rabbit_reproduction_rate_scale_text.pack()

grass_growth_scale = tk.Scale(settings_panel,from_=2,to=20,orient="horizontal",command=grass_growth_change)
grass_growth_scale.set(7)
grass_growth_scale.pack()
grass_growth_scale_text = tk.Label(settings_panel, text="Grass growth rate", font=("Georgia", 12))
grass_growth_scale_text.pack()



plt.style.use("fivethirtyeight")
fig, axes = plt.subplots(2, 2)

canvas = FigureCanvasTkAgg(fig, master=root)
canvas_panel = canvas.get_tk_widget()

confirm_button = tk.Button(settings_panel, text="Run simulation",font=("Georgia", 13), command=start)
confirm_button.pack(pady="20")
root.mainloop()