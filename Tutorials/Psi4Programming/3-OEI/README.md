(AO) h<sub>μν</sub>


Include the headers:
```c++
#include "psi4/libmints/factory.h"
```

Grab one-electron integrals from mintshelper:

```c++
    // Grab kinetic and 1e potential ints in AO basis
    SharedMatrix T = SharedMatrix(ref_wfn -> matrix_factory() -> create_matrix(PSIF_SO_T) );
    SharedMatrix V_oe = SharedMatrix(ref_wfn -> matrix_factory() -> create_matrix(PSIF_SO_V) );

    MintsHelper mints(ref_wfn);
    T = mints.so_kinetic();
    V_oe = mints.so_potential();
```

h = T<sub>e</sub> + V<sub>en</sub> :

```
    // Now build alpha/beta oei in AO basis
    SharedMatrix Ha = T->clone();
    SharedMatrix Hb = T->clone();

    Ha->add(V_oe);
    Hb->add(V_oe);
```

Transform H to MO basis, h<sub>pq</sub> = C<sub>pμ</sub>h<sub>μν</sub>C<sub>νq</sub> :

```
    // Now transform Ha/Hb to MO basis
    // First grab C matrices
    SharedMatrix Ca = ref_wfn->Ca();
    SharedMatrix Cb = ref_wfn->Cb();

    // CaHaCa^(T)
    Ha->transform(Ca);
    Hb->transform(Cb);
```

Transform one-electron integral to spin-orbital representation.

```c++
    // Build oeis in spin-orbital basis
    size_t nso2 = nso * nso;
    std::vector<double> so_oeis(nso2, 0.0);
    Dimension nmopi = ref_wfn->nmopi();
    size_t offset = 0;
    for (int h = 0; h < nirrep; ++h) {
        size_t nmo_h = 2 * nmopi[h];
        for (size_t p = 0; p < nmo_h; ++p) {
            size_t p_orb = so_labels[p].first;
            size_t p_spin = so_labels[p].second;
            for (size_t q = 0; q < nmo_h; ++q) {
                size_t q_orb = so_labels[q].first;
                size_t q_spin = so_labels[q].second;
                if ( p_spin == q_spin ){
                    double value = (p_spin == 0) ? Ha->get(h, p_orb, q_orb) : Hb->get(h, p_orb, q_orb);
                    so_oeis[two_idx(offset+p, offset+q, nso)] = value;
                }
            }
        }
        offset += nmo_h;
    }

```

Build Fock matrix F<sub>pq</sub> = h<sub>pq</sub> + Σ<pr||qr>:

```c++
    // Build Fock matrix in MO basis
    SharedMatrix F(std::make_shared<Matrix>("Fock", nso, nso));

    for (size_t p = 0; p < nso; ++p) {
        for (size_t q = 0; q < nso; ++q) {
            double value = so_oeis[two_idx(p, q, nso)];

            for (size_t r: O ){
                value += so_ints[four_idx(p, r, q, r, nso)];
            }

            F->set(p, q, value);
        }
    }
```

Extract orbital energies from Fock matrix:

```c++
    std::vector<double> epsilon(nso, 0.0);

    for (size_t p = 0; p < nso; ++p) {
        epsilon[p] = F->get(p,p);
    }
```
