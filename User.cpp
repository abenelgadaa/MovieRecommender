#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    full_name_= full_name;
    email_=email;
    watch_history_=watch_history;
//   for (int i=0; i<watch_history_.size(); i++)
//        watch_history.push_back(watch_history_[i]);
    // Replace this line with correct code.
}

string User::get_full_name() const
{
    return full_name_;
  // Replace this line with correct code.
}

string User::get_email() const
{
    return email_;
// Replace this line with correct code.
}

vector<string> User::get_watch_history() const
{
    return watch_history_;
  // Replace this line with correct code.
}
