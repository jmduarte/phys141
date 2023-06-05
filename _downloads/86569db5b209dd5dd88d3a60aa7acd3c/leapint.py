"""
leapint.py: program to integrate hamiltonian system using leapfrog.
"""
import numpy as np

MAXPNT = 100


def main():
    x = np.zeros((MAXPNT))
    v = np.zeros((MAXPNT))

    # first, set up initial conditions
    n = 1  # set number of points
    x[0] = 1.0  # set initial position
    v[0] = 0.0  # set initial velocity
    tnow = 0.0  # set initial time

    # next, set integration parameters
    mstep = 256  # number of steps to take
    nout = 4  # steps between outputs
    dt = 1.0 / 32.0  # timestep for integration

    # now, loop performing integration
    for nstep in range(mstep):  # loop mstep times in all
        if nstep % nout == 0:  # if time to output state
            printstate(x, v, n, tnow)  # then call output routine
        leapstep(x, v, n, dt)  # take integration step
        tnow = tnow + dt  # and update value of time
    if mstep % nout == 0:  # if last output wanted
        printstate(x, v, n, tnow)  # then output last step


def leapstep(x, v, n, dt):
    """LEAPSTEP: take one step using the leapfrog integrator, formulated
    as a mapping from t to t + dt.  WARNING: this integrator is not
    accurate unless the timestep dt is fixed from one call to another.

    Args:
        x (np.array): positions of all points
        v (np.array): velocities of all points
        n (int): number of points
        dt (float): timestep for integration
    """
    a = np.zeros((MAXPNT))

    accel(a, x, n)  # call acceleration code

    for i in range(n):  # loop over all points...
        v[i] = v[i] + 0.5 * dt * a[i]  # advance vel by half-step
    for i in range(n):  # loop over points again...
        x[i] = x[i] + dt * v[i]  # advance pos by full-step

    accel(a, x, n)  # call acceleration code

    for i in range(n):  # loop over all points...
        v[i] = v[i] + 0.5 * dt * a[i]  # and complete vel. step


def accel(a, x, n):
    """ACCEL: compute accelerations for harmonic oscillator(s)

    Args:
        a (np.array): accelerations of points
        x (np.array): positions of points
        n (int): number of points
    """
    for i in range(n):  # loop over all points...
        a[i] = -x[i]  # use linear force law


def printstate(x, v, n, tnow):
    """PRINTSTATE: output system state variables.

    Args:
        x (np.array): positions of all points
        v (np.array): velocities of all points
        n (int): number of points
        tnow (float): current value of time
    """
    for i in range(n):  # loop over all points...
        print("%8.4f%4d%12.6f%12.6f" % (tnow, i, x[i], v[i]))

if __name__ == "__main__":
    main()