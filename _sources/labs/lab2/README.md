# lab2

## Compilation of C code
```bash
gcc -o xnbody nbody0-ang.c -lm
```

## To run
- `xnbody` reads in `initc.data` file and outputs `sphere.data` 
- `initc.data`  has 1 header line plus one line for each particle in 7 columns: `mass, x, y, z, vx, vy, vz`
- header line of `initc.data` has 5 data: `# of particles, eta=0.02, dt, tmax, epsilon**2=0.25`
- `sphere.data` has 4 columns: `mass, x, y, z`

```bash
./xnbody initc.data
```
