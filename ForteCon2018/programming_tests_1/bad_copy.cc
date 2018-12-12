#include <complex>
#include <iomanip>
#include <sstream>
#include <stdlib.h>

#include "psi4/libmints/molecule.h"
#include "psi4/libmints/pointgrp.h"
#include "psi4/libpsi4util/process.h"
#include "psi4/libpsio/psio.hpp"

#include "../helpers/printing.h"
#include "tdaci.h"

namespace psi { namespace forte {

ACI::ACI(SharedWavefunction ref_wfn, Options& options, std::shared_ptr<ForteIntegrals> ints, std::shared_ptr<MOSpaceInfo> mo_space_info) : Wavefunction(options), ints_(ints), mo_space_info_(mo_space_info) {
    // Copy the wavefunction information
    shallow_copy(ref_wfn);
    wfn_ = ref_wfn;
}

ACI::~ACI() {}

// Francesco, shield your eyes
double ACI::compute_overlap( vector<Determinant> &wfn1, vector<double> &coeffs1, std::vector<Determinant> &wfn2, std::vector<double> &coeffs2 ) {



    double overlap, Ca, Cb;
    
    overlap = 0.0;
    for( size_t A = 0; A < wfn1.size(); ++A )
    {   
      for( size_t B = 0; B < wfn2.size(); ++B ) {
        Determinant detA = wfn1[A]; 
        Ca = coeffs1[A];

        Determinant detB = wfn2[B]; 
        Cb = coeffs2[B];

        if( detA == detB ){
           overlap += Ca*Cb; 

        }

      }  
    }

    return overlap;
}


    


}  }
