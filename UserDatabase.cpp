#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename)
{

    ifstream file("/home/koll/Downloads/Pnetphlix/Pnetphlix/users.txt");
    for (int i=0; i<alreadyOpened.size();i++)
    {
        if(alreadyOpened[i]==filename)
            return false;
    }
//    file.open(filename,ios::in);
 //   std::cout  << (file.rdstate() & std::ifstream::failbit) << std::endl;
    alreadyOpened.push_back(filename);
    
    int count = 0;
    string name="";
    string email="";
    int size = -99;
    std::vector<std::string> movie_history;
    string line;
    
    while (getline(file,line))
    {
       // std::cout << line << " " << count << std::endl;
        if (line=="")
            continue;
        if (count == 0)
        {
            name = line;
            count++;
        }
        else if (count ==1)
        {
            email = line;
            count++;
        }
        else if(count==2)
        {
      //      cout << line << endl;
            size = stoi(line);
            count++;
            
        }
        else if (line!="")
        {
            movie_history.push_back(line);
            count++;
        }
        if (count ==3+size)
        {
            User* n = new User(name, email, movie_history);
          //  cout<<"about to insert"<<endl;
            m_tree.insert(email,n);
         //   cout<<"finished insert"<<endl;
            count = 0;
            name = "";
            email = "";
            size=-99;
            movie_history.clear();
        }
    }
  //  std::cout << line << std::endl;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if( m_tree.find(email).is_valid() == false)
        return nullptr;
    return m_tree.find(email).get_value();// Replace this line with correct code.
}
