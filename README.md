# Cellular automata simulation of Lotka–Volterra population model

## Project description:

The program is meant to perform a visual simulation of a simple ecosystem with predator-prey dependence. It features an interactive GUI wherein parameters may be adjusted before running the simulation. Moreover, inside of the GUI appears a real-time rendered plot of the population of the cells.

## Technologies used:

- C++
    - [Nlohmann json](https://github.com/nlohmann/json)
    - [Raylib](https://www.raylib.com/)
- Python
    - [matplotlib](https://matplotlib.org/)

## How to run the program?

Make sure python and matplotlib is installed.
You may verify the above are installed by running:
``` bash
python --version
```
after verifying python version >3.0 is installed:
``` bash
python
import matplotlib 
matplotlib.__version__
```
Should any of these dependencies not be installed they may be installed with the following:

### Python:

Ubuntu/Debian:
``` bash
sudo apt install python3
```
Fedora/Red hat:
``` bash
sudo dnf install python3
```
Arch:
``` bash
sudo pacman -S python3
```
Windows:
https://www.geeksforgeeks.org/python/how-to-install-python-on-windows/
### matplotlib:

Ubuntu/Debian:
``` bash
sudo apt-get install python3-matplotlib.
```
Fedora:
``` bash
sudo dnf install python3-matplotlib
```
Red Hat:
``` bash
sudo yum install python3-matplotlib.
```
Arch:
``` bash
sudo pacman -S python3-matplotlib
```
Windows:
``` bash
pip install matplotlib
```

After verifying that the dependencies are installed, run the program with the following commands on Windows or Linux:

``` bash
cd path/to/directory/BT4BR-Final-Project/c++_simulation
python run.py
```

## Manual compilation

Should you require to manually compile the c++ program yourself you may do so by doing the following:
### Linux (tested on Manjaro)

``` bash
cd path/to/directory/BT4BR-Final-Project/c++_simulation
cmake .
cmake --build .
mv ./c++_simulation ./simulation
```
## Windows
Kuba, please add windows instructions

## Further reading and inspirations

Insight into real-life examples:

<https://besjournals.onlinelibrary.wiley.com/doi/10.1111/j.1365-2656.2005.00977.x>

similar projects:

<http://en.alife.pl/predators-and-prey-the-Lotka-Volterra-model>

<https://youtu.be/sGKiTL_Es9w?si=9HQs78u29Kml01Jf>
