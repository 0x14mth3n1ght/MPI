TDs de programmation parallèle avec l'api MPI (mpich) sur un cluster HPC (Centos), avec l'outil slurm et le compilateur mpicc (voir td1 pour l'exemple).

![Prise en main](https://github.com/0x14mth3n1ght/ProgrammationParallele_MPI-S3/tree/master/td1/td1_mpi_collective)

# Installation

MPI (mpicc, mpirun):
```
sudo apt update
sudo apt install mpich #ou openmi-bin
```
Slurm (sinfo,srun):
```
# Install dependencies
sudo apt install build-essential munge munge-libs munge-devel openssl openssl-devel pam-devel

# Download Slurm source code
wget https://download.schedmd.com/slurm/slurm-20.11.1.tar.bz2
tar -xvf slurm-20.11.1.tar.bz2
cd slurm-20.11.1
```
Pour Arch:

```
sudo pacman -S slurm-llnl
```
# Exemple

![exemple](https://github.com/0x14mth3n1ght/MPI/edit/master/td1/td1_mpi_collective/mpi.png)
