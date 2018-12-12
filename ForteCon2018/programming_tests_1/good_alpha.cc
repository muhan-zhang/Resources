// some reference determinant space, 
std::vector<Determinant> P_dets = ... 
std::vector<double> P_coeffs = ... 

det_hash<double> V_hash;                                                          
for (size_t P = 0; P < P_dets.size(); ++P) {                                      
    const Determinant& det(P_dets[P]);                                              
    const double& Cp = P_coeffs[P];                                                   
                                                                                    
    std::vector<int> aocc = det.get_alfa_occ(nact_);                                
    std::vector<int> avir = det.get_alfa_vir(nact_);                                
    
    // Precompute sizes                                                                                
    int noalpha = aocc.size();                                                      
    int nvalpha = avir.size();                                                      

    // Precompute copy
    Determinant new_det(det);                                                       

    // Generate alpha excitations                                                   
    for (int i = 0; i < noalpha; ++i) {                                             
        int ii = aocc[i];                                                           
        for (int a = 0; a < nvalpha; ++a) {                                         
            int aa = avir[a];                                                      
            if ((mo_symmetry_[ii] ^ mo_symmetry_[aa]) == 0) {                       
                double HIJ = fci_ints_->slater_rules_single_alpha(det, ii, aa) * Cp;
                if (std::abs(HIJ) >= screen_thresh_) {                              
                    new_det = det;                                                  
                    new_det.set_alfa_bit(ii, false);                                
                    new_det.set_alfa_bit(aa, true);                                 
                    V_hash[new_det] += HIJ;                                       
                }                                                                   
            }                                                                       
        }                                                                           
    }
}
