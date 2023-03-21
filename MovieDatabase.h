#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"
#include <cctype>
#include <algorithm>
class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase() {};
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    std::vector<Movie*> m_movie;
    std::vector<std::string> alreadyOpenedmovies;
    TreeMultimap <std::string, Movie*> m_treemovie_id;
    TreeMultimap <std::string, std::vector<Movie*>> m_treemovie_director;
    TreeMultimap <std::string, std::vector<Movie*>> m_treemovie_actor;
    TreeMultimap <std::string, std::vector<Movie*>> m_treemovie_genre;
    
    std::string to_lowercase( const std::string& s) {
        std::string result = s;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
};

#endif // MOVIEDATABASE_INCLUDED
