#ifndef FORM_HPP
#define FORM_HPP
#include <iostream>

class Bureaucrat;

class Form {
 private:
  const std::string name;
  bool isSign;
  const int signGrade;
  const int execGrade;
  const std::string target;

 public:
  Form(const std::string name, int signGrade, int execGrade,
       const std::string target);
  Form(const Form& obj);
  ~Form();
  Form& operator=(const Form& obj);
  const std::string& getName(void) const;
  const bool& getIsSign(void) const;
  const int& getSignGrade(void) const;
  const int& getExecGrade(void) const;
  const std::string& getTarget(void) const;
  void beSigned(const Bureaucrat& obj);
  void checkForm(Bureaucrat const& executor) const;
  virtual void execute(Bureaucrat const& executor) const = 0;
};

std::ostream& operator<<(std::ostream& stream, const Form& obj);
const std::string form_name[3] = {
    "ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
#endif
