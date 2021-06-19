#ifndef LibrarySystem
#define LibrarySytem
#include <string>
using namespace std;
struct Movie{
    int movieId;
    string movieTitle;
    int movieYear;
    int check;
    Movie* next;
};

struct Checkedout{
    int movieId;
    int movieYear;
    string movieTitle;
    int userId;
    Checkedout* next;
};

struct User{
    int userId;
    string userName;
    User* next;
};
vector<string> parserFile(string str);
void control(string cmd,string oupt);
bool controlMovie(int id);
void addMovie(const int movieId,const string movieTitle,const int year);
void deleteForMovieFromCheckList(int movieId);
void deleteMovie( const int movieId);
bool controlUser(int id);
void addUser(const int userId,const string userName);
void deleteForUserFromCheckList(int userId);
void deleteUser(const int userId);
void checkOutMovie(const int movieId,const int userId);
void returnMovie(const int movieId);
void showAllMovie();
void showMovie(const int movieId);
void showUser(const int userId);
void clearLists(Movie* m,User *u,Checkedout *c);
#endif