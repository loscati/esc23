---
title:  Introduction to MPI
layout: main
section: parallelism
---

Check that your environment is correctly configured to compile and run MPI code.

```shell
$ module load compilers/gcc-12.2_sl7 compilers/openmpi-4-1-4_gcc12.2
$ mpic++ -v
g++ (GCC) 12.2.1 20221004
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ which mpirun
/shared/software/compilers/openmpi-4.1.4_gcc12.2/bin/mpirun
```

Note that for MPI we will use the `gcc` v. 12 compiler.

Examples and exercises are available in the
[`hands-on/mpi`]({{site.exercises_repo}}/hands-on/mpi) directory. Follow the
instructions included in the presentation.
