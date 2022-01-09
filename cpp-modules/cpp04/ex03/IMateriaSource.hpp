#if !defined(IMATERIASOURCE_HPP)
#define IMATERIASOURCE_HPP
#include "AMateria.hpp"

class IMateriaSource {
 private:
 public:
  virtual ~IMateriaSource() {}
  virtual void learnMateria(AMateria* m) = 0;
  virtual AMateria* createMateria(std::string const& type) = 0;
};

#endif