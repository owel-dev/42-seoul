#include "Bureaucrat.hpp"

#include <iostream>

#include "Form.hpp"
#include "GradeException.hpp"

Bureaucrat::Bureaucrat(const std::string name, int grade) : name(name) {
  if (grade < 1) throw GradeTooLowException();
  if (grade > 150) throw GradeTooHighException();
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
    throw GradeTooLowException();
  else if (this->grade - amount > 150)
    throw GradeTooHighException();
  this->grade -= amount;
}

void Bureaucrat::decreaseGrade(int amount) {
  if (this->grade + amount < 1)
    throw GradeTooLowException();
  else if (this->grade + amount > 150)
    throw GradeTooHighException();
  this->grade += amount;
}

void Bureaucrat::signForm(Form& obj) {
  try {
    obj.beSigned(*this);
    std::cout << this->name << " signs " << obj.getName() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << this->name << " cannot sign " << obj.getName() << " ";
    throw;
  }
}

void Bureaucrat::executeForm(Form const& form) {
  try {
    form.execute(*this);
    std::cout << form.getTarget() << " " << form.getName() << " execute seccess"
              << std::endl;
  } catch (std::exception e) {
    std::cout << form.getTarget() << " " << form.getName() << " execute fail ";
    throw;
  }
}

std::ostream& operator<<(std::ostream& stream, const Bureaucrat& obj) {
  stream << "name: " << obj.getName() << ", "
         << "grade: " << obj.getGrade();
  return (stream);
}
