# King Model

```bash
mkking out=king.in nbody=10000 W0=5
gyrfalcON king.in king.out tstop=50 step=0.1 kmax=6 eps=0.03
```

Plot in GLNemo2

```bash
glnemo2 king.out

```bash
mkbaredisk disk.in 10000
gyrfalcON disk.in disk.out tstop=10 kmax=5 step=0 eps=0.03
```