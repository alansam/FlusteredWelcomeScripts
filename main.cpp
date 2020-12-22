
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cstdlib>

class Comparable {
public:
/*
  virtual
  int compare( Comparable & f1, Comparable & f2) = 0;
  virtual
  int totalWeight() = 0;
*/

  virtual
  int compare(Comparable const & that) const = 0;
  virtual
  int totalWeight() const = 0;
};

//In the derived class I implement the method compare()
class FreightTrainRoute : public Comparable {
protected:
  int nbOfWagons;
  float * weightPerWagon = nullptr;

public:
  FreightTrainRoute(int const nrw = 0, float * wpw = nullptr)
  : nbOfWagons(nrw), weightPerWagon(wpw) {
    std::cout << ". " << __func__ << std::endl;
    if (weightPerWagon != nullptr) {
      weightPerWagon = new float[nrw];
      std::cout << std::setw(5)
                << nbOfWagons
                << ' '
                << weightPerWagon
                << '\n'
                << std::endl;
    // deep copy
      for (size_t w_ = 0; w_ < nrw; ++w_) {
        weightPerWagon[w_] = wpw[w_];
      }
    }
    else {
      nbOfWagons = 0;
    }
    return;
  }

  virtual
  ~FreightTrainRoute() {
    std::cout << ". " << __func__ << std::endl;
    if (weightPerWagon != nullptr) {
      std::cout << "-- deleting " << weightPerWagon << std::endl;
      delete [] weightPerWagon;
      weightPerWagon = nullptr;
    }
  }

  int totalWeight() const override {
    std::cout << ". " << __func__ << std::endl;
      std::cout << std::setw(5)
                << nbOfWagons
                << ' '
                << weightPerWagon
                << '\n'
                << std::endl;
    int tw = 0;
    float total = 0;
    int count = 0;
    if (weightPerWagon != nullptr) {
      for (int i = 0; i < nbOfWagons; i++) {
        total += weightPerWagon[i];
        count++;
      }
      tw = static_cast<int>(total);
    }
    else {
//      weightPerWagon = nullptr;
      tw = 0;
    }
    std::cout << "Total weight: " << tw << std::endl;
    return tw;
  }
//Error here: C2061 syntax error: identifier 'FreightTrainRoute' for f1
/*
  bool compare( FreightTrainRoute & f1, FreightTrainRoute & f2) override
  {
    if (f1.totalWeight() < f2.totalWeight()) {
      return -1;
    }
    else if(f1.totalWeight() == f2.totalWeight()) {
      return 0;
    }
    return 1;
  }
*/
  int compare(Comparable const & that) const override {
    std::cout << __func__ << std::endl;
    int w_this = totalWeight();
    int w_that = that.totalWeight();

    if (w_this < w_that) {
      return -1;
    }
    else if(w_this == w_that) {
      return 0;
    }
    return 1;
  }
};

std::string resolve(int comp) {
  std::string re;
  re = comp == 0 ? "equal"
     : comp > 0 ? "greater"
     : "less";
  return re;
}

int main(int argc, char const * argv[]) {
  int nrw1 = 10;
  int nrw2 = 110;
  int cc;
  int const cc_max = 10;
  auto wpw1 = std::make_unique<float []>(nrw1);
  if (!wpw1) {
    std::exit(EXIT_FAILURE);
  }
  std::cout << wpw1.get() << std::endl;
  auto wpw2 = std::unique_ptr<float []>(new float[nrw2]);
  if (!wpw2) {
    std::exit(EXIT_FAILURE);
  }
  std::cout << wpw2.get() << std::endl;

  for (size_t w_ = 0; w_ < nrw1; ++w_) {
    wpw1[w_] = 100.0F;
  }
  cc = 10;
  for (size_t w_ = 0; w_ < nrw1; ++w_) {
    std::cout << std::setw(5) << wpw1[w_]
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << '\n' << std::endl;

  for (size_t w_ = 0; w_ < nrw2; ++w_) {
    wpw2[w_] = 110.0F;
  }
  cc = 10;
  for (size_t w_ = 0; w_ < nrw2; ++w_) {
    std::cout << std::setw(5) << wpw2[w_]
              << (++cc % cc_max == 0 ? "\n" : "");
  }
  std::cout << '\n' << std::endl;

  FreightTrainRoute tr1(nrw1, wpw1.get());

  FreightTrainRoute tr2(nrw2, wpw2.get());

  int comp;
  comp = tr1.compare(tr2);
  std::cout << "\nCompare: " << resolve(comp) << '\n' << std::endl;

  comp = tr2.compare(tr1);
  std::cout << "\nCompare: " << resolve(comp) << '\n' << std::endl;

  comp = tr1.compare(tr1);
  std::cout << "\nCompare: " << resolve(comp) << '\n' << std::endl;

  return 0;
}
