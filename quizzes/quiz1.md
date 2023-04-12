# Quiz 1

Physics 141/241: Computational Physics I

Instructor: Javier Duarte

Spring 2023

Due date: _Friday, April 15, 2023 5pm_

Total points: 30

## Submission Instructions

- Please submit your quiz as a single `.pdf` file to Gradescope under **Quiz 1**.
  - For instructions specifically pertaining to the Gradescope submission process, see https://www.gradescope.com/get_started#student-submission.

## Problem 1 (141/241) [10 points]
In this problem, you will prove that leapfrog integration has exact time-reversal symmetry.
Recall the kick-drift-kick leapfrog update equations, which tell you how to go from $(x_n, v_n) \to (x_{n+1}, v_{n+1})$:

$$
\begin{align}
v_{n+1/2} & = v_n + a(x_n) \Delta t / 2\\
x_{n+1} &= x_n + v_{n+1/2} \Delta t \\
v_{n+1} &= v_{n+1/2} + a(x_{n+1}) \Delta t 
\end{align}
$$

Consider the time-reversed problem, with variables we'll denote with a prime:
$t', x', v', a'$.
By flipping the "arrow of time," some variables are negated with respect to the forward problem. 
That is, $t' = -t$ and $v' = -v$, but $x' = x$ and $a' = a$ are unchanged.

Prove that if you start from the end point in the time-reversed problem $x'_{n} = x_{n+1}$ and $v_{n}' = -v_{n+1}$, then apply the leapfrog update rule, you arrive back at the starting point: $x'_{n+1} = x_{n}$ and $v'_{n+1} = -v_{n}$.

Hint: recall that $\Delta t' = - \Delta t$.
 

## Problem 2 (141/241) [20 points]
For a uniform sphere of mass $M$ with radius $R$, prove that the gravitational potential $\Phi$ inside the sphere is related to the mass density $\rho$ by the following equation (from lecture 5):

$$
\begin{align}
\Phi(r) & = -2\pi G\rho(R^2 - \frac{r^2}{3}) &  r \leq R
\end{align}
$$

where $\rho = M/(4\pi R^3 /3)$.

Hint: Start from the equations derived from the infinitesimal spherical shell:

$$
\Phi(r) &= G\int_{r_0}^r dr' ~\frac{M(r')}{r'^2}\\
M(r) & = 4\pi\int_{r_0}^r dr'~ r'^2 \rho(r')
$$