#! /bin/tcsh

# Script to compile ambit using llvm and C++11 on a mac

# Modify the following four parameters
set srcdir = /Users/fevange/Source/ambit        # <- location of source
set build_type = Debug                          # <- debug, release, or profile

# define object and prefix dirs
set prefix = /Users/fevange/Bin/ambit-$build_type

# RUN CMAKE
cd $srcdir

rm -rf objdir

cmake -H. -Bobjdir \
-DCMAKE_C_COMPILER=clang \
-DCMAKE_CXX_COMPILER=clang++ \
-DCMAKE_BUILD_TYPE=$build_type \
-DCMAKE_INSTALL_PREFIX=$prefix

cd objdir
make
make install
