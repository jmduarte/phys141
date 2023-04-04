/* nbody.c
 * adapted from f2c code generated from Aarseth's
 * Fortran code
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define dot(a,b) ((a[0])*(b[0]) + (a[1])*(b[1]) + (a[2])*(b[2]))
#define lengthSquared(a) dot(a,a)
#define length(a) sqrt(lengthSquared(a))

#define cross(c,a,b) c[0] = (a[1])*(b[2]) - (a[2])*(b[1]); \
                     c[1] = (a[2])*(b[0]) - (a[0])*(b[2]); \
                     c[2] = (a[0])*(b[1]) - (a[1])*(b[0]);

#define kMaxParticles 20000
#define kNumDims 3

/* per-particle physical and dynamic properties */
double masses[kMaxParticles], positions[kMaxParticles][kNumDims], 
    previousPositions[kMaxParticles][kNumDims], previousVelocities[kMaxParticles][kNumDims],
    forces[kMaxParticles][kNumDims], forceDots[kMaxParticles][kNumDims];

/* other per-particle state variables */
double steps[kMaxParticles], t0[kMaxParticles], t1[kMaxParticles], t2[kMaxParticles],
    t3[kMaxParticles], d1[kMaxParticles][kNumDims], d2[kMaxParticles][kNumDims],
    d3[kMaxParticles][kNumDims];

double currentTime = 0.0, nextTime = 0.0, timeStep, finalTime, eta, epsilonSquared;

int numSteps = 0, numParticles;

void readParameters();
void readParticles();
void initializeParticles();
void outputData();
void advanceParticles();
void writeAllParticleData();

FILE * inputFile;
FILE * outputFile;
FILE * phyFile;

int main()
{
    /* the input file can either be a file or the standard input */
    /*inputFile = stdin;*/
    inputFile = fopen("initc.data", "r");

    readParameters();
    readParticles();
    outputFile = fopen("sphere.data", "w");
    phyFile = fopen("spheredata.data", "w");
    initializeParticles();

    while(1)
    {
        outputData();
        if(currentTime > finalTime)
            break;
        nextTime += timeStep;
        advanceParticles();
    }
        
    fclose(outputFile);
    fclose(inputFile);
    fclose(phyFile);    

    return 0;
}


void readParameters()
{
    printf("Enter numParticles, eta, timeStep, finalTime and epsilonSquared: ");
    fscanf(inputFile, "%i", &numParticles);
    if(numParticles > kMaxParticles)
    {
        fprintf(stderr, "The program currently supports up to %i particles.\n"
                        "If you reqire more particles, please increase\n"
                        "kMaxParticles in nbody.c and recompile.\n", kMaxParticles);
        exit(1);
    }
    fscanf(inputFile, "%lf", &eta);
    fscanf(inputFile, "%lf", &timeStep);
    fscanf(inputFile, "%lf", &finalTime);
    fscanf(inputFile, "%lf", &epsilonSquared);
    printf("\n");
}

void readParticles()
{
    int i, j;
    for(i=0; i<numParticles; i++)
    {
        fscanf(inputFile, "%lf", &masses[i]);
        for(j=0; j<kNumDims; j++)
            fscanf(inputFile, "%lf", &previousPositions[i][j]);
        for(j=0; j<kNumDims; j++)
            fscanf(inputFile, "%lf", &previousVelocities[i][j]);
    }
}

void initializeParticles()
{
    int i,j,k;
    double deltaVel[kNumDims], deltaPos[kNumDims], deltaForce[kNumDims],
        deltaForceDot[kNumDims], f1Dot[kNumDims], f2Dot[kNumDims], f3Dot[kNumDims];
    double a, b, c, d, e;

    /* obtain total forces and first derivative for each body */
    printf("Initializing particles\n");
    printf("Obtaining total forces and first derivatives\n");
    for(i=0; i<numParticles; i++)
    {
        for(k=0; k<kNumDims; k++)
        {
            forces[i][k] = 0.0;
            forceDots[i][k] = 0.0;
            d2[i][k] = 0.0;
            d3[i][k] = 0.0;
        }
        for(j=0; j<numParticles; j++)
        {
            if(j!=i)
            {
                for(k=0; k<kNumDims; k++)
                {
                    deltaPos[k] = previousPositions[j][k] - previousPositions[i][k];
                    deltaVel[k] = previousVelocities[j][k] - previousVelocities[i][k];
                }
                a = 1.0/(lengthSquared(deltaPos) + epsilonSquared);
                b = masses[j] * a * sqrt(a);
                c = 3.0 * a * dot(deltaPos, deltaVel);
                for(k=0; k<kNumDims; k++)
                {
                    forces[i][k] += b * deltaPos[k];
                    forceDots[i][k] += b * (deltaVel[k] - c * deltaPos[k]);
                }
            }
        }
        if(i%(numParticles/20) == 0)
        {
            printf(".");
            fflush(stdout);
        }
    }
    printf("\n");

    /* form second and third derivative */
    printf("Forming second and third derivatives\n");
    for(i=0; i<numParticles; i++)
    {
        for(j=0; j<numParticles; j++)
        {
            if(i!=j)
            {
                for(k=0; k<kNumDims; k++)
                {
                    deltaPos[k] = previousPositions[j][k] - previousPositions[i][k];
                    deltaVel[k] = previousVelocities[j][k] - previousVelocities[i][k];
                    deltaForce[k] = forces[j][k] - forces[i][k];
                    deltaForceDot[k] = forceDots[j][k] - forceDots[i][k];
                }
                a = 1.0/(lengthSquared(deltaPos) + epsilonSquared);
                b = masses[j] * a * sqrt(a);
                c = a * dot(deltaPos, deltaVel);
                d = a * (lengthSquared(deltaVel) + dot(deltaPos, deltaForce)) + c*c;
                e = a * (9.0 * dot(deltaVel, deltaForce) + 3.0 * dot(deltaPos, deltaForceDot))
                    + c * (9.0 * d - 12.0 * c * c);
                for(k=0; k<kNumDims; k++)
                {
                    f1Dot[k] = deltaVel[k] - 3.0 * c * deltaPos[k];
                    f2Dot[k] = b * (deltaForce[k] - 6.0 * c * f1Dot[k] - 3.0 * d * deltaPos[k]);
                    f3Dot[k] = b * (deltaForceDot[k] - 9.0 * d * f1Dot[k] - e * deltaPos[k]);
                    d2[i][k] += f2Dot[k];
                    d3[i][k] += f3Dot[k] - 9.0 * c * f2Dot[k];
                }
            }
        }
        if(i%(numParticles/20) == 0)
        {
            printf(".");
            fflush(stdout);
        }
    }
    printf("\n");

    /* initialize integration steps and convert to force differences */
    for(i=0; i<numParticles; i++)
    {
        steps[i] = sqrt(eta * sqrt(lengthSquared(forces[i])/lengthSquared(d2[i])));
        t0[i] = currentTime;
        t1[i] = currentTime - steps[i];
        t2[i] = currentTime - 2.0 * steps[i];
        t3[i] = currentTime - 3.0 * steps[i];
        for(k=0; k<kNumDims; k++)
        {
            d1[i][k] = (d3[i][k]*steps[i]/6.0 - 0.5*d2[i][k])*steps[i] + forceDots[i][k];
            d2[i][k] = 0.5*d2[i][k] - 0.5*d3[i][k]*steps[i];
            d3[i][k] /= 6.0;
            forces[i][k] *= 0.5;
            forceDots[i][k] /= 6.0;
        }
    }
}

void outputData()
{
    double totalEnergy = 0.0, totalMass = 0.0;
    double centerOfMass[kNumDims], totalMomentum[kNumDims],
        totalAngularMomentum[kNumDims];
   
double refPos[kNumDims], temp[kNumDims];

    double f2Dot[kNumDims], velocity[kNumDims], deltaPos[kNumDims];

    int i,j,k;

    double dt;

    for(k=0; k<kNumDims; k++)
    {
        centerOfMass[k] = 0.0f;
        totalMomentum[k] = 0.0f;
        totalAngularMomentum[k] = 0.0f;
    }

    /* kinetic energy */

    for(i=0; i<numParticles; i++)
    {
        dt = nextTime - t0[i];
        for(k=0; k<kNumDims; k++)
        {
            f2Dot[k] = d3[i][k] * ((t0[i]-t1[i]) + (t0[i]-t2[i])) + d2[i][k];
            positions[i][k] = ((((0.05*d3[i][k]*dt + f2Dot[k]/12.0)*dt + forceDots[i][k])
                *dt + forces[i][k])*dt + previousVelocities[i][k])*dt + previousPositions[i][k];
            velocity[k] = (((0.25*d3[i][k]*dt + f2Dot[k]/3.0)*dt + 3.0*forceDots[i][k])
                *dt + 2.0*forces[i][k])*dt + previousVelocities[i][k];

            centerOfMass[k] += masses[i]*positions[i][k];
            totalMomentum[k] += masses[i]*velocity[k];
        }

        /* write the particle to the file */

        totalEnergy += 0.5 * masses[i] * lengthSquared(velocity);

        totalMass += masses[i];

//        cross(totalAngularMomentum, positions[i], masses[i]*velocity)
	refPos[0] = positions[i][0];
	refPos[1] = positions[i][1];
	refPos[2] = positions[i][2];
        cross(temp, refPos, masses[i]*velocity)
        totalAngularMomentum[0] += temp[0];
        totalAngularMomentum[1] += temp[1];
        totalAngularMomentum[2] += temp[2];

        fprintf(outputFile, "%14.7g %14.7g %14.7g 1\n", positions[i][0],
            positions[i][1], positions[i][2]);

    }

    /* potential energy */
    for(i=0; i<numParticles; i++)
    {
        for(j=0; j<i; j++)
        {
            for(k=0; k<kNumDims; k++)
                deltaPos[k] = positions[i][k] - positions[j][k];
            totalEnergy -= masses[i]*masses[j] / sqrt(lengthSquared(deltaPos) + epsilonSquared);
        }
    }

    for(k=0; k<kNumDims; k++)
    {
        centerOfMass[k] /= totalMass;
    }
    /*for(i=0; i<numParticles; i++)
    {
	refPos[0] = positions[i][0] - centerOfMass[0];
	refPos[1] = positions[i][1] - centerOfMass[1];
	refPos[2] = positions[i][2] - centerOfMass[2];
        cross(temp, refPos, masses[i]*velocity)
        totalAngularMomentum[0] += temp[0];
        totalAngularMomentum[1] += temp[1];
        totalAngularMomentum[2] += temp[2];
    }*/


    printf("\n"
           "            time: %14.7g\n"
           "           steps: %14i\n"
           "  center of mass: <%14.7g, %14.7g, %14.7g>\n"
           "        momentum: %14.7g\n"
           "angular momentum: %14.7g\n"
           "          energy: %14.7g\n",
           currentTime,
           numSteps,
           centerOfMass[0], centerOfMass[1], centerOfMass[2],
           length(totalMomentum),
           length(totalAngularMomentum),
           totalEnergy);
    fprintf(phyFile, "%-10.7g %10.7g %10.7g %10.7g "
                     "%10.7g %10.7g %10.7g\n", currentTime,
                                               centerOfMass[0],
                                               centerOfMass[1],
                                               centerOfMass[2],
					       length(totalMomentum),
					       length(totalAngularMomentum),
					       totalEnergy);
}

void advanceParticles()
{
    double s, dt, dt1,dt2, dt3, t1pr, t2pr, t3pr;

    int i,j,k;

    double deltaPos[kNumDims], f1Dot[kNumDims], f2Dot[kNumDims], f3Dot[kNumDims],
        f1[kNumDims];
    double a,b, temp1, temp2, temp3, temp4;

    printf("\n"
           "Advancing Particles to goal time: %10.7f\n", nextTime);
    printf("                            steps       time\n");
    /* this is a hack for printing out the current state */
    printf("                                            ");

    while(currentTime < nextTime)
    {
        currentTime = 1e10;
        for(j=0; j<numParticles; j++)
        {
            if(currentTime > t0[j] + steps[j])
            {
                i = j;
                currentTime = t0[j] + steps[j];
            }
        }

        /* predict all coordinates to first order in force derivative */

        for(j=0; j<numParticles; j++)
        {
            s = currentTime - t0[j];
            for(k=0;k<kNumDims; k++)
                positions[j][k] = ((forceDots[j][k]*s + forces[j][k])*s
                    + previousVelocities[j][k])*s + previousPositions[j][k];
        }

        /* include 2nd and 3rd order and obtain the velocity */

        dt = currentTime - t0[i];

        for (k=0; k<kNumDims; k++)
        {
            f2Dot[k] = d3[i][k] * ((t0[i]-t1[i]) + (t0[i]-t2[i])) + d2[i][k];
            positions[i][k] = (d3[i][k]*0.05*dt + f2Dot[k]/12.0)
                *(dt*dt*dt*dt) + positions[i][k];
            previousVelocities[i][k] = (((d3[i][k]*0.25*dt + f2Dot[k]/3.0)*dt
                + forceDots[i][k]*3.0)*dt + forces[i][k]*2.0)*dt + previousVelocities[i][k];
            f1[k] = 0.0;
        }

        /* obtain current force on i-th body */

        for (j=0; j<numParticles; j++)
        {
            if (j != i)
            {
                for(k=0; k<kNumDims; k++)
                    deltaPos[k] = positions[j][k] - positions[i][k];
                a = 1. / (lengthSquared(deltaPos) + epsilonSquared);
                b = masses[j] * a * sqrt(a);

                for(k=0; k<kNumDims; k++)
                    f1[k] += b*deltaPos[k];
            }
        }

        /* set time intervals for new difference and update the times */

        dt1 = currentTime - t1[i];
        dt2 = currentTime - t2[i];
        dt3 = currentTime - t3[i];
        t1pr = t0[i] - t1[i];
        t2pr = t0[i] - t2[i];
        t3pr = t0[i] - t3[i];
        t3[i] = t2[i];
        t2[i] = t1[i];
        t1[i] = t0[i];
        t0[i] = currentTime;

        /* form new differences and include 4th order semi-iterative */

        for (k=0; k<kNumDims; k++)
        {
            temp1 = (f1[k] - 2.0*forces[i][k]) / dt;
            temp2 = (temp1 - d1[i][k]) / dt1;
            temp3 = (temp2 - d2[i][k]) / dt2;
            temp4 = (temp3 - d3[i][k]) / dt3;
            d1[i][k] = temp1;
            d2[i][k] = temp2;
            d3[i][k] = temp3;
            f1Dot[k] = t1pr * t2pr * t3pr * temp4;
            f2Dot[k] = (t1pr * t2pr + t3pr * (t1pr + t2pr)) * temp4;
            f3Dot[k] = (t1pr + t2pr + t3pr) * temp4;
            previousPositions[i][k] = (((temp4 * dt / 30.0 + f3Dot[k] * 0.05) * dt
                + f2Dot[k] / 12.0) * dt + f1Dot[k] / 6.0) * (dt*dt*dt) + positions[i][k];
            previousVelocities[i][k] = (((temp4 * .2 * dt + f3Dot[k] * 0.25) * dt
                + f2Dot[k] / 3.0) * dt + f1Dot[k] * 0.5) * (dt*dt) + previousVelocities[i][k];
        }

        /* scale F and FDOT by factorials and set new integration step */

        for (k=0; k<kNumDims; k++)
        {
            forces[i][k] = f1[k] * 0.5;
            forceDots[i][k] = ((d3[i][k] * dt1 + d2[i][k]) * dt + d1[i][k]) / 6.0;
            f2Dot[k] = (d3[i][k] * (dt + dt1) + d2[i][k]) * 2.0;
        }
        steps[i] = sqrt(eta * sqrt(lengthSquared(f1) / lengthSquared(f2Dot)));
        numSteps++;
        if(numSteps%100 == 0)
        {
            for(k=0; k<21; k++)
                printf("\b");
            printf("%10i %10.7f", numSteps, currentTime);
            fflush(stdout);
        }
    }
    for(k=0; k<21; k++)
        printf("\b");
    printf("%10i %10.7f", numSteps, currentTime);
    fflush(stdout);
    printf("\n");
}

void writeAllParticleData()
{
    FILE * file;
    int i;
    file = fopen("particlesLocal.data", "w");
    for(i=0; i<numParticles; i++)
    {
        fprintf(file, "%i\n"
                      "    pos = <%f %f %f>\n"
                      "      f = <%f %f %f>\n"
                      "   fdot = <%f %f %f>\n"
                      "prevPos = <%f %f %f>\n"
                      "prevVel = <%f %f %f>\n"
                      "     t0 = %f\n"
                      "     t1 = %f\n"
                      "     t2 = %f\n"
                      "     t3 = %f\n"
                      "   step = %f\n"
                      "     d1 = <%f %f %f>\n"
                      "     d2 = <%f %f %f>\n"
                      "     d3 = <%f %f %f>\n\n", i,
                      positions[i][0], positions[i][1], positions[i][2],
                      forces[i][0], forces[i][1], forces[i][2],
                      forceDots[i][0], forceDots[i][1], forceDots[i][2],
                      previousPositions[i][0], previousPositions[i][1], previousPositions[i][2],
                      previousVelocities[i][0], previousVelocities[i][1], previousVelocities[i][2],
                      t0[i], t1[i], t2[i], t3[i], steps[i],
                      d1[i][0], d1[i][1], d1[i][2],
                      d2[i][0], d2[i][1], d2[i][2],
                      d3[i][0], d3[i][1], d3[i][2]);
    }
    fclose(file);
}
