// some reference determinant space, 
std::vector<Determinant> P_dets = ... 
std::vector<double> P_coeffs = ... 

det_hash<double> V_hash;                                                          
for (size_t P = 0; P < P_dets.size(); ++P) {                                      
    Determinant det(P_dets[P]);                                              
    double Cp = P_coeffs[P];                                                   
                                                                                    
    std::vector<int> aocc = det.get_alfa_occ(nact_);                                
    std::vector<int> avir = det.get_alfa_vir(nact_);                                

    // Generate alpha excitations                                                   
    for (int i = 0; i < aocc.size(); ++i) {                                             
        for (int a = 0; a < avir.size(); ++a) {                                         
            // absolute indices
            int ii = aocc[i];                                                           
            int aa = avir[a];                                                      
            
            // Do the excitation
            det.set_alfa_bit(ii, false);                                
            det.set_alfa_bit(aa, true);                                 

            // Get matrix element
            double HIJ = fci_ints_->slater_rules_single_alpha(det, ii, aa);
        
            // Add to hash if correct symmetry/magnitude
            if (std::abs(HIJ * Cp) >= screen_thresh_) {                              
                if ((mo_symmetry_[ii] ^ mo_symmetry_[aa]) == 0) {                       
                    V_hash[det] += HIJ * Cp;                                       
    
                    // Rebuild original determinant
                    det.set_alfa_bit(ii, true);                                
                    det.set_alfa_bit(aa, false);                                 
                }                                                                   
            }                                                                       
        }                                                                           
    }
}
