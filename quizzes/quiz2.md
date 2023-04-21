# Quiz 2

Physics 141/241: Computational Physics I

Instructor: Javier Duarte

Spring 2023

Due date: _Monday, April 24, 2023 8pm_

Total points: 10

## Submission Instructions

-   Please submit your quiz as a single `.pdf` file to Gradescope under **Quiz 2**.
-   For instructions specifically pertaining to the Gradescope submission process, see https://www.gradescope.com/get_started#student-submission.


## Problem 1 (141/241) [10 points]
In lecture 8, we showed that starting from the distribution function
$$
f = \begin{cases} 
F(-E)^{7/2} & \mathrm{if}~E<0\\
0 & \mathrm{if}~E\geq0
\end{cases}~,
$$
we could integrate over the velocity components $\rho = \int d^3v f$ to derive the relation $\rho = c_p(-\Phi)^5$. 

From the last line of slide 8, we saw that the constant $c_p$ is given by the integral
$$
c_p = 2^{7/2}\pi F \int_{0}^{\pi/2}d\theta  \sin\theta \cos^2\theta~\left(1-\cos^2\theta\right)^{7/2} 
$$


Evaluate this integral to derive $c_p = 2^{5/2}\pi^2 F\frac{7!!}{10!!}$, where $!!$ denotes the [double factorial](https://en.wikipedia.org/wiki/Double_factorial) (*not to be confused with the factorial function iterated twice*).


*Hint*: Use the trigonometric identity $\sin^2\theta + \cos^2\theta = 1$ and $\int_0^{\pi/2}\sin^{2m}\theta d\theta = \frac{\pi}{2}\frac{(2m-1)!!}{(2m)!!}$.
 