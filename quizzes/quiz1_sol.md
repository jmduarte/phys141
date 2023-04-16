# Quiz 1 Solution

Physics 141/241: Computational Physics I

Instructor: Javier Duarte

Spring 2023

Due date: _Friday, April 14, 2023 5pm_

Total points: 10

## Submission Instructions

-   Please submit your quiz as a single `.pdf` file to Gradescope under **Quiz 1**.
    -   For instructions specifically pertaining to the Gradescope submission process, see https://www.gradescope.com/get_started#student-submission.

## Problem 1 (141/241) [10 points]

In this problem, you will prove that leapfrog integration has exact time-reversal symmetry.
Recall the kick-drift-kick leapfrog update equations, which tell you how to go from $(x_n, v_n) \to (x_{n+1}, v_{n+1})$:

$$
\begin{align}
v_{n+1/2} & = v_n + a(x_n) \Delta t / 2\\
x_{n+1} &= x_n + v_{n+1/2} \Delta t \\
v_{n+1} &= v_{n+1/2} + a(x_{n+1}) \Delta t / 2
\end{align}
$$

Consider the time-reversed problem, with variables we'll denote with a prime:
$t', x', v', a'$.
By flipping the "arrow of time," some variables are negated with respect to the forward problem.
That is, $t' = -t$ and $v' = -v$, but $x' = x$ and $a' = a$ are unchanged.

Prove that if you start from the end point in the time-reversed problem $x'_{n} = x_{n+1}$ and $v_{n}' = -v_{n+1}$, then apply the leapfrog update rule, you arrive back at the starting point: $x'_{n+1} = x_{n}$ and $v'_{n+1} = -v_{n}$.

Hint: recall that $\Delta t' = - \Delta t$.

## Solution:

We write down the kick-drift-kick leapfrog update equations using time-reversed coordinates $t'$, $x'$, $v'$, and $a'$:

$$
\begin{align}
v'_{n+1/2} & = v'_{n} + a'(x'_{n}) \Delta t' / 2\\
x'_{n+1} &= x'_{n} + v'_{n+1/2} \Delta t' \\
v'_{n+1} &= v'_{n+1/2} + a'(x'_{n+1}) \Delta t' / 2
\end{align}
$$

Next, we can relate these equations to the time-forward ones with the facts that $a' = a$, $x'_n = x_{n+1}$, $v'_n = v_{n+1}$, and $\Delta t' = -\Delta t$ to figure out what $x'_{n+1}$ and $v'_{n+1}$ are:

$$
\begin{align}
v'_{n+1/2} & = v_{n+1} - a(x_{n+1}) \Delta t / 2\\
x'_{n+1} &= x_{n+1} - v'_{n+1/2} \Delta t \\
v'_{n+1} &= v'_{n+1/2} - a(x'_{n+1}) \Delta t / 2
\end{align}
$$

Moving terms around a little bit:

$$
\begin{align}
v_{n+1} & = v'_{n+1/2} + a(x_{n+1}) \Delta t / 2\\
x_{n+1} &= x'_{n+1} + v'_{n+1/2} \Delta t \\
v'_{n+1/2} &= v'_{n+1} + a(x'_{n+1}) \Delta t / 2
\end{align}
$$

Comparing to the time-forward equations, we can tell that $v'_{n+1/2} = v_{n+1/2}$. And therefore, $x'_{n+1} = x_n$ and $v'_{n+1} = v_n$. We've successfully reveresed one step back in time.

## Problem 2 (141/241) [10 points]

For a uniform sphere of mass $M$ with radius $R$, prove that the gravitational potential $\Phi$ inside the sphere is related to the mass density $\rho$ by the following equation (from lecture 5):

$$
\begin{align}
\Phi(r) & = -2\pi G\rho(R^2 - \frac{r^2}{3}) &  r \leq R
\end{align}
$$

where $\rho = M/(4\pi R^3 /3)$.

Hint: Start from the equations derived from the infinitesimal spherical shell:

$$
\begin{align}
\Phi(r) &= G\int_{r_0}^r dr' ~\frac{M(r')}{r'^2}\\
M(r) & = 4\pi\int_{r_0}^r dr'~ r'^2 \rho(r')
\end{align}
$$

## Solution:

First, let's find the potential at radius $R$:

I can simply claim that the gravitational field outside the sphere is as if it's a point mass $M$ at the center. So,

$$
\begin{align}
M &= 4\pi\int_0^R dr' r'^2 \rho = \frac{4\pi}{3} R^3 \rho \\
\Phi(R) &= \int_{R}^{\infty} dr' \frac{-GM}{r'^2} = -\frac{GM}{R} = -\frac{4\pi}{3}G\rho R^2
\end{align}
$$

Next, we find the potential difference when we go from $R$ to $r$. The mass of a uniform sphere of radius $r$ is:

$$
\begin{align}
M(r) &= \frac{4\pi}{3} r^3 \rho
\end{align}
$$

So, the potential difference is:

$$
\begin{align}
\Phi(r) - \Phi(R) &= \int_{r}^{R} dr' \frac{-GM(r')}{r'^2} \\
&= - \frac{4\pi}{3}G\rho \int_{r}^{R} dr' r' \\
&= - \frac{4\pi}{3}G\rho \left[\frac{R^2}{2} - \frac{r^2}{2}\right]
\end{align}
$$

Therefore,

$$
\begin{align}
\Phi(r) &= -\frac{4\pi}{3}G\rho R^2 - \frac{4\pi}{3}G\rho \left[\frac{R^2}{2} - \frac{r^2}{2}\right] \\
&= -2\pi G\rho R^2 + \frac{2\pi}{3}G\rho r^2 \\
&= -2\pi G\rho(R^2 - \frac{r^2}{3})
\end{align}
$$

which is the gravitational potential inside a uniform sphere ($r \leq R$).
