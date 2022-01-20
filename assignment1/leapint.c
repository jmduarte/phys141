/*
 * LEAPINT.C: program to integrate hamiltonian system using leapfrog.
 */

#include <math.h>
#include <stdio.h>

#define MAXPNT  100				/* maximum number of points */

void leapstep();				/* routine to take one step */

void accel();					/* accel. for harmonic osc. */

void printstate();				/* print out system state   */

void main(argc, argv)
int argc;
char *argv[];
{
    int n, mstep, nout, nstep;
    double x[MAXPNT], v[MAXPNT], tnow, dt;

    /* first, set up initial conditions */

    n = 1;					/* set number of points     */
    x[0] = 1.0;					/* set initial position     */
    v[0] = 0.0;					/* set initial velocity     */
    tnow = 0.0;					/* set initial time         */

    /* next, set integration parameters */

    mstep = 256;				/* number of steps to take  */
    nout = 4;					/* steps between outputs    */
    dt = 1.0 / 32.0;				/* timestep for integration */

    /* now, loop performing integration */

    for (nstep = 0; nstep < mstep; nstep++) {	/* loop mstep times in all  */
	if (nstep % nout == 0)			/* if time to output state  */
	    printstate(x, v, n, tnow);		/* then call output routine */
	leapstep(x, v, n, dt);			/* take integration step    */
	tnow = tnow + dt;			/* and update value of time */
    }
    if (mstep % nout == 0)			/* if last output wanted    */
	printstate(x, v, n, tnow);		/* then output last step    */
}

/*
 * LEAPSTEP: take one step using the leap-from integrator, formulated
 * as a mapping from t to t + dt.  WARNING: this integrator is not
 * accurate unless the timestep dt is fixed from one call to another.
 */

void leapstep(x, v, n, dt)
double x[];					/* positions of all points  */
double v[];					/* velocities of all points */
int n;						/* number of points         */
double dt;					/* timestep for integration */
{
    int i;
    double a[MAXPNT];

    accel(a, x, n);				/* call acceleration code   */
    for (i = 0; i < n; i++)			/* loop over all points...  */
	v[i] = v[i] + 0.5 * dt * a[i];		/* advance vel by half-step */
    for (i = 0; i < n; i++)			/* loop over points again...*/
	x[i] = x[i] + dt * v[i];		/* advance pos by full-step */
    accel(a, x, n);				/* call acceleration code   */
    for (i = 0; i < n; i++)			/* loop over all points...  */
	v[i] = v[i] + 0.5 * dt * a[i];		/* and complete vel. step   */
}

/*
 * ACCEL: compute accelerations for harmonic oscillator(s).
 */

void accel(a, x, n)
double a[];					/* accelerations of points  */
double x[];					/* positions of points      */
int n;						/* number of points         */
{
    int i;

    for (i = 0; i < n; i++)			/* loop over all points...  */
	a[i] = - x[i];				/* use linear force law     */
}

/*
 * PRINTSTATE: output system state variables.
 */

void printstate(x, v, n, tnow)
double x[];					/* positions of all points  */
double v[];					/* velocities of all points */
int n;						/* number of points         */
double tnow;					/* current value of time    */
{
    int i;

    for (i = 0; i < n; i++)			/* loop over all points...  */
	printf("%8.4f%4d%12.6f%12.6f\n", tnow, i, x[i], v[i]);
}
