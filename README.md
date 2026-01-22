# Cellular automata simulation of Lotka–Volterra population model

## Project introduction:
For our project, we have prepared program with visual simulation of a simple ecosystem, and bunch functionalities around it.
It features an interactive GUI wherein parameters may be adjusted before running the simulation. Moreover, inside of the GUI appears a real-time rendered plot of the population of the objects included.
Why we have chosen this particular topic? We wanted to test out computer capabilities to fabricate ecosystems, in our example, really trivial one. Ecologists lack clean real-world data in a scale large enough to derive idealised mathematical models able to grasp mass population variations. Heavy computer simulations, due to the ability to create large, parallel processes and easy access to data might give the insight into many real-life problems.
In our simple example, focus is placed on prey-predator population fluctuations described by Lotka-Volterra equations [1]. Read more in "Results and Discussion" section.

## Technologies used:

- C++ 20:
    - [Nlohmann json](https://github.com/nlohmann/json)
    - [Raylib](https://www.raylib.com/)
- Python:
    - [matplotlib](https://matplotlib.org/)

### Why C++?
C++ was chosen as the language for the simulation due to its extraordinary speed and computational power when compared to Python. Its speed has allowed us to carry out the simulation with a ton of cells. Furthermore, it has also made it possible to visualise the cells moving around with the use of the Raylib library. Moreover, C++ is a language that not only is taught here at the UJ, but it is also a language that the both of us have experience in. 
### Why Python?
Python is a go-to option when it comes to programming GUI with plotting embedded. Although Raylib is efficient and gives a lot of flexibility, programming GUI is a pure spartan work, and is not necesseary to meet our needs. Thus said, we have chosen Tkinter, an easy to use built-in python library, coupled with matplotlib.

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
## Program explaination:
### Settings:
Grid size [integer, 10-180]: Changes the number of cells per row to the selected value. 

- Tick duration [float, 0.01-0.5]: Sets the duration in seconds of each tick to the selected value.

  _Warning: low values (e.g. 0.01, may cause program to run unevenly_

- Number of foxes [integer, 0-100]: Sets the starting number of foxes.

- Numbers of rabbits [integer, 0-200]: Sets the starting number of rabbits. (default = 70) 

- Grass amount [integer, 1-200]: Sets the starting grass amount.

  _Warning: if there is no place to instantiate new object, it is not being created_
  
- Include grass [Boolean]: Include grass or not.

  _Warning: By default it is disabled, this means that rabbits don't need grass to reproduce, assuming, they have sufficient amount of food. Enabling it may be resource consuming._

- Density [integer, 3-10]: Objects need some personal space. When number of objects surrounding meets Density value, it is being destroyed.

- Grass growth rate [integer, 2-20]: Sets the grass spreading speed

### Objects behavior:
Every object has its own place on a grid, and perform action every tick, with the order determined by a randomization algorithm. This action may cause object to move, reproduce and consume simultaneously.
- How do objects move?
    - Foxes: choose random surrounding cell (24 cells) if unprovoked by rabbit, and move if the place is vacant.
    - Rabbits: choose random surrounding cell (8 cells) if unprovoked by fox, and move if the place is vacant.
    - Grass: read "Why our project is flawed" section in "Results and discussion"
- How do objects reproduce?
    - Every object has few variables, these are of the utmost importance:
        - saturation - represents amount of food the object has eaten. Every object start at 0.
        - reproduction saturation - amount of saturation that make an object to reproduce.
        - saturation per food - amount of saturation points that is added after the food is eaten.
        - saturation per tick - amount of saturation points that is added per tick. For the type of object, that is last in the food chain, it should be a positive number.
        - saturation per reproduction, amount of saturation points that is added (it's a negative number) after reproduction.
        - minimum saturation - saturation at which an object dies. Should be negative
- How do objects consume other objects?
    - Foxes: check if rabbit is on the surrounding cell (8 cells) if there is, it moves to this place, rabbit object is destroyed.
    - Rabbits: check if grass is on the surrounding cell (8 cells) if there is, it moves to this place, grass object is destroyed.
## Results and discussion:
To test capabilies of our program we have ran the simulation several times and observed certain constants. LotkaVolterra.py was made to visualise overall fluctuations in the processes
...
...
...

### Why our project is flawed:

Cellular automata, although it is easy to visualise and perform calculations, it is huge simplification. Rules that we have chosen arbitrally, may also be adjusted in a way that doesn't meet our assumptions.

Reproduction system doesn't align with "only simple rules" principle. It was being rewritten multiple times, adding new parts of code, but not revamping whole system. Like sewing patches on worn out clothes until they became only patches. This does not make it possible to explain objects behavior in one sentence using simple terms. It is especially visible in grass behavior that was programmed quickly and uncarefully without any strict plan in mind.

Randomization algorithms cause simulation to look undetermined and chaotic (in a good way), but cellular automata should mostly be based on strict deterministic rules to easly follow extrapolations from small scale to large scale. It is also important for reproducibility reasons.

Bad file management, mostly due to a fact that we, the creators, have completely unlike workflows, been using seperate IDEs and operating systems (Jakub: Visual Studio and Visual Studio code on Windows, Bartosz: CLion and Pycharm on Linux) 

Described above dichotomy is also manifesting in the code. Every time each of us has been trying to compile freshely pulled frieds commitmennt, it was full of bugs and compilations errors. This is the reason for many try/catch, try/except statements and conditional instructions used to prevent it. But every cloud has a silver lining, our program may be ran successfully on both Windows and Linux.

Bad code management, multiple variables declared but never used, files such as settings.json containing obsolete information.

### Known bugs:

Windows version of the program isn't the latest and function meant to create setting_used.json file is obsolete.

### AI disclaimer:
We have been using AI LLMs such as ChatGPT in these cases:
- Jakub: getting help understanding some compilation errors, *.vcxproj files management and corrections, getting help in building standalone .exe file using Visual Studio.  

## Further reading and inspirations:

[1] <https://en.wikipedia.org/wiki/Lotka–Volterra_equations>

Insight into real-life example:

<https://besjournals.onlinelibrary.wiley.com/doi/10.1111/j.1365-2656.2005.00977.x>

Similar projects:

<http://en.alife.pl/predators-and-prey-the-Lotka-Volterra-model>

<https://youtu.be/sGKiTL_Es9w?si=9HQs78u29Kml01Jf>

Well made video being an introduction to the topic:

<https://www.youtube.com/watch?v=fW_Df8bytIU>





