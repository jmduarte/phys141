# Introduction to Select NEMO Tools

## binary <-> ascii conversions

```bash
# An example of converting between text and snapshot formats
# First, activate NEMO by sourcing the NEMO init script (depending on the machine)
# Second, create an example snapshot
magalie gal.ic ndisk=10000 nbulge=0 nhalo=10000
# Run gyrfalcON for a while to get a multi-snapshot file
gyrfalcON gal.ic gal.out tstop=5 step=0.1 kmax=3 eps=0.03
# Convert the snapshots into text format
snapprint in=gal.ic options=m,x,y,z,vx,vy,vz header=t > gal.ic.tab
snapprint in=gal.out options=m,x,y,z,vx,vy,vz header=t > gal.out.tab
# Check for the format in the results. You want to make your own output into this format so that it can be converted into snapshots and be opened in glnemo2
# Convert the text back into snapshots
tabtos in=gal.ic.tab out=gal.ic.tab.snp header=nbody,time block1=mass,pos,vel
tabtos in=gal.out.tab out=gal.out.tab.snp header=nbody,time block1=mass,pos,vel
# Finally, check with glnemo2 that the convertion works.
```

```bash
# converting from ascii format (like x.tab that is Aarseth format) to nemo binary format (x.snap):
tabtos in=x.tab out=x.snap header=nbody,time block1=mass,pos,vel

# quick peek inside a binary in readable format:
tsf xrun.snap

# converting from binary format (like x.snap) to ascii format (x.tab):
snapprint in=xrun.snap options=m,x,y,z,vx,vy,vz header=t > xrun.tab
```

## `snaprotate` and `snapstack`

```bash
magalie gal.ic ndisk=10000 nbulge=0 nhalo=10000

# First we rotate a galaxy we created:
snaprotate gal.ic gal.rot theta=0,90,0 order=xyz

# Now we join the two galaxies into one snapshot:
snapstack gal.ic gal.rot col.ic deltar=10,10,0 deltav=-1,0,0

# Check the initial conditions (note the disk indices):
glnemo2 col.ic 0:9999,20000:29999

# Run the collision:
gyrfalcON col.ic col.out tstop=50 step=0.1 kmax=6 eps=0.03

# View the result:
glnemo2 col.out 0:9999,20000:29999
```