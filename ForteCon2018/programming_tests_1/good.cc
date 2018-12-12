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

double ACI::compute_overlap_vector(std::vector<Determinant>& wfn1, std::vector<double>& coeffs1,
                                   std::vector<Determinant>& wfn2, std::vector<double>& coeffs2) {

    double overlap = 0.0;
    for (size_t I = 0, max_I = wfn1.size(); I < max_I; ++I) {
        const Determinant& detI = wfn1[I];
        const double& cI = coeffs1[I];
        for (size_t J = 0, max_J = wfn2.size(); J < max_J; ++J) {
            const Determinant& detJ = wfn2[J];
            if (detI == detJ) {
                cJ = coeffs2[J];
                overlap += cI * cJ;
            }
        }
    } // end loop over determinants

    return overlap;
}

// How it's really done
double ACI::compute_overlap_hash(DeterminantHashVec& wfn1, std::vector<double>& coeffs1,
                                 DeterminantHashVec& wfn2, std::vector<double>& coeffs2) {

    double overlap = 0.0;
    const det_hashvec& dets1 = wfn1.wfn_hash();
    for (size_t I = 0, max_I = dets1.size(); I < max_I; ++I) {
        const Determinant& detI = dets1[I];
        if( wfn2.has_det(detI){
            size_t idx2 = wfn2.get_idx(detI);
            overlap += coeffs1[I] * coeffs2[idx2];
        }
    }
    return overlap;
}

}
}
