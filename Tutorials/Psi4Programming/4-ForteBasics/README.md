Create a branch
```
git checkout -b tutorial
```

Copy from an existing code and adapt to your method (ca. CISD).
```
cp mrci.cc cisd.cc
cp mrci.h cisd.h
```

Change the CMakeLists.txt, and `.cc` file to `add_psi4_plugin(forte ...)`.
```
vi CMakeLists.txt
rm -r CMakeFiles
```
Run `cmake` and `make` again.
```
cmake <options>
make
```

Add `#include "cisd.h"` to `forte_old_methods.cc`, and
```c++
    if (options.get_str("JOB_TYPE") == "CISD") {
        auto cisd = std::make_shared<CISD>(ref_wfn, options, ints, mo_space_info);
        cisd->compute_energy();
    }
```

Add test with `job_type cisd` in the `set forte {` section and call `energy('forte')` in `input.dat`.
```
cd tests/methods/
mkdir cisd-1
vi input.dat
```

Your code in `CISD::compute_energy()` will be run!
