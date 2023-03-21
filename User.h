#ifndef USER_INCLUDED
#define USER_INCLUDED

#include <string>
#include <vector>

class User
{
  public:
    User(const std::string& full_name, const std::string& email,
         const std::vector<std::string>& watch_history) ;
    
    ~User() {}

    std::string get_full_name() const;
    std::string get_email() const;
    std::vector<std::string> get_watch_history() const;

  private:
        std::string full_name_;
       std::string email_;
       std::vector<std::string> watch_history_;

};

#endif // USER_INCLUDED
