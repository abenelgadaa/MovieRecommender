#include "MovieDatabase.h"
#include "Movie.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;
//"/Users/omara/Desktop/Pnetphlix/movies.txt"

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

bool MovieDatabase::load(const string& filename)
{
    ifstream file("/home/koll/Downloads/Pnetphlix/Pnetphlix/movies.txt");
    for (int i=0; i<alreadyOpenedmovies.size();i++)
    {
        if(alreadyOpenedmovies[i]==filename)
            return false;
    }
    alreadyOpenedmovies.push_back(filename);
    
    int count = 0;
    string movie_id ="";
    string movie_title ="";
    string movie_date="";
    std::vector<std::string> movie_directors;
    std::vector<std::string> movie_actors;
    std::vector<std::string> movie_genres;
    float movie_rating = -99;
    
    string line;
    
    while (getline(file,line))
    {
        // std::cout << line << " " << count << std::endl;
        if (line=="")
            continue;
        //cout<<count<<endl;
        if (count == 0)
        {
            movie_id = to_lowercase(line);
            count++;
        }
        else if (count ==1)
        {
            movie_title = line;
            count++;
        }
        else if (count ==2)
        {
            movie_date = line;
            count++;
        }
        else if (count ==3)
        {
            std::stringstream ss(line);
            std::string director_name;
            while (std::getline(ss, director_name, ',')) {
                movie_directors.push_back(to_lowercase(director_name));
                
            }
            count++;
        }
            else if (count ==4)
            {
                std::stringstream ss(line);
                std::string actor_name;
                while (std::getline(ss, actor_name, ',')) {
                    movie_actors.push_back(to_lowercase(actor_name));
                    
                }
                count++;
//                for (const auto& actor : movie_actors) {
//                        std::cout << actor << '\n';
//                    }
            }
            else if (count==5)
            {
                    //    movie_date = line;
                    std::stringstream ss(line);
                    std::string genre_name;
                    while (std::getline(ss, genre_name, ','))
                    {
                        movie_genres.push_back(to_lowercase(genre_name));
                        
                    }
                count++;
                }
                else if(count==6)
                {
                    movie_rating = stof(line);
                    count++;
                    
                }
                //Movie::Movie(const string& id, const string& title, const string& release_year,
                //             const vector<string>& directors, const vector<string>& actors,
                //             const vector<string>& genres, float rating)
                if (count ==7)
                {
                    Movie* n = new Movie(movie_id, movie_title, movie_date,movie_directors,movie_actors,movie_genres,movie_rating);
                    m_movie.push_back(n);
                     // cout<<"about to insert"<<endl;
                    m_treemovie_id.insert(to_lowercase(movie_id),n);
                    for (const auto& director : movie_directors) {
                        if (!m_treemovie_director.find(director).is_valid()){
                            std::vector<Movie*> temporary;
                            temporary.push_back(n);
                            m_treemovie_director.insert(to_lowercase(director), temporary);
                        }
                        else
                        {
                            m_treemovie_director.find(director).get_value().push_back(n);
                        }
                    }
                    for (const auto& actor : movie_actors) {
                        if (!m_treemovie_actor.find(actor).is_valid()){
                            std::vector<Movie*> temporary2;
                            temporary2.push_back(n);
                            m_treemovie_actor.insert(to_lowercase(actor), temporary2);
                        }
                        else
                        {
                            m_treemovie_actor.find(actor).get_value().push_back(n);
                        }
                    }
                    for (const auto& genre : movie_genres) {
                        if (!m_treemovie_genre.find(genre).is_valid()){
                            std::vector<Movie*> temporary3;
                            temporary3.push_back(n);
                            m_treemovie_genre.insert(to_lowercase(genre), temporary3);
                        }
                        else
                        {
                            m_treemovie_genre.find(genre).get_value().push_back(n);
                        }
                    }
                      // cout<<"finished insert"<<endl;
                    count = 0;
                    movie_id = "";
                    movie_title ="";
                    movie_date="";
                    movie_directors.clear();
                    movie_rating=-99;
                    movie_actors.clear();
                    movie_genres.clear();
                }
            }
            //  std::cout << line << std::endl;
            return true;
        }
        // Replace this line with correct code.
    
    


Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string id_lowercase;
    std::transform(id.begin(), id.end(), std::back_inserter(id_lowercase), [](char c) { return std::tolower(c); });
    if( m_treemovie_id.find(id_lowercase).is_valid() == false)
        return nullptr;
    return m_treemovie_id.find(id_lowercase).get_value();
     // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string director_lowercase;
        std::transform(director.begin(), director.end(), std::back_inserter(director_lowercase), [](char c) { return std::tolower(c); });
    if( m_treemovie_director.find(director).is_valid() == false)
        return {};
    return (m_treemovie_director.find(director).get_value());;
}


vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string actor_lowercase;
        std::transform(actor.begin(), actor.end(), std::back_inserter(actor_lowercase), [](char c) { return std::tolower(c); });
    if( m_treemovie_actor.find(actor_lowercase).is_valid() == false)
        return {};
    return (m_treemovie_actor.find(actor_lowercase).get_value());;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string genre_lowercase;
        std::transform(genre.begin(), genre.end(), std::back_inserter(genre_lowercase), [](char c) { return std::tolower(c); });
    if( m_treemovie_genre.find(genre).is_valid() == false)
        return {};
    return (m_treemovie_genre.find(genre).get_value());;
}

//key = id of movie
//value = ptr to the movie 

