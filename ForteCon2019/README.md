# ForteCon and QForteCon 2019

## Goals for ForteCon
- [ ] Use integrals read from python, disk, or other programs
- [ ] Tutorials: write a FCI code in python using the determinant class (symmetry, determinants, integrals)
- [ ] Tutorials: write a DSRG-MRPT2 code in numpy (need to write interface, numpy)
- [ ] Get rid of `reference` and other warnings
- [ ] Conda package for Forte and QForte
- [ ] Web page

## Goals for QForteCon
- [ ] Eliminate the OpenFermion dependency (need Psi4 api)
- [ ] Code coverage
- [ ] Online documentation for python API
- [ ] Tests and tutorials
- [ ] Web page

## Pre-con assignment
- [ ] Fix TravisCI
- [ ] Write interface for DSRG-MRPT2 code
- Talk \
Object-oriented Programming in 7 minutes https://www.youtube.com/watch?v=pTB0EiLXUC8
- Articles

## Schedule

### Day 1 morning (9-12)

- Overview of Forte
  + folder stucture
  + code execution
  + interface with Psi4
  + Forte python API

- FCI Tutorial
  + determinants
  + integrals
  + setting up the FCI determinants
  + forming and diagonalizing H
  + assignment DOCI, CC?  
  
### Day 1 afternoon (1-3:30)

- QForte tutorial

### Day 2 morning (9-11:30)

- DSRG-MRPT2 tutorial (part I)
  + ???
  
### Day 2 afternoon (1:30-4)

- DSRG-MRPT2 tutorial (part II)

### Day 3

- Coding sessions
 + goal 1
 + goal 2

### Day 4

- TensorFlow tutorial

## Task list
### Psi4
- [ ] fix the issue with `mints.one_electron_integrals()` when changing molecule/basis

### Forte
- [ ] Pass forte_options to `ints = forte.make_forte_integrals(wfn, options, mo_space_info)`
- [ ] Fix default argument  `.def("str", &Determinant::str, "Get the string representation of the Slater determinant")`

## Extended reading
- UML Class diagram https://en.wikipedia.org/wiki/Class_diagram
- Code Complete https://proquest-safaribooksonline-com.proxy.library.emory.edu/book/software-engineering-and-development/0735619670
- SOLID principles of object-oriented programming https://en.wikipedia.org/wiki/SOLID
