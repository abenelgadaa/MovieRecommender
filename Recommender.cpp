#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    user_database_ = user_database;
    movie_database_ = movie_database;
}

// 3 Helper functions
bool exists(string x, set<string>& my_set){
    return find(my_set.begin(), my_set.end(),x)!=my_set.end();
}
bool exists_vector(string x, vector<string>& my_vector){
    return find(my_vector.begin(), my_vector.end(),x)!=my_vector.end();
}
set<string> convertToSetAndLower(vector<string> vector)
{
    set<string> my_set;
    for (string x : vector) {
        string x_lower;
        transform(x.begin(), x.end(), back_inserter(x_lower), [](char c) { return tolower(c); });
        my_set.insert(x_lower);
    }
    return my_set;
}

// This structure is used for handling and storing movie details and its compatibility
struct movie_with_info_and_compatibility{
    movie_with_info_and_compatibility(const string& movie_id, const string& movie_title, int& compatibility_score, const float& movie_rating)
     : id(movie_id), compatibility(compatibility_score), rating(movie_rating), title(movie_title)
    {}
    string id, title;
    int compatibility;
    float rating;
};

// This function is used for sorting the movies by their compatibilities, rating and title
bool cmp(movie_with_info_and_compatibility& a,
        movie_with_info_and_compatibility& b)
{
    if (a.compatibility > b.compatibility) return true;
    else if (a.compatibility < b.compatibility) return false;
    else{
        if (a.rating > b.rating) return true;
        else if (a.rating < b.rating) return false;
        else{
            if (a.title.compare(b.title) < 0) return true;
            else return false;
        }
    }
}

// This function returns the compatibility score between two movies ( 20 for director similarity, 30 for actor similarity, 1 for genre similarity)
int compare_two_movies(const Movie* movie1, const Movie* movie2){
    int compatibility = 0;
    vector<string> directors1 = movie1->get_directors();
    vector<string> actors1 = movie1->get_actors();
    vector<string> genres1 = movie1->get_genres();
    vector<string> directors2 = movie2->get_directors();
    vector<string> actors2 = movie2->get_actors();
    vector<string> genres2 = movie2->get_genres();
    for (auto director : directors1){
        if (exists_vector(director, directors2)) compatibility+= 20;
    }
    for (auto actor : actors1){
        if (exists_vector(actor, actors2)) compatibility+= 30;
    }
    for (auto genre : genres1){
        if (exists_vector(genre, genres2)) compatibility+= 1;
    }
    return compatibility;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count)const
{
    // Getting watch history and storing all their directors actors and genres without duplicates ( using sets )
    User* u = user_database_.get_user_from_email(user_email);
    vector<string> watch_history = u->get_watch_history();
    set<string> watch_history_set = convertToSetAndLower(watch_history);
    set<string> directors;
    set<string> actors;
    set<string> genres;

    for (auto &history_movie_id : watch_history_set){
        Movie* movie = movie_database_.get_movie_from_id(history_movie_id);
        if (movie != nullptr){
            vector<string> movie_directors = movie->get_directors();
            vector<string> movie_actors = movie->get_actors();
            vector<string> movie_genres = movie->get_genres();
            for (auto &director : movie_directors){
                directors.insert(director);
            }
            for (auto &actor : movie_actors){
                actors.insert(actor);
            }
            for (auto &genre : movie_genres){
                genres.insert(genre);
            }
            
        }
        else{
            continue;
            //cout << "Could not find the movie, with id: " << history_movie_id << endl;
        } 
    }
    // Getting all the movies that have 1 property in common (this means we only get movies that have at least 1 point of compatibility)
    set<string> similar_movies;
    for (auto &director : directors){
        vector<Movie*> movies = movie_database_.get_movies_with_director(director);
        for (auto &movie : movies){
            string movie_id = movie->get_id();
            if (!exists(movie_id, watch_history_set))
                similar_movies.insert(movie_id);
        }
    }
    for (auto &actor : actors){
        vector<Movie*> movies = movie_database_.get_movies_with_actor(actor);
        for (auto &movie : movies){
            string movie_id = movie->get_id();
            if (!exists(movie_id, watch_history_set))
                similar_movies.insert(movie_id);
        }
    }
    for (auto &genre : genres){
        vector<Movie*> movies = movie_database_.get_movies_with_genre(genre);
        for (auto &movie : movies){
            string movie_id = movie->get_id();
            if (!exists(movie_id, watch_history_set))
                similar_movies.insert(movie_id);
        }
    }
    // Calculating the compatibility of each similar movie
    vector<movie_with_info_and_compatibility> similar_movies_compatibilities;
    for (auto & similar_movie_id : similar_movies){
        Movie* similar_movie = movie_database_.get_movie_from_id(similar_movie_id);
        int compatibility = 0;
        for (auto &history_movie_id : watch_history_set){
            Movie* history_movie = movie_database_.get_movie_from_id(history_movie_id);
            if (history_movie != nullptr) {
                vector<string> directors = history_movie->get_directors();
                compatibility += compare_two_movies(history_movie, similar_movie);
            }
            else continue;
        }
        movie_with_info_and_compatibility my_element(similar_movie_id, similar_movie->get_title(), compatibility, similar_movie->get_rating());

        similar_movies_compatibilities.push_back(my_element);
    }
    
    // Sorting the vector containing similar movies with their compatibility
    sort(similar_movies_compatibilities.begin(), similar_movies_compatibilities.end(), cmp);

    // Getting the first n recommended movies
    vector<MovieAndRank> recommended_movies;
    for (int i = 0; i<movie_count; i++){
        if (i < similar_movies_compatibilities.size()){
            MovieAndRank recommended_movie(similar_movies_compatibilities[i].id, similar_movies_compatibilities[i].compatibility);
            recommended_movies.push_back(recommended_movie);
        }
        else break;
    }

    
    return recommended_movies;  // Replace this line with correct code.
}
