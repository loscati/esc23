#ifndef GOOD_PARTICLE
#define GOOD_PARTICLE
#include <vector>
#include <string> 

struct GoodParticle {
  static int counter_;
  double x_, y_, z_;
  double px_, py_, pz_;
  bool hit_x_, hit_y_, hit_z_;
  float mass_;
  float energy_;
  int id_;
  std::string name_; 
};



struct  ParticleSoA{
    ParticleSoA(int N) {
      x_.resize(N);
      y_.resize(N);
      z_.resize(N);
      px_.resize(N);
      py_.resize(N);
      pz_.resize(N);
      hit_x_.resize(N);
      hit_y_.resize(N);
      hit_z_.resize(N);
      mass_.resize(N);
      energy_.resize(N);
      id_.resize(N);
      name_.resize(N);
  
    }  



    std::vector<double> x_, y_, z_;
    std::vector<double> px_,py_, pz_;
    std::vector<bool> hit_x_, hit_y_, hit_z_; 
    std::vector<float> mass_; 
    std::vector<float> energy_; 
    std::vector<int> id_; 
    std::vector<std::string> name_; 
};
#endif
