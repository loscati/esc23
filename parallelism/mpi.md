---
title:  Introduction to MPI
layout: main
section: parallelism
---

Your environment needs to be correctly configured in order to compile and run
MPI code. The following instructions assume that you are in your home directory
on `hpc-200-11-40`.

```shell
$ hostname
hpc-201-11-40.cr.cnaf.infn.it
$ pwd
/home/HPC/studentN
```

- Be sure to have the `bash` initialization files in your home directory, as
  recommended when we [set up the
  environment]({{site.baseurl}}/basic/environment.html)

```shell
$ ls .bash_profile .bashrc
.bash_profile .bashrc
```

- Add at the end of `.bashrc` the loading of the modules
  `compilers/gcc-12.3_sl7` and `compilers/openmpi-4-1-5_gcc12.3`

```shell
echo 'module load compilers/gcc-12.2_sl7 compilers/openmpi-4-1-4_gcc12.2' >> .bashrc
```

- Modify (or create from scratch if not existing) the `.ssh/config` file so that it contains the following:

```shell
$ cat .ssh/config
Host *
  StrictHostKeyChecking no
```

- Exit from the machine and login again. If you open a terminal directly in a
  VSCode remote connection, disconnect and reconnect again. In both cases **be
  sure to forward the SSH agent**. Check that the environment is correct.

```shell
$ hostname
hpc-201-11-40.cr.cnaf.infn.it
$ ssh-add -l
3072 SHA256:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx student30@esc (RSA)
...
$ ssh hpc-200-06-06 pwd
Warning: Permanently added 'hpc-200-06-06,131.154.184.9' (ECDSA) to the list of known hosts.
/storage-hpc/gpfs_data/HPC/home_recovery/student30
...

$ gcc --version
gcc (GCC) 12.3.0
...
$ mpicc --version
gcc (GCC) 12.3.0
...
$ mpirun --version
mpirun (Open MPI) 4.1.5
...
```

Be sure that when issuing the `ssh hpc-200-06-06 pwd` command, you don't need to interact in any way to get the result back.

Examples and exercises are available in the
[`hands-on/mpi`]({{site.exercises_repo}}/hands-on/mpi) directory. Follow the
instructions included in the presentation.
