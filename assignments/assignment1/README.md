# Assignment 1

## Introduction

To prepare for your first assignment, you might want to download and modify a sample program.
The source code is available in C ([`leapint.c`](leapint.c)) and in Python ([`leapint.py`](leapint.py)). 
To compile the C program, use the command

```bash
gcc -lm -o leapint leapint.c
```

This compilation command creates the executable `leapint`.
The `-lm` links the math libraries during compilation.
To run the compiled program, use the command

```bash
./leapint
```

Alternatively, you can use the python program
```bash
python leapint.py
```

The output consists of four columns, listing (1) time, (2) point index, (3) position `x`, and (4) velocity `v`.
Running the program as supplied yields the trajectory of a point starting at `(X0, V0) = (1, 0)` in the phase space of `(x, v)`, defined by the linear pendulum, or equivalent simple harmonic oscillator, `a(x) = -x`.
The total number of steps taken, number of steps between outputs, and time step used are determined by the parameters `mstep`, `nout`, `dt`, respectively.
These parameters are set in the main procedure of the program.

## Problem 1 (141/241)
(a) Modify the statements which set up initial conditions in the main program to produce trajectories starting from the points `(2, 0)` and `(0, 3)`.
On the `(x, v)` plane, plot these trajectories (e.g. Matplotlib, or your favorite plotting platform) together with the one starting from `(1, 0)`.

(b) Replace the linear pendulum in the `accel` routine with the "nonlinear pendulum", `a(x) = -sin(x)`, and again plot trajectories starting from the points `(1, 0)`, `(2, 0)`, and `(0, 3)`. 

(c) Animate the phase space motion for the three trajectories simultaneously.

(d) Make two-dimensional `(x, v)` plots and three-dimensional `(x, v, t)` plots for (a) and (b).

## Problem 2 (141/241)
(a) Write leapfrog code for Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto, orbiting around the Sun.
Put the Sun at the origin of your coordinate system.
Do some web-based research for setting up the initial conditions to have realistic scales of the orbits.
Help and links will be provided during lectures and labs.
Ignore the interactions of the planets in the time integration and keep the Sun fixed at the origin.

(b) Make a composite plot of all the planetary orbits you calculated.

## Problem 3 (141/241)
(a) Compare your numerically integrated orbits to the analytic form of the elliptic orbits for Earth and Mars.
Investigate the error behavior over the growing number of revolutions of the planets.
Do you detect a deterioration with the number of revolutions growing?

(b) For the two planets, plot the numerically integrated orbit and the analytic elliptic orbit on the same plot.
Each planet will have its own plot.

(c) Animate Earth's motion in Matplotlib (or some other application of your choice) over many revolutions.

## Problem 4 (for Physics 141/241)
Prove the exact conservation of angular momentum of the discretized leapfrog-Verlet algorithm on Kepler orbits.

## Problem 5 (for Physics 241 only)
Calculate and plot the orbit of the Halley comet (read about the comet and its orbit in [Wikipedia](https://en.wikipedia.org/wiki/Halley%27s_Comet)).

## Problem 6 (for Physics 241 only)
Put the Halley comet and Earth in the same animation and demonstrate one full Halley year.
See [Wikipedia](https://en.wikipedia.org/wiki/Halley%27s_Comet) and the [comet table](https://en.wikipedia.org/wiki/List_of_numbered_comets) for more information.


## Additional resources
- [Tutorial for Leapfrog Integration](leapfrog.pdf)
- [Leapfrog Python tutorial](http://cvarin.github.io/CSci-Survival-Guide/leapfrog.html)
- [Kepler orbit tutorial](kepler.pdf)
- [kepler_py.pdf](kepler_py.pdf)
- [stoermer-verlet.pdf](stoermer-verlet.pdf)