#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP
#include "Form.hpp"
class PresidentialPardonForm : public Form {
 private:
 public:
  PresidentialPardonForm(const std::string target);
  PresidentialPardonForm(const PresidentialPardonForm& obj);
  ~PresidentialPardonForm();
  PresidentialPardonForm& operator=(const PresidentialPardonForm& obj);
  void execute(const Bureaucrat& executor) const;
  static Form* create(const std::string target);
};

#endif
