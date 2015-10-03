#! /bin/tcsh

# Script to compile psi4 using llvm and C++11 on a mac 

# Modify the following four parameters
set srcdir = /Users/francesco/Source/psi4  # <- location of psi4 source
set fc = /usr/local/bin/gfortran-4.9       # <- fortran compiler
set cc = llvm-gcc                          # <- C compiler
set cxx = llvm-g++                         # <- C++ compiler
set psi4type = debug                       # <- debug, release, or profile
set maxameri = 5                           # <- 5 for cc-pV5Z, 6 for cc-pV6Z 

# define object and prefix dirs
set objdir = $srcdir-obj-$psi4type
set prefix = $srcdir-bin-$psi4type

# RUN CONFIGURE
$srcdir/setup \
--type=$psi4type \
--prefix=$prefix \
--fc=$fc \
--cc=$cc \
--cxx=$cxx \
--cxx11=on \
--plugins=on \
--accelerate \
--chemps2 off \
--max-am-eri=$maxameri \
$objdir
