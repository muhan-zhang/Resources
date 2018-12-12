## Forte (https://github.com/evangelistalab/forte) Overview

Forte is an open-source **plugin** to **Psi4** (https://github.com/psi4/psi4) that implements a variety of quantum chemistry methods for strongly correlated electrons.

### Psi4 Plugin
For a basic idea of how Forte runs, let us create a plugin that possesses similar ingredients as forte.
Say we want to write a plugin to compute the MP2 energy by doing the following command

`psi4 --plugin-name my_mp2 --plugin-template scf`

Here I am using the SCF template, which gives us an SCF class.
Besides, the above command also provides us `doc.rst`, `plugin.cc`, `CMakeLists.txt`, `pymodule.py`, `__init__.py`, and `input.dat`.

#### 1. Treat `input.dat` as a python script.
Let us first quickly go through the input file.

```
sys.path.insert(0, './..')
import my_mp2
```
The first line will insert the directory that contains `my_mp2` to the beginning of sys.path (a list of strings that specifies the search path for modules) so that we can import `my_mp2`.
The next line will actually import the module `my_mp2` and run `__init__.py`, inside which will try to load the `my_mp2.so` file.
In fact, since we have not yet compile the code, if we try to run `psi4` now, we shall stop at the `import my_mp2` stage.

Next, the input file sets the molecule and some **global options**.
*Please try figuring out what these options are doing by reading the Psi4 manual. Google them!*

Finally, we call `energy('my_mp2')`.
This is a Psi4 procedure controlled by the Psi4 driver.
To see this, open `pymodule.py` and near the end we have `psi4.driver.procedures['energy']['my_mp2'] = run_my_mp2`.
Now we need to check what `run_my_mp2` is doing.
The "useful" part is `my_mp2_wfn = psi4.core.plugin('my_mp2.so', new_wfn)`, which run the plugin using the wavefunction `new_wfn` and return the a new wavefunction `my_mp2_wfn`.

Everything so far is in the python side. We can treat the input file as a python script and do a lot of useful things.
We can directly print the current energy (instead of digging the output file), modify the orbital coefficients, etc.
The latter uses Part of the Psi4 C++ functions exposed to the python side, which can be found in the `export_xxx.cc` files of Psi4.

#### 2. Compile the plugin.
In short, we use cmake and make to compile the plugin.
Let us check the `CMakeLists.txt` file.
Inside, we have minimum cmake version requirement, project name, finding psi4 package, and those plugin files that need to be compiled.
The last one should include all the `xxx.cc` files used in this plugin.
As such, if new classes are added, the corresponding `.cc` files should be added to the `CMakeLists.txt` accordingly.

For this simple plugin, we can simply `cmake .` which runs `CMakeLists.txt` and provides a `Makefile`.
We type `make` to run the `Makefile` to compile our C++ code.

#### 3. Code execution flow
For this plugin, the "main" function is located in `plugin.cc`.
Two important points here.
1. The `read_options` function, which allows us to set the *module specific* (in this case, the module is `my_mp2`) options in the input file.
2. The `my_mp2` function, which actually does the computation of this plugin.

Now if we want to write a piece of code to compute MP2 energy using the SCF optimized orbitals computed by the `SCF` class, we could create a MP2 class, inside which we define a `compute_energy` function.
Then in the end of `my_mp2` function of `plugin.cc`, we say `MP2 mp2(scfwfn, options); mp2.compute_energy();`.
How to implement MP2 is not the focus, but some of the ingredients are: integral transformation and tensor contractions.

### Folder Structure
With the above intro on Psi4 plugin, we are ready to discuss about forte, which is not that different from the above one.

In the forte folder, we have our old friends `__init__.py` and `pymodule.py`.
Where are the C++ files?

For a nontrivial project, we generally put different parts in the corresponding folders.
For examples, the source code is usually put in the `src` folder.
Otherwise, it would be somewhat difficult to spot what you are looking for. (Let's see what forte used to be, the libadaptive.)

Some of the most important folders in forte:
1. `src` folder
    - The "main" function (`forte(...)`) is in `main.cc`.
    - The options are either in the corresponding method folder (e.g. CI-NO options in ci-no folder) or in `forte_old_options.cc` (needs clean-up).
    - How different methods (ACI, PCI, DSRG, etc) run can be found in `forte_old_methods.cc` (needs clean-up).
2. `tests` folder
    - It contains test cases for each theoretical method. Since the manual is not complete, please check the corresponding test cases.
    - It is encouraged to run the `run_forte_tests.py` script in `tests/methods/` to test all test cases yielding consistent results.
3. `docs` folder
    - The documents are in the `docs/sphinx/` directory.
    - Currently, DSRG is not documented, so nonexistent.

### Code Execution

I won't repeat myself here as I explain in the "Psi4 Plugin" section.

One thing I need to point out is that the `pymodule.py` of forte is different from the above `my_mp2` example.
Forte will look for `ref_wfn` and if it is not found, it will run a SCF computation and use the SCF wavefunction.
Thus, the correct way to run forte is to do either the following: `energy("forte")` or `E, wfn = energy('xxx') energy('forte', ref_wfn=wfn)` where "xxx" could be "scf" or "casscf" or even "forte".

### Current Methods in Forte

Here are some important methods and helper classes that you may use regularly.

Major methods:
- adaptive configuration interaction/self-consistent field (ACI/ACI-SCF)
- projective configuration interaction (PCI)
- full configuraton interaction (FCI)
- complete active space self-consistent field (CASSCF)
- single-reference/multireference driven similarity renormalization group (SR/MR-DSRG)

Other methods (not commonly used/under development/not fully tested)
- coupled-cluster singles and doubles
- other selective CAS methods: VCIS, VCISD, DOCI
- uncontracted multireference perturbation theory / configuration interaction
- finite-temperature Hartree-Fock
- density matrix renormalization group

Some helpers:
- Integral class: conventional two-electron integrals, density fitting, Cholesky decomposition, user defined
- Reference class: holds the density matrices/cumulants
- orbital modification: localizer, semicanonical, mp2-no, cis-no, avas, orbital optimizer
- Davidson-Liu solver
- Determinant class
- Hashvector template library
- V2RDM: an interface to read V2RDM dumped density files

*Since there are so many methods in Forte, we use `JOB_TYPE` option to handle what method should be run.*

Quiz: where to look for the way how each method is excecuted? Hint: `grep` is your friend.

### Add New Features to Forte / Connection to Psi4
Let us first see an example of existing feature, the CASSCF class.
Let us answer the following questions:
- What should CASSCF do? Decide what to be exposed to the public.
    - compute energy
    - optimize orbitals
    - compute RDMs
- Create a CASSCF class.
    - include guard
    - namespace
    - derived from Psi4 Wavefunction
    - use Psi4 functionalities: Matrix, Vector, Dimension, JK, etc.
- Are there any options that user can tune the CASSCF procedure? Where should those options go?
- In which file should we create the CASSCF object and call the compute_energy function (under current convention)?
- One last thing: change CMakeLists.txt!

**Before implementing anything useful (filling the details of a class), just write the constructor and see if the class compiles and runs!**
