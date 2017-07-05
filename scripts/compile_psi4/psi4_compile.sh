#! /bin/tcsh

# Script to compile psi4 using llvm and C++11 on a mac

# Modify the following four parameters
set srcdir = /Users/fevange/Source/psi4         # <- location of psi4 source
set psi4type = Debug                            # <- debug, release, or profile
set maxameri = 6                                # <- 5 for cc-pV5Z, 6 for cc-pV6Z

# define object and prefix dirs
set objdir = $srcdir/objdir
set prefix = $srcdir-bin-$psi4type

# RUN CMAKE
cd $srcdir

cmake -H. -B$objdir \
-DCMAKE_C_COMPILER=clang \
-DCMAKE_CXX_COMPILER=clang++ \
-DCMAKE_BUILD_TYPE=$psi4type \
-DMAX_AM_ERI=$maxameri \
-DBUILD_SHARED_LIBS=ON \
-DCMAKE_INSTALL_PREFIX=$prefix
