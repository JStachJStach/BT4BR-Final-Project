# Cellular automata simulation of Lotka–Volterra population model

## Project introduction:
For our project, we have prepared program with a visual simulation of a simple ecosystem, and built additional functionalities around it.
It features an interactive GUI wherein parameters may be adjusted before running the simulation. Moreover, inside of the GUI appears a real-time rendered plot of the population of the objects included.
### Why we have chosen this particular topic?
 We wanted to test out computer capabilities to fabricate ecosystems, which in our example is a really trivial one. Ecologists lack clean real-world data in a scale large enough to derive idealised mathematical models able to grasp mass population variations. Heavy computer simulations, due to the ability to create large, parallel processes and easy access to data might give the insight into many real-life problems.
In our simple example, focus is placed on prey-predator population fluctuations described by Lotka-Volterra equations [1], read more in "Results and Discussion" section.

## Technologies used:

- C++
    - [Nlohmann json](https://github.com/nlohmann/json)
    - [Raylib](https://www.raylib.com/)
- Python
    - [matplotlib](https://matplotlib.org/)

### Why C++?
C++ was chosen as the language for the simulation due to its extraordinary speed and computational power when compared to Python. Its speed has allowed us to carry out the simulation with a ton of cells. Furthermore, it has also made it possible to visualise the cells moving around with the use of the Raylib library. Moreover, C++ is a language that not only is taught here at the UJ, but it is also a language that the both of us have experience in. 
### Why Python?
Python is a go-to option when it comes to programming GUI with plotting embedded. Although Raylib is efficient and gives a lot of flexibility, programming GUI is a pure spartan work, and is not neccessary to meet our needs. Thus said, we have chosen Tkinter, an easy to use built-in python library, coupled with matplotlib.

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
Arch:
``` bash
sudo pacman -S python-matplotlib
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
mkdir build
cd build
cmake ..
cmake --build .
mv ./simulation ../simulation
cd ..
```
## Program explaination
### Settings:
Grid size [integer, 10-180]: Changes the number of cells per row to the selected value. 

- Tick duration [float, 0.01-0.5]: Sets the duration in seconds of each tick to the selected value.

  _Warning: low values (e.g. 0.01), may cause program to run unevenly_

- Number of foxes [integer, 0-100]: Sets the starting number of foxes.

- Numbers of rabbits [integer, 0-200]: Sets the starting number of rabbits. (default = 70) 

- Grass amount [integer, 1-200]: Sets the starting grass amount.

  _Warning: if there is no place to instantiate new object, it is not being created_
  
- Include grass [Boolean]: Include grass or not.

  _Warning: By default it is disabled, this means that rabbits don't need grass to reproduce, assuming, they have sufficient amount of food. Enabling it may be resource consuming._

- Density [integer, 3-10]: Objects need some personal space. When number of objects surrounding meets Density value, it is being destroyed.

- Grass growth rate [integer, 2-20]: Sets the grass spreading speed

### Objects behavior


## Results and discussion
To test capabilies of our program we have ran the simulation several times and observe certain constants. LotkaVolterra.py was made to visualise overall fluctuations of the processes

### Why our project is flawed

When it comes to the simulation, the reproduction system doesn't align with the "only simple rules" principle. It was rewritten multiple times, adding new parts of code, but not revamping the entire system. Like sewing patches on worn out clothes until they became only patches. This does not make it possible to explain objects behavior in one sentence using simple terms.

Cellular Automata, although it is easy to visualise and perform calculations, it is a huge simplification. Rules that we have chosen arbitrally, may also be adjusted in a way that doesn't meet our assumptions.

Bad file management, mostly due to a fact that we, the creators, have completely unlike workflows, been using seperate IDEs and operating systems (Jakub: Visual Studio and Visual Studio code on Windows, Bartosz: CLion and Pycharm on Linux) 

The dichotomy described above has also manifested in the code. Every time either of us had tried to compile a freshely pulled commit, it was full of bugs and compilation errors. This is the reason for why many try/catch, try/except statements and conditional instructions were used. But every cloud has a silver lining, our program may be ran successfully on both Windows and Linux.

### AI disclaimer!
We have been using AI LLMs such as ChatGPT in these cases:
- Jakub: getting help understanding some compilation errors, *.vcxproj files management and corrections, getting help in building standalone .exe file using Visual Studio.  
- Bartosz: getting help with errors, CMake, and understanding how to derive the Lotka-Volterra equations.

## Further reading and inspirations

Insight into real-life example:

<https://besjournals.onlinelibrary.wiley.com/doi/10.1111/j.1365-2656.2005.00977.x>

Similar projects:

<http://en.alife.pl/predators-and-prey-the-Lotka-Volterra-model>

<https://youtu.be/sGKiTL_Es9w?si=9HQs78u29Kml01Jf>

Well made video being an introduction to the topic:

<https://www.youtube.com/watch?v=fW_Df8bytIU>

[1] <https://en.wikipedia.org/wiki/Lotka–Volterra_equations>
