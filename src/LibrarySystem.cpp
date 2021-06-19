#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LibrarySystem.h"
using namespace std;

class LibrarySystem{
    private:
    Movie* movieList;
    User* userList;
    Checkedout* checkedoutList;
    int forMovie;
    int forUser;
    int forCheckedout;
    int forMessage;
    ofstream fout;

    public:
    LibrarySystem(){
        movieList = nullptr;
        userList = nullptr;
        checkedoutList = nullptr;
        forMovie=0,forUser=0,forCheckedout=0,forMessage=1;
    }
    ~LibrarySystem(){

    }

    vector<string> parserFile(string str){
        vector<string> wordArr;
        string word = "";
        for (auto x : str) 
        {
            if (x == '\t'){
                wordArr.push_back(word);
                word = "";
            }
            else {
                word = word + x;
            }
        }
        wordArr.push_back(word);
        return wordArr;
    }

    void control(string cmd,string oupt){
        ifstream input(cmd);
        fout.open(oupt);
        fout << "===Movie Library System===" << endl;
        int a = 0,b = 0,c = 0,d = 0,e = 0,f = 0,g = 0,h = 0,k = 0;

        for ( string line; getline(input, line);){
            vector<string> wordArr = parserFile(line);
            
            if ( wordArr[0] == "addUser"){
                if ( a == 0 ){    // print only one time for all consecutively addUser commands 
                    fout << "\n===addUser method() test===" << endl;
                    a++;
                    b = 0,c = 0,d = 0,e = 0,f = 0,g = 0,h = 0,k = 0;
                }
                int userId = stoi(wordArr[1]);
                addUser(userId,wordArr[2]);
            }else if(wordArr[0] == "addMovie") {
                if ( b == 0 ){
                    fout << "\n===addMovie method() test===" << endl;
                    b++;
                    a = 0,c = 0,d = 0,e = 0,f = 0,g = 0,h = 0,k = 0;
                }
                int id = stoi(wordArr[1]);
                int year = stoi(wordArr[3]);
                addMovie(id,wordArr[2],year);
            }else if (wordArr[0] == "deleteMovie"){
                if ( c == 0 ){
                    fout << "\n===deleteMovie method() test===" << endl;
                    c++;
                    a = 0,b = 0,d = 0,e = 0,f = 0,g = 0,h = 0,k = 0;
                }
                int id = stoi(wordArr[1]);
                deleteMovie(id);
            }else if (wordArr[0] == "deleteUser"){
                if ( d == 0 ){
                    fout << "\n===deleteUser method() test===" << endl;
                    d++;
                    a = 0,b = 0,c = 0,e = 0,f = 0,g = 0,h = 0,k = 0;
                }
                int id = stoi(wordArr[1]);
                deleteUser(id);
            }else if (wordArr[0] == "showMovie"){
                if ( e == 0 ){
                    fout << "\n===showMovie method() test===" << endl;
                    e++;
                    a = 0,b = 0,c = 0,d = 0,f = 0,g = 0,h = 0,k = 0;
                }
                int id = stoi(wordArr[1]);
                showMovie(id); 
            }else if (wordArr[0] == "returnMovie"){
                if ( f == 0 ){
                    fout << "\n===returnMovie method() test===" << endl;
                    f++;
                    a = 0,b = 0,c = 0,d = 0,e = 0,g = 0,h = 0,k = 0;
                }
                int id = stoi(wordArr[1]);
                returnMovie(id);
            }else if (wordArr[0] == "showUser"){
                if ( g == 0 ){
                    fout << "\n===showUser method() test===" << endl;
                    g++;
                    a = 0,b = 0,c = 0,d = 0,e = 0,f = 0,h = 0,k = 0;
                }
                int id = stoi(wordArr[1]);
                showUser(id);
            }else if (wordArr[0] == "checkoutMovie"){
                if ( h == 0 ){
                    fout << "\n===checkoutMovie method() test===" << endl;
                    h++;
                    a = 0,b = 0,c = 0,d = 0,e = 0,f = 0,g = 0,k = 0;
                }
                int mId = stoi(wordArr[1]);
                int uId = stoi(wordArr[2]);
                checkOutMovie(mId,uId);
            }else{ // show all movie
                if ( k == 0 ){
                    fout << "\n===showAllMovie method() test===\nMovie id - Movie name - Year - Status" << endl;
                    k++;
                    a = 0,b = 0,c = 0,d = 0,e = 0,f = 0,g = 0,h = 0;
                }
                showAllMovie();
            }
        }
        input.close();
        fout.close();
        clearLists(movieList,userList,checkedoutList);        
    }

    bool controlMovie(int id){
        if ( forMovie == 0){
            return true;   // linked list is empty
        }
        for( int i = 0; i < forMovie; i++){   // movieId already exists
            if ( movieList->movieId == id){
                return false;
            }
            movieList = movieList->next;
        }
        return true;
    }

    void addMovie(const int movieId,const string movieTitle,const int year){
        for ( int i = 0; i < forCheckedout; i++){    // check whether movie exists in the checkedout list
            if ( checkedoutList->movieId == movieId){
                fout << "Movie "<< movieId <<" already exists" << endl;
                return; // exit the function
            }
            checkedoutList = checkedoutList->next;
        }

        if ( controlMovie(movieId) ){
            Movie* temp = new Movie();  
            temp ->movieId = movieId;
            temp ->movieTitle = movieTitle;
            temp ->movieYear = year;
            
            if ( movieList == nullptr){   // if linked is empty
                movieList = temp;
                temp -> next = temp;
            }else{
                if (movieList->next != movieList){    // if linked list has at least two elements
                    temp ->next = movieList->next;
                    movieList ->next = temp;
                }else{     // if linked list only has one element
                    movieList->next = temp;
                    temp->next = movieList;
                }
            }
            forMovie++;
            if ( forMessage == 1){
                fout << "Movie " << movieId << " has been added" << endl;
            }
            forMessage = 1;
        }else{
            fout << "Movie "<< movieId <<" already exists" << endl;
        }
    }

    void deleteForMovieFromCheckList(int movieId){
        int size = forCheckedout;
        for ( int i = 0; i < size; i++){
            if ( checkedoutList->next->movieId == movieId){
                Checkedout* temp;
                temp = checkedoutList->next;
                checkedoutList->next = temp ->next;
                temp->next = nullptr;
                delete temp;
                forCheckedout--;
                if ( forCheckedout == 0){
                    checkedoutList = nullptr;
                }
                return;
            }
            checkedoutList = checkedoutList->next;
        }
    }

    void deleteMovie( const int movieId){
        for ( int a = 0; a < forCheckedout; a++){   // control checkedout list whether movie is exists
            if ( checkedoutList->movieId == movieId){
                fout << "Movie " << movieId << " has been checked out" << endl;
                deleteForMovieFromCheckList(movieId);
                fout << "Movie " << movieId << " has been deleted" << endl;
                return; // exit the function
            }
            checkedoutList = checkedoutList->next;
        }

        if ( !controlMovie(movieId) ){  // linked list contains this movie
            int count = 0;
            while ( count <= forMovie){
                if ( movieList->next->movieId == movieId){  // we want to delete this node
                    Movie* temp;
                    temp = movieList->next;
                    fout << "Movie " << movieId << " has not been checked out" << endl;
                    movieList->next = temp->next;  // prev node will connect to next node of deleted node
                    temp->next = nullptr;  // deleted node doesn't point anywhere
                    delete temp;  // remove from movieList
                    fout << "Movie " << movieId << " has been deleted" << endl;
                    forMovie--;   // decrease movieList count
                    if ( forMovie == 0){  // if there is no element in circular linked list it points nullptr
                        movieList = nullptr;
                    }
                    break;
                }
                movieList = movieList->next;
                count++;
            }
        }else{
            fout << "Movie "<< movieId << " does not exist" << endl;
        }
    }

    bool controlUser(int id){
        if ( forUser == 0){
            return true;   // linked list is empty
        }
        for( int i = 0; i < forUser; i++){   // movieId already exists
            if ( userList->userId == id){
                return false;
            }
            userList = userList->next;
        }
        return true;
    }

    void addUser(const int userId,const string userName){
        if ( controlUser(userId)){
            User* temp = new User();
            temp ->userId = userId;
            temp ->userName = userName;
            
            if ( userList == nullptr){   // if linked list is empty
                userList = temp;
                temp ->next = temp;
            }else{
                if (userList->next != userList){   // if linked list has at least two elements
                    temp ->next = userList->next;
                    userList ->next = temp;
                }else{       // if linked list only has one element
                    userList->next = temp;
                    temp->next = userList;
                }
            }
            fout << "User " << userId << " has been added" << endl;
            forUser++;
        }else{
            fout << "User "<< userId <<" already exists" << endl;
        }    
    }

    void deleteForUserFromCheckList(int userId){
        int size = forCheckedout;
        for ( int i = 0; i < size; i++){  // traverse checked out list and remove all element checked out by given userId
            if ( checkedoutList->next->userId == userId){
                Checkedout* temp;
                temp = checkedoutList->next;
                checkedoutList->next = temp ->next;
                temp->next = nullptr;
                delete temp;
                forCheckedout--;  // decrease checkedout list count
                if ( forCheckedout == 0){    // checkedout list have no element
                    checkedoutList = nullptr;
                }
            }
            checkedoutList = checkedoutList->next;
        }
    }

    void deleteUser(const int userId){
        if ( !controlUser(userId)){    // if Linked list contains this user do it inside if block
            int count = 0;
            while ( count <= forUser){
                if ( userList->next->userId == userId){   // we want to delete this node
                    User* temp;
                    temp = userList->next;

                    deleteForUserFromCheckList(userId);

                    userList->next = temp->next;  // prev node will connect to next node of deleted node
                    temp->next = nullptr;   // deleted node doesn't point anywhere
                    delete temp;  // remove from userList
                    forUser--;    // decrease count of userList
                    fout << "User " << userId << " has been deleted" << endl;
                    if ( forUser == 0){   // if there is no element in circular linked list it points nullptr
                        userList = nullptr;
                    }
                    break; 
                }
                userList = userList->next;
                count++;
            }
        }else{
            fout << "User "<< userId << " does not exist\n";
        }    
    }

    void checkOutMovie(const int movieId,const int userId){
        if ( !controlMovie(movieId)){    // check whether Movie exists for checkout
            if ( !controlUser(userId)){    // check whether user exists for checkout
                for ( int i = 0; i < forMovie; i++){      // traverse circular linkedlist
                    if ( movieList->next->movieId == movieId){   // movie found and it is avaliable for checkout
                        Checkedout* temp = new Checkedout();
                        temp ->userId = userId;
                        temp ->movieId = movieId;
                        temp ->movieTitle = movieList->next->movieTitle;
                        temp ->movieYear = movieList->next->movieYear;

                        Movie* tempTwo;
                        tempTwo = movieList->next;
                        movieList->next = tempTwo->next;  // prev node will connect to next node of deleted node
                        tempTwo->next = nullptr;  // deleted node doesn't point anywhere
                        delete tempTwo;  // remove from movieList
                        forMovie--;   // decrease movieList count
                        if ( forMovie == 0){  // if there is no element in circular linked list
                            movieList = nullptr;
                        }
                        // now we will add element to checkedout list deleted from movieList            
                        if ( checkedoutList == nullptr){   // if linked list is empty
                            checkedoutList = temp;
                            temp ->next = temp;
                        }else{
                            if (checkedoutList->next != checkedoutList){   // if linked list has at least two elements
                                temp ->next = checkedoutList->next;
                                checkedoutList ->next = temp;
                            }else{       // if linked list only has one element
                                checkedoutList->next = temp;
                                temp->next = checkedoutList;
                            }
                        }
                        forCheckedout++;   // one element append checked out list
                        fout << "Movie " << movieId << " has been checked out by User " << userId << endl;
                        return;
                    }
                    movieList = movieList->next;
                }
            }else{
                fout << "User " << userId << " does not exist for checkout\n";
            }
        }else{
            fout << "Movie " << movieId << " does not exist for checkout\n";
        }
    }

    void returnMovie(const int movieId){
        for ( int i = 0; i < forMovie; i++){  // traverse linked list and find movie
            if ( movieList->movieId == movieId){
                fout << "Movie " << movieId << " has not been checked out" << endl;
                return;  // finish all processes for this function
            }
            movieList = movieList->next;
        }

        for ( int j = 0; j < forCheckedout; j++){  // traverse linked list and find movie
            if ( checkedoutList->movieId == movieId){
                int id = checkedoutList->movieId,yr = checkedoutList->movieYear;
                string title = checkedoutList->movieTitle;
                
                deleteForMovieFromCheckList(movieId);
                forMessage = 0;  // don't print added message
                addMovie(id,title,yr);  // add element movielist deleted from checkedout list             
                fout << "Movie " << movieId << " has been returned" << endl;
                return;  // finish all processes for this function
            }
            checkedoutList = checkedoutList->next;
        }
        fout << "Movie " << movieId << " not exist in the library" << endl;
    }

    void showAllMovie(){
        for( int i = 0; i < forMovie; i++){  // traverse circular linked list and print all elements
            fout << movieList->movieId << " " << movieList->movieTitle << " " << movieList->movieYear;
            fout << " Not checked out" << endl;
            movieList = movieList->next;
        }
        for( int j = 0; j < forCheckedout; j++){  // traverse circular linked list and print all elements
            fout << checkedoutList->movieId << " " << checkedoutList->movieTitle << " " << checkedoutList->movieYear;
            fout << " Checked out by User " << checkedoutList->userId << endl;
            checkedoutList = checkedoutList->next;
        }
    }

    void showMovie(const int movieId){
        for ( int i = 0; i < forMovie; i++){   // traverse circular linked list
            if ( movieList->movieId == movieId){
                fout << movieId << " " << movieList->movieTitle << " " << movieList->movieYear << " Not checked out" << endl;
                return;  // finish all processes for this function
            }
            movieList = movieList->next;
        }

        for ( int j = 0; j < forCheckedout; j++){   // traverse circular linked list
            if ( checkedoutList->movieId == movieId){
                fout << movieId << " " << checkedoutList->movieTitle << " " << checkedoutList->movieYear << " Checked out by User " << checkedoutList->userId << endl;
                return;  // finish all processes for this function
            }
            checkedoutList = checkedoutList->next;
        }
        fout << "Movie with the id " << movieId << " does not exist" << endl;
    }

    void showUser(const int userId){
         for ( int i = 0; i < forUser; i++){    // traverse circular linked list
            if ( userList->userId == userId){
                fout << "User id: " << userId << " User name: " << userList->userName << endl << "User "<< userId << " checked out the following Movies:" << endl;
                bool flag = true;
                for ( int j = 0; j < forCheckedout; j++){   // traverse circular linked list and find checkout movie
                    if ( checkedoutList->userId == userId){
                        if ( flag ){   // print only one time for one user if s/he has been checked out any movies
                            fout << "Movie id - Movie name - Year" << endl;
                            flag = false;
                        }
                        fout << checkedoutList->movieId << " " << checkedoutList->movieTitle << " " << checkedoutList->movieYear << endl;
                    }
                    checkedoutList = checkedoutList->next;
                }
                return;  // finish all processes for this function
            }
            userList = userList->next;
        }
        fout << "User with the id " << userId << " does not exist"<< endl;
    }

    void clearLists(Movie* m,User *u,Checkedout* c){
        // clear movieList
        for ( int i = 0; i < forMovie; i++){
            if ( m->next == m){    // if linked list has a one element
                m->next = nullptr;
                delete m;
            }else{         // if linked list has more than one element
                Movie* temp;
                temp = m->next;
                m->next = temp->next;
                temp->next = nullptr;
                delete temp;
            }               
        }
        // clear userList
        for ( int j = 0; j < forUser; j++){
            if ( u->next == u){    // if linked list has a one element
                u->next = nullptr;
                delete u;
            }else{         // if linked list has more than one element
                User* temp;
                temp = u->next;
                u->next = temp->next;
                temp->next = nullptr;
                delete temp;
            }               
        }
        for ( int k = 0; k < forCheckedout; k++){
            if ( c->next == c){    // if linked list has a one element
                c->next = nullptr;
                delete c;
            }else{         // if linked list has more than one element
                Checkedout* temp;
                temp = c->next;
                c->next = temp->next;
                temp->next = nullptr;
                delete temp;
            }               
        }        
    }
};