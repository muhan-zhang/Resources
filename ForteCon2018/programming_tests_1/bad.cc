#include <iomanip>
#include <sstream>
#include <stdlib.h>

#include "psi4/libmints/molecule.h"
#include "psi4/libmints/pointgrp.h"
#include "psi4/libpsi4util/process.h"
#include "psi4/libpsio/psio.hpp"

#include "../helpers/printing.h"
#include "aci.h"

namespace psi {
namespace forte {

ACI::ACI(SharedWavefunction ref_wfn, Options& options, std::shared_ptr<ForteIntegrals> ints,
         std::shared_ptr<MOSpaceInfo> mo_space_info)
    : Wavefunction(options), ints_(ints), mo_space_info_(mo_space_info) {
    // Copy the wavefunction information
    shallow_copy(ref_wfn);
    wfn_ = ref_wfn;
}

ACI::~ACI() {}

double ACI::compute_overlap(std::vector<Determinant>& wfn1, std::vector<double>& coeffs1,
                            std::vector<Determinant>& wfn2, std::vector<double>& coeffs2) {

    double overlap = 0.0;

    size_t maxB = wfn2.size();

    for (size_t A = 0, maxA = wfn1.size(); A < maxA; ++A) {
        const Determinant& detA = wfn1[A];
        const double Ca = coeffs1[A];
        for (size_t B = 0; B < maxB; ++B) {

            const Determinant& detB = wfn2[B];

            if (detA == detB) {
                const double Cb = coeffs2[B];
                overlap += Ca * Cb;
                break; // Stop looping over B
            }
        }
    }

    return overlap;
}
}
}
