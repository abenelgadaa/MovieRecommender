#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating)
{
    id_=id;
    title_=title;
    release_year_=release_year;
    director_=directors;
    actors_=actors;
    genres_=genres;
    rating_=rating;// Replace this line with correct code.
}

string Movie::get_id() const
{
    return id_;  // Replace this line with correct code.
}

string Movie::get_title() const
{
    return title_;  // Replace this line with correct code.
}

string Movie::get_release_year() const
{
    return release_year_;  // Replace this line with correct code.
}

float Movie::get_rating() const
{
    return rating_;  // Replace this line with correct code.
}

vector<string> Movie::get_directors() const
{
    return director_;  // Replace this line with correct code.
}

vector<string> Movie::get_actors() const
{
    return actors_;  // Replace this line with correct code.
}

vector<string> Movie::get_genres() const
{
    return genres_;  // Replace this line with correct code.
}
