#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Recommender.h"
#include "Movie.h"
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

int main()
{
    
    //    UserDatabase udb;
    //    if (0&&!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    //    {
    //        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
    //        return 1;
    //    }
    
    UserDatabase udb;
    if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
    {
    	cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
    	return 1;
    }

    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))  // In skeleton, load always return false
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }

    Recommender movie_recommender(udb, mdb);
    cout << "Correctly intialized recommender" << endl;
    vector<MovieAndRank> recommendations = movie_recommender.recommend_movies("climberkip@gmail.com", 5);
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = mdb.get_movie_from_id(mr.movie_id);
            cout << i+1 << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n   Rating: "
            << m->get_rating() << "\n   Compatibility Score: "
            << mr.compatibility_score << "\n\n";
        }
    }
    cout << endl << endl <<"Correctly recommended movies" << endl;
    return 0;
    /*
    for (;;)
    {
        cout << "Enter actor (or quit): ";
        string director;
        getline(cin, director);
        if (director == "quit")
            return 0;
        vector<Movie*> u = mdb.get_movies_with_actor(director);
        if (u.empty())
            cout << "No director in the database has that email address." << endl;
        else
            for (int i = 0; i < u.size(); i++) {
                std::cout << u[i]->get_title() << endl;
            }
        //  cout << "Found " << u->get_title() << endl;
    }
    */

    //	for (;;)
    //	{
    //		cout << "Enter user email address (or quit): ";
    //		string email;
    //		getline(cin, email);
    //		if (email == "quit")
    //			return 0;
    //		User* u = udb.get_user_from_email(email);
    //		if (u == nullptr)
    //			cout << "No user in the database has that email address." << endl;
    //		else
    //			cout << "Found " << u->get_full_name() << endl;
    //	}
    //}
    //int main() {
    // TreeMultimap<std::string, int> tmm;
    // tmm.insert("carey", 5);
    // tmm.insert("carey", 6);
    // tmm.insert("carey", 7);
    // tmm.insert("david", 25);
    // tmm.insert("david", 425);
    // TreeMultimap<std::string,int>::Iterator it = tmm.find("carey");
    // // prints 5, 6, and 7 in some order
    // while (it.is_valid()) {
    // std::cout << it.get_value() << std::endl;
    // it.advance();
    // }
    //    std::cout << "HERE1" << std::endl;
    //it = tmm.find("laura");
    //    std::cout << "HERE2" << std::endl;
    //    if (!it.is_valid())
    // std::cout << "laura is not in the multimap!\n";
    //}
}
