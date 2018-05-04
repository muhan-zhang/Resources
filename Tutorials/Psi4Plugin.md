In this tutorial we will create a Psi4 plugin that computes the MP2 energy using the spin orbital formalism

Create a new plugin with support for integrals transformed to the MO basis

```
> psi4 --plugin-name mp2so_plug --plugin-template mointegrals
```

Next, change directory and generate the CMake command to compile the plugin
```
> cd mp2so_plug
> psi4 --plugin-compile
cmake -C /Users/fevange/anaconda3/envs/p4env/share/cmake/psi4/psi4PluginCache.cmake -DCMAKE_PREFIX_PATH=/Users/fevange/anaconda3/envs/p4env .
```
and execute the command `cmake -C ...` to compile the plugin.

1. Get number of molecular integrals from the `ref_wfn` object:

```c++
    // Allocate a vector of size nmo^4
    size_t nmo = ref_wfn->nmo();
    size_t nmo4 = nmo * nmo * nmo * nmo;
    std::vector<double> mo_ints(nmo4);
    
    auto four_idx = [&](size_t p, size_t q, size_t r, size_t s,
                      size_t dim) -> size_t {
        size_t dim2 = dim * dim;
        size_t dim3 = dim2 * dim;
        return (p * dim3 + q * dim2 + r * dim + s);
    };
```


```
// PRINT_ELEMENTS()
// - prints optional string optcstr followed by
// - all elements of the collection coll
// - separated by spaces
template <typename T>
inline void PRINT_ELEMENTS(const T &coll, const std::string &optcstr = "",
                           bool el = false) {
  std::cout << optcstr << "[";
  bool notfirst = false;
  for (auto elem : coll) {
    if (notfirst) {
      std::cout << ',' << elem;
    } else {
      std::cout << elem;
      notfirst = true;
    }
  }
  std::cout << "]";
  if (el)
    std::cout << std::endl;
}
```

```
// PRINT_MAPPED_ELEMENTS()
// - prints optional string optcstr followed by
// - all elements of the key/value collection coll
// - separated by spaces
template <typename T>
inline void PRINT_MAPPED_ELEMENTS(const T &coll,
                                  const std::string &optcstr = "") {
  std::cout << optcstr;
  for (auto elem : coll) {
    std::cout << '[' << elem.first << ',' << elem.second << "] ";
  }
  std::cout << std::endl;
}
```

```
// INSERT_ELEMENTS (collection, first, last)
// - fill values from first to last into the collection
// - NOTE: NO half-open range
template <typename T>
inline void INSERT_ELEMENTS(T &coll, int first, int last) {
  for (int i = first; i <= last; ++i) {
    coll.insert(coll.end(), i);
  }
}
```
