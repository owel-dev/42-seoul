#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP
#include "Bureaucrat.hpp"
#include "Form.hpp"

class RobotomyRequestForm : public Form {
 private:
 public:
  RobotomyRequestForm(const std::string target);
  RobotomyRequestForm(const RobotomyRequestForm& obj);
  ~RobotomyRequestForm();
  RobotomyRequestForm& operator=(const RobotomyRequestForm& obj);
  void execute(const Bureaucrat& executor) const;
  static Form* create(const std::string target);
};

#endif
