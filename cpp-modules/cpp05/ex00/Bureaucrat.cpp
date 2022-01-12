#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(const std::string name, int grade) : name(name) {
  if (grade < 1) throw Bureaucrat::GradeTooLowException();
  if (grade > 150) throw Bureaucrat::GradeTooHighException();
  this->grade = grade;
}
Bureaucrat::Bureaucrat(const Bureaucrat& obj) : name(obj.name) {
  this->grade = obj.grade;
}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& obj) {
  this->grade = obj.grade;
  return (*this);
}

const std::string& Bureaucrat::getName(void) const { return (this->name); }

const int& Bureaucrat::getGrade(void) const { return (this->grade); }

void Bureaucrat::increaseGrade(int amount) {
  if (this->grade - amount < 1)
    throw Bureaucrat::GradeTooLowException();
  else if (this->grade - amount > 150)
    throw Bureaucrat::GradeTooHighException();
  this->grade -= amount;
}

void Bureaucrat::decreaseGrade(int amount) {
  if (this->grade + amount < 1)
    throw Bureaucrat::GradeTooLowException();
  else if (this->grade + amount > 150)
    throw Bureaucrat::GradeTooHighException();
  this->grade += amount;
}

std::ostream& operator<<(std::ostream& stream, const Bureaucrat& obj) {
  stream << obj.getName() << ": " << obj.getGrade();
  return (stream);
}

// std::ostream& operator<<(const Bureaucrat& obj, std::ostream& stream) {
//   stream << obj.getName() << ": " << obj.getGrade();
//   return (stream);
// }