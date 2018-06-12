In this tutorial we will introduce how to adapt symmetry in the so-mp2 code.

Symmetry in orbitals:
```

C1:[i,j,k,...,a,b,c,...]
   [1,1,1,...,0,0,0,...]

C2v:a1[1,1,0,0];
    a2[...]
    ...

```

In order to handle the symmetry, we need to know the total number of MO and occupation number in each irrep.
```c++
    Dimension noccpi = ref_wfn->doccpi();
    Dimension nmopi = ref_wfn->nmopi();
```

Declairation of occupied and virtual indicies and orbital energies:
```c++
    std::vector<double> epsilon(nso, 0.0); 
    std::vector<size_t> O; // list of occupied mos (in so basis)
    std::vector<size_t> V; // list of virtual mos (in so basis)
```

Loop over irreps for orbital energies:
``` c++
    size_t offset = 0;
    for (int h = 0; h < nirrep; ++h) {
        size_t nocc_h = 2 * noccpi[h];
        size_t nmo_h = 2 * nmopi[h];
        for (size_t i = 0; i < nocc_h; ++i) {
            epsilon[ offset + i ] = epsilon_a->get(h,i/2);
            O.push_back( offset + i );
        }
        for (size_t a = nocc_h; a < nmo_h; ++a) {
            epsilon[ offset + a ] = epsilon_a->get(h,a/2);
            V.push_back( offset + a );
        }
        offset += nmo_h;
    }
```
