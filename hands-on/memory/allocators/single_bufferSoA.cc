#include <cstring>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

class ParticleSoA {
public:
  ParticleSoA() = delete;
  // Constructor that takes the size and allocates memory
  ParticleSoA(size_t numParticles) : size(numParticles) {
    // Calculate the size required for the memory buffer
    size_t bufferSize =
        numParticles *
        (3 * sizeof(double) + 3 * sizeof(double) + 3 * sizeof(bool) +
         2 * sizeof(float) + sizeof(int) +
         sizeof(char) * 256 // maximum of 255 charachters for my string
        ); //no padding here!
    
    size_t padding = (alignof(float) - bufferSize % alignof(float)) % alignof(float);
    buffer = std::aligned_alloc(alignof(double), bufferSize + padding);

    // Set pointers to the beginning of each column
    char *currentPtr =
        static_cast<char *>(buffer); // keep this pointer a char for consistency
                                     // when moving around the pointer
    x = reinterpret_cast<double *>(currentPtr);
    currentPtr += numParticles * sizeof(double);
    y = reinterpret_cast<double *>(currentPtr);
    currentPtr += numParticles * sizeof(double);
    z = reinterpret_cast<double *>(currentPtr);
    currentPtr += numParticles * sizeof(double);
    px = reinterpret_cast<double *>(currentPtr);
    currentPtr += numParticles * sizeof(double);
    py = reinterpret_cast<double *>(currentPtr);
    currentPtr += numParticles * sizeof(double);
    pz = reinterpret_cast<double *>(currentPtr);
    currentPtr += numParticles * sizeof(double);
    hit_x = reinterpret_cast<bool *>(currentPtr);
    currentPtr += numParticles * sizeof(bool);
    hit_y = reinterpret_cast<bool *>(currentPtr);
    currentPtr += numParticles * sizeof(bool);
    hit_z = reinterpret_cast<bool *>(currentPtr);
    currentPtr += numParticles * sizeof(bool);
    currentPtr += padding; 
    mass = reinterpret_cast<float *>(currentPtr);
    currentPtr += numParticles * sizeof(float);
    energy = reinterpret_cast<float *>(currentPtr);
    currentPtr += numParticles * sizeof(float);
    id = reinterpret_cast<int *>(currentPtr);
    currentPtr += numParticles * sizeof(int);
    name = reinterpret_cast<std::string *>(
        currentPtr); // remember: std::string needs to be CONSTRUCTED!

    std::cout << " x " << x << "\n";
    std::cout << " y " << y << "\n";
    std::cout << " z " << z << "\n";
    std::cout << " px " << px << "\n";
    std::cout << " py " << py << "\n";
    std::cout << " pz " << pz << "\n";
    std::cout << " hit_x " << hit_x << "\n";
    std::cout << " hit_y " << hit_y << "\n";
    std::cout << " hit_z " << hit_z << "\n";
    std::cout << " mass " << mass << "\n";
    std::cout << " energy " << energy << "\n";
    std::cout << " id " << id << "\n";
    std::cout << "name " << name << "\n";
  }
  // defining data members
  size_t size;
  double *x;
  double *y;
  double *z;
  double *px;
  double *py;
  double *pz;
  float *mass;
  float *energy;
  bool *hit_x;
  bool *hit_y;
  bool *hit_z;
  int *id;
  std::string *name;

  // Destructor to free the allocated memory
  ~ParticleSoA() { std::free(buffer); }

private:
  void *buffer;
};

void initializeSoA(ParticleSoA &particles, const std::vector<double> &pxDist,
                   const std::vector<double> &xDist,
                   const std::vector<double> &yDist,
                   const std::vector<double> &zDist,
                   const std::vector<double> &massDist, int Npart) {

  particles.name =
      new (particles.name) std::string[Npart]; // constructing the string!
  for (int i = 0; i < Npart; ++i) {
    particles.id[i] = i;
    particles.px[i] = pxDist[i];
    particles.py[i] = pxDist[i];
    particles.pz[i] = pxDist[i];
    particles.x[i] = xDist[i];
    particles.y[i] = yDist[i];
    particles.z[i] = zDist[i];
    particles.mass[i] = massDist[i];
    particles.name[i] = "Particle" + std::to_string(i);
    particles.energy[i] = 0.;
  }
}

int main() {
  int N = 17;
  ParticleSoA p(N);
  std::random_device rd;
  std::mt19937 gen(1);

  // creating some random vectors
  std::vector<double> pxDist;
  std::vector<double> xDist;
  std::vector<double> zDist;
  std::vector<double> yDist;
  std::vector<double> massDist;
  std::vector<double> timeDist;

  // utility function for filling the vectors
  auto fillVec = [N, &gen](std::vector<double> &vec, double min,
                           double max) -> void {
    for (int i = 0; i < N; ++i) {
      std::uniform_real_distribution<double> dist(min, max);
      vec.push_back(dist(gen));
    }
  };

  fillVec(pxDist, 10., 100.);
  fillVec(xDist, -100., 100.);
  fillVec(yDist, -100., 100.);
  fillVec(zDist, -300., 300.);
  fillVec(massDist, 10., 100.);
  fillVec(timeDist, -10., 10.);

  // Filling the SoA
  initializeSoA(p, pxDist, xDist, yDist, zDist, massDist, N);
  for (int i = 0; i < N; ++i) {
    // printing out to check everything works as expected
    std::cout << " Name  " << p.name[i] << "\n";
    std::cout << " X " << p.x[i] << "\n";
  }
  std::destroy_at(p.name); // destructing the string!

} // destructor called here, no memory leaks
