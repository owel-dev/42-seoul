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

 public:
  Form(const std::string name, int signGrade, int execGrade);
  Form(const Form& obj);
  ~Form();
  Form& operator=(const Form& obj);
  const std::string& getName(void) const;
  const bool& getIsSign(void) const;
  const int& getSignGrade(void) const;
  const int& getExecGrade(void) const;
  void beSigned(const Bureaucrat& obj);

  // class GradeTooLowException : std::exception {
  //  public:
  //   const char* what() const throw() { return ("Throw
  //   GradeTooLowException!"); }
  // };
};

std::ostream& operator<<(std::ostream& stream, const Form& obj);

#endif
