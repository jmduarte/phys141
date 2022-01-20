# assignment1

To prepare for your first C code, you might want to download and modify a sample program. The source code is available in C (leapint.c). To compile the program, try to use the command

```bash
gcc -o leapint leapint.c
```

after you located the path to the gcc gnu compiler on the computing platform available to you. This could be your laptop, your workstation at home, the computer lab in Mayer Hall, or a remote computer lab. Sometimes gcc requires the `-lm` linking of the math libraries during compilation: `gcc -lm -o leapint leapint.c`. To run the compiled program, use the command

```bash
leapint
```
## Introduction
Equivalently, you might use the modern clang compiler if you have access to it. It is available in the lab iMAc workstations, or on your Mac laptop or workstation if the Xcode platform is installed under OS X. The clang compiler is popular with its clean and comprehensive error message system. To compile the program with clang, try to use the command

```bash
clang -o leapint leapint.c
```

The output consists of four columns, listing (1) time, (2) point index, (3) position x, and (4) velocity v. Running the program as supplied yields the trajectory of a point starting at (X0,V0) = (1,0) in the phase space flow on (x,v), defined by the linear pendulum, or equivalent harmonic oscillator, a(x) = -x. The total number of steps taken, number of steps between outputs, and timestep used are determined by the parameters mstep, nout, dt, respectively; these parameters are set in the main procedure of the program.

## Problem 1 (141/241)
(a)  Modify the statements which set up initial conditions in the main program to produce trajectories starting from the points (2,0) and (0,3). On the (x,v) plane, plot these trajectories (gnuplot, or your favorite plotting platform) together with the one starting from (1,0).

(b) Replace the linear pendulum in the accel routine with the "nonlinear pendulum", a(x) = -sin(x), and again plot trajectories starting from the points (1,0), (2,0), & (0,3). 

(c) Animate the phase space motion for the three trajectories simultaneously.

(d) Make two-dimensional (x,v) plots and three-dimensional (x,v,t) plots for (a) and (b).

## Problem 2 (141/241)
(a)  Write leapfrog code for Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto, orbiting around the Sun. Put the Sun at the origin of your coordinate system. Do some web based research for setting up the initial conditions to have realistic scales of the orbits. Help and links will be provided in Lecture 4. Ignore the interactions of the planets in the time integration and keep the Sun fixed at the origin.

(b) Make a composite plot of all the planetary orbits you calculated.

## Problem 3 (141/241)
(a)  Compare your numerically integrated orbits to the analytic form of the elliptic orbits for Earth and Mars. Investigate the error behavior over the growing number of revolutions of the planets. Do you detect a deterioration with the number of revolutions growing?

(b) For the two planets, plot the numerically integrated orbit and the analytic elliptic orbit on the same plot. Each planet will have its own plot.

(c) Do a simple animation of the earth motion in gnuplot or some other plotting method of your choice over many revolutions.

## Problem 4  (for Physics 141/241)
Prove the exact conservation of angular momentum of the discretized leapfrog-Verlet algorithm on Kepler orbits.


## Problem 5  (for Physics 241 only)

Calculate and plot the orbit of the Halley comet (read about the comet and its orbit in Wikipedia).

## Problem 6  (for Physics 241 only)

Put the Halley comet and Earth in the same animation and demonstrate one full Halley year: https://en.wikipedia.org/wiki/Halley%27s_Comet

Comet table: https://en.wikipedia.org/wiki/List_of_numbered_comets

## Tutorial for Leapfrog Integration
[leapfrog.pdf](leapfrog.pdf)

## Leapfrog in Python tutorial:

http://cvarin.github.io/CSci-Survival-Guide/leapfrog.html

## Tutorial on Kepler orbits
[kepler.pdf](kepler.pdf)

