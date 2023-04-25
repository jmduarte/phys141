# Introduction to NEMO - A Stellar Dynamics Toolbox

## Links

-   [NEMO Home Page](https://teuben.github.io/nemo/)

-   [NEMO GitHub](https://github.com/teuben/nemo)

-   [NEMO Reference Manual (Old Manual)](https://teuben.github.io/nemo/man_html/)

-   [NEMO Read the Docs (New Manual)](https://astronemo.readthedocs.io/en/latest/index.html#)

-   [GLNEMO2](https://projets.lam.fr/projects/glnemo2/wiki)

-   [Galaxy Collision](https://www.youtube.com/watch?v=C0XNyTp5brM&ab_channel=HubbleSpaceTelescope), [Milky Way Meets Andromeda](https://www.youtube.com/watch?v=4disyKG7XtU&ab_channel=VideoFromSpace)

## Activate NEMO Environment

-   Local (Lab iMac)

    ```bash
    todo
    ```

-   DSMLP

    Choose the `phys141` image and start a terminal.

    ```bash
    source /home/jovyan/nemo/nemo_start.sh
    ```

Note that the NEMO installation in Lab iMac and DSMLP are not the latest/full version. Some features may not work like you see in the docs.

## Quick Start

-   Simple Disk Galaxy

    Note: the current version of the DSMLP `phys141` image does not have `glnemo2` installed.

    ```bash
    # This exercise is specifically for the iMacs in the lab

    # add glnemo2 library to PATH
    PATH=/usr/local/physics/bin/glnemo2.app/Contents/MacOS:$PATH

    # create initial disk galaxy
    magalie gal.ic ndisk=10000 nbulge=0 nhalo=10000

    # The first ten thousand particles (indices 0:9999) are the disk
    # Inspect the disk:
    glnemo2 gal.ic 0:9999 xrot=90

    # The next ten thousand particles (indices 10000:19999) are the halo
    # Inspect the halo:
    glnemo2 gal.ic 10000:19999 xrot=90

    # run N-body simulation for 50 time units
    gyrfalcON gal.ic gal.out tstop=50 step=0.1 kmax=6 eps=0.03

    # Inspect the result
    glnemo2 gal.out 0:9999,10000:19999

    # prepare to make a video
    mkdir frames
    cd frames

    # use glnemo2 to generate the frames
    glnemo2 ../gal.out 0:9999 hsize=400 wsize=400 play=t screenshot=frame

    # generate the video
    ffmpeg -y -i frame.%05d.jpg -c:v libx264 -vf fps=20 -pix_fmt yuv420p video.mp4
    ```

-   Bare Unstable Disk

    ```bash
    # create a bare unstable disk
    mkbaredisk disk.ic 10000

    # Check the initial conditions:
    glnemo2 disk.ic all point=t psize=5

    # Run the simulation:
    gyrfalcON disk.ic disk.out tstop=10 kmax=5 step=0 eps=0.03

    # View the result:
    glnemo2 disk.out all point=t psize=5
    ```

-   More Advanced Galaxies

    ```bash
    # build WD99disc
    mkWD99disc out=WDdisc_init.snp nbody=100000 Sig_0=1 Q=1

    # N-body simulation
    gyrfalcON in=WDdisc_init.snp out=WDdisc_run.snp tstop=50 step=0.1 eps=0.01 kmax=4 logfile=disc.log

    # view the result
    glnemo2 WDdisc_run.snp
    ```

    ```bash
    # build complete galaxy with mkgalaxy:
    mkgalaxy name=testgalaxy

    # view the components of the galaxy in glnemo2:
    glnemo2 testgalaxy.snp 0:39999

    # run the n-body evolution of galaxy with gyrfalcON:
    gyrfalcON in=testgalaxy.snp out=xrun50k4.snp tstop=50 step=0.1 eps=0.01 kmax=4 logfile=xrun50k4.log

    # view the simulation result:
    glnemo2 xrun50k4.snp 0:39999
    ```

Read more about `mkgalaxy` and `gyrfalcON` here [mkgalaxy user guide](mkgalaxy_user_guide.pdf) and [gyrfalcON user guide](gyrfalcON_user_guide.pdf).
