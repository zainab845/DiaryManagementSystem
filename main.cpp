#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class user {
private:
	string username;
	string password;
public:
	user() {
		username = "";
		password = "";
	}
	user(string user, string pass) {
		username = user;
		password = pass;
	}
	void setUsername(string user){
		username = user;
	}
	void setPassword(string pass) {
		password = pass;
	}
	string getUsername() {
		return username;
	}
	string getPassword() {
		return password;
	}
	bool authentication(string user,string pass) {
		return (username == user && password == pass);
	}
	virtual void displayUser() {
		cout << "Username: " << username<<endl;
		cout << "Password: " << password<<endl;
	}
	void changePassword() {
		string currentPass, newPass;
		cout << "enter current password: " << endl;
		cin >> currentPass;

		while (password != currentPass) {
			cout << "enter current password: " << endl;
			cin >> currentPass;
		}

		cout << "enter new password: " << endl;
		cin >> newPass;
		password = newPass;
		cout << "password successfully changed" << endl;
	}
};
class entry {
private:
	string title, date, content;
	int id;
public:
	entry() {
		title = "";
		date = "";
		content = "";
		id = -1;
	}
	entry(string t, string d, string c, int iD) {
		title = t;
		date = d;
		content = c;
		id = iD;
	}

	void setID(int iD){
	    id = iD;
	}

	void setTitle(string t){
        title = t;
	}

	void setDate(string d){
        date = d;
	}

	void setContent(string c){
        content = c;
	}

	string getTitle() {
		return title;
	}
	string getDate() {
		return date;
	}
	string getContent() {
		return content;
	}
	int getID() {
		return id;
	}
	void editContent(string newContent) {
		content = newContent;
		cout << "\tentry content updated." << endl;
	}
	void displayEntry(){
	    cout << "\t\t|------------------------------------------------------\n";
		cout << "\t\t|\tID: " << id <<"\tTitle: " << title << "\tDate: " << date
		<< endl<<"\t\t|\t\tContent: " << content << endl;
		cout << "\t\t|------------------------------------------------------\n";
	}

	void displayEntryNoContent(){
	    cout << "\t\t|------------------------------------------------------\n";
	    cout << "\t\t|Entry: " << endl;
		cout << "\t\t|\tID: " << id
		<< endl<<"\t\t|\tTitle: " << title
		<< endl<<"\t\t|\tDate: " << date<< endl;
		cout << "\t\t|------------------------------------------------------\n";
	}
};
/*
* diaryUser inherit User
User object will be created only when diary object will be created
concept of composition, array of entries
*/
class diaryUser :public user{
private:
	entry* entries;
	int count, size, nextid;
public:

    // default constructor
    diaryUser() : user() {
        size = 5;
        entries = new entry[size];
        count = 0;
        nextid = 1;
    }

	diaryUser(string userN, string pass, int startSize = 5) : user(userN, pass) {
		size = startSize;
		entries = new entry[size];
		count = 0;
		nextid = 1;
	}

	~diaryUser() {
		delete[] entries;
	}

	// for the concepts of deep copy
	void resize() {
		size *= 2;
		entry* newEntries = new entry[size];
		for (int i = 0; i < count; i++) {
			newEntries[i] = entries[i]; // deep copying as entry class doesnt contain any pointer member
		}
		delete[] entries;
		entries = newEntries;
		//cout << "Performed resize operation. \n New size for storing entries is: " << size << endl;
		// no need to delete newEntries before leaving this function
		// as it becomes our main array

	}

	void setUser(string userN, string pass){
        setUsername(userN);
        setPassword(pass);
	}

	void addEntry() {
		if (count == size) {
			resize();
		}
		string date, title, content;
		cout << "Enter data for diary entry: " << endl;
		cin.ignore();

		cout << "enter date: ";
		getline(cin, date);
		cout << "enter title: ";
		getline(cin, title);
		cout << "enter content: ";
		getline(cin, content);

        entries[count].setID(nextid);
        entries[count].setContent(content);
        entries[count].setDate(date);
        entries[count].setTitle(title);
        count++;
        nextid++;
		//entries[count++] = entry(title, date, content, nextid++);
	}

	void addEntryFromFile(int id, string date, string title, string content){
	    if (count == size) {
			resize();
		}
	    entries[count].setID(id);
        entries[count].setContent(content);
        entries[count].setDate(date);
        entries[count].setTitle(title);
        count++;
	}

	int getCount(){
        return count;
	}
    string getTitle(int j) const {
		return entries[j].getTitle();
	}
	string getDate(int j) const {
		return entries[j].getDate();
	}
	string getContent(int j) const {
		return entries[j].getContent();
	}
	int getID(int j) const {
		return entries[j].getID();
	}

	void searchByTitle(string title){
	    // loop through entries
	    for (int i=0; i< count; i++){
            if (entries[i].getTitle() == title)
            {
                cout << "\n\t\t------------------Entry Found ---------------------\n";
                // display content of found entry
                entries[i].displayEntry();
                return;
            }
	    }
	    cout << "\n\tEntry not Found with title: " << title << " .Try again!"<<endl;

	}

	void searchByDate(string date){
        // loop through entries
	    for (int i=0; i< count; i++){
            if (entries[i].getDate() == date)
            {
                cout << "\n\t\t\------------------Entry Found ---------------------\n";
                // display content of found entry
                entries[i].displayEntry();
                return;
            }
	    }
	    cout << "\n\tEntry not Found with date: " << date << " .Try again!"<<endl;

	}

	void deleteEntry(int id){
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (entries[i].getID() == id) {
                // Shift all elements after index i one step left
                for (int j = i; j < count - 1; j++) {
                    entries[j] = entries[j + 1];
                }
                count--;  // reduce total count
                found = true;
                cout << "\tEntry with ID " << id << " deleted successfully.\n";
                /*
                for(int i=0; i<count; i++){
                    entries[i].displayEntryNoContent();
                }
                */
                break;
            }
        }

        if (!found) {
            cout << "\tEntry with ID " << id << " not found.\n";
        }

	}

	void editEntry(int id){
	    for (int i = 0; i < count; i++) {
            if (entries[i].getID() == id) {
                string newContent;
                cout << "\tEnter new content:> ";
                cin.ignore();
                getline(cin, newContent);
                entries[i].editContent(newContent);
                return;
            }
	    }
	    cout << "\nEntry with ID " << id << " not found.\n";
	}

	void displayEntries(string uName){
	    // displaying username
	    cout << "\t\t|---------------------Diary of "<< uName << "--------------------\n";
	    for(int i=0; i<count; i++){
            entries[i].displayEntryNoContent();
	    }
	}

    // concept of exception handling index out of bound
	void displayEntryContent(int id){
	    for(int i=0; i<count; i++){
            if (entries[i].getID() == id){
                entries[i].displayEntry();
                return;
            }

	    }
	    cout << " This entry id doesn't exist. Try again!"<<endl;
	}

	// concept of exception handling index out of bound
	bool isIDValid(int id){
	    try{
	        // count is the total number of entries
	        if (id > -1 && id < count)
                return true;
            else
                throw "Error!";
	    }
	    catch(const char* a){
	        cout << endl <<"\t" <<a << " This entry id doesn't exist. Try again!"<<endl;
	        return false;
	    }

	}

	// set nextID
	void setNextID(int id){
        nextid = ++id;
	}

};

class diaryArray{
private:
    // creating array of userDiaries
    diaryUser* diaries;
    int di; // diary count
    int dSize;

public:
    diaryArray(const int dSize){
        // creating array of userDiaries
        diaries = new diaryUser[dSize];
        di = 0;
        this->dSize = dSize;
    }

    ~diaryArray() {
		delete[] diaries;
	}

	void saveFile(const string& filename) {
		ofstream outfile(filename);
		if (!outfile) {
			cout << "error opening file" << endl;
			return;
		}
		// save diary array into file
        for (int i=0; i < di; i++)
        {
            outfile << "User: " << diaries[i].getUsername() << "," << diaries[i].getPassword() << endl;
            int count = diaries[i].getCount();
            //cout << "Count of diary of " << diaries[i].getUsername() << ": " << count << endl;
            for (int j = 0; j < count; j++) {
                //cout << diaries[i].getTitle(j);
                outfile << diaries[i].getID(j) << "," << diaries[i].getDate(j) << "," <<
                diaries[i].getTitle(j) << "," << diaries[i].getContent(j) << endl;
            }
        }
		outfile.close();
		cout << "Diaries saved successfully"<<endl;
    }

    /*
    loadFile function is reading following file format saving into corresponding objects:
    User: zainab,1234
    0, 23, recipe, pancake
    1, 24, todos, study
    User: zainab,1234
    0, 25, lunch, dineout
    1, 26, game, bedminton
    */
    void loadFile(const string& filename) {

        ifstream inFile(filename);
        if (!inFile) {
            cout << "File could not be opened.\n";
            return;
        }
        di = -1; //  setting diary index to -1 to increase it only when User: string found from file
        string line;
        int id;
        //diaryUser currentUser;
        //bool userBlockStarted = false;

        while (getline(inFile, line)) {
            if (line.substr(0, 5) == "User:") {

                string uname, pass;
                size_t pos = line.find(':');
                if (pos != string::npos) {
                    string data = line.substr(pos + 1); // " zainab,1234"
                    stringstream ss(data);
                    getline(ss, uname, ',');
                    getline(ss, pass);

                    // Trim spaces
                    uname.erase(0, uname.find_first_not_of(" "));
                    pass.erase(0, pass.find_first_not_of(" "));

                    //cout << "user: " << uname << ", " << pass << endl;
                    diaries[++di].setUser(uname, pass);

                }
            } else if (!line.empty()){
                // Read entry line: 0, 23, recipe, pancake
                stringstream ss(line);
                string idStr, date, title, content;

                getline(ss, idStr, ',');
                getline(ss, date, ',');
                getline(ss, title, ',');
                getline(ss, content);

                // Trim whitespace
                date.erase(0, date.find_first_not_of(" "));
                title.erase(0, title.find_first_not_of(" "));
                content.erase(0, content.find_first_not_of(" "));

                id = stoi(idStr);
                //cout << id << date << title << content << endl;
                diaries[di].addEntryFromFile(id, date, title, content);
            }
            diaries[di].setNextID(id);// set the pointer for nextid after loading file contents
        }
        cout << ++di << " Existing Diary(s) Loaded Successfully." << endl;
        cout << "******************************************" << endl;
        inFile.close();
        //return di;
    }

    void displayDiaries(){
        cout << "-------------Displaying Existing Diaries-------------" << endl;
        for (int i=0; i < di; i++)
            {
                int count = diaries[i].getCount();
                cout << i+1 << ": Diary of User: " << diaries[i].getUsername() << " ,contains (" <<  count << ") entries." << endl;
            }
        cout << "------------------------------------------------------" << endl;
    }

    void createDiary(){
            string uName, pass;
            //diaryUser d1("zainab", "1234", 5);
            cout << "----------------Creating Diary----------------" << endl;
            cout << "Enter username: ";
            cin>> uName;
            cout << "Enter password: ";
            cin >> pass;
            diaries[di].setUser(uName, pass);
            diaries[di].addEntry();
            char subOption = displaySubMenu1();
            while (subOption == 'Y' || subOption == 'y'){
                diaries[di].addEntry();
                subOption = displaySubMenu1();
            }
            cout << "---------------------------------------------" << endl;
            di++;
            //diaries[di++] = d1;
    }

    char displaySubMenu1(){
        char option;
        bool invalid = true;
        while (invalid){
            cout << "Do you want to add another entry (y) or not (N) ? > ";
            cin >> option;
            if (option == 'Y' || option == 'y' || option == 'N'|| option == 'n'){
                invalid = false;
            }
        }
        return option;
    }

    // return diary if login successful
    diaryUser* login(string uName, string pass){
        //diaryUser* du;
        //cout << "Login " << endl;
        for (int i=0; i<di; i++){
            if (diaries[i].authentication(uName, pass)){
                cout << "Login successful." << endl;
                //du = diaries[i];
                diaries[i].displayEntries(uName);
                return &diaries[i];
            }
        }
        cout << "Login failed. Try again!" << endl;
        return nullptr;
    }

    int displaySubMenu2(){
        int option;
        bool invalid = true;
        while (invalid){
            cout << "\n\tEntry menu: \n\t\tUpdate Content <1>,"
            <<" \n\t\tDelete Entry <2>,"
            <<" \n\t\tView Entry <3>,"
            <<" \n\t\tSearch Entry by Title <4>,"
            <<" \n\t\tSearch Entry by Date <5>,"
            <<" \n\t\tAdd a new Entry <6>,"
            <<" \n\t\tView All Entries <7>,"
            <<" \n\t\tExit Entry Menu <8>: \n\tChoose an entry option?> ";
            cin >> option;
            //cout << endl;
            if (cin.fail()) {
                cin.clear();                // Clear error flag
                cin.ignore(1000, '\n');     // Discard invalid input
                cout << "Invalid input! Try again.\n";
                continue;
            }
            if (option == 1 || option == 2 || option == 3|| option == 4 ||
                option == 5 || option == 6 || option == 7 || option == 8){
                invalid = false;
            }
        }
        //cout << option << endl;
        return option;
    }

    // diary operations after successful login
    void diaryOperations(){
            int subOption;
            diaryUser* du;
            // login
            string username, pass;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> pass;
            du = login(username, pass);
            // run the submenu loop only after successful login
            if (du != nullptr){
                //du.displayEntries();
                subOption = 0;
                while (subOption != 8){
                    subOption = displaySubMenu2();
                    if (subOption == 1){
                        // Edit Entry
                        int id;
                        cout << "\tEnter id of entry to edit: ";
                        cin >> id;
                        //if (du->isIDValid(id))
                            du->editEntry(id);
                    }
                    else if (subOption == 2){
                        // Delete Entry
                        int id;
                        cout << "\tEnter id of entry to delete: ";
                        cin >> id;
                        //if(du->isIDValid(id)){
                            du->deleteEntry(id);
                        //}
                    }
                    else if (subOption == 3){
                        // View Entry
                        int id;
                        cout << "\tEnter id of entry to view: ";
                        cin >> id;
                        du->displayEntryContent(id);
                    }
                    else if (subOption == 4){
                        // search Entry by title
                        string title;
                        cout << "\tEnter title of entry to search: ";
                        cin.ignore();
                        getline(cin, title);
                        du->searchByTitle(title);
                    }
                    else if (subOption == 5){
                        // search Entry by date
                        string date;
                        cout << "\tEnter date of entry to search: ";
                        cin.ignore();
                        getline(cin, date);
                        du->searchByDate(date);
                    }
                    else if (subOption == 6){
                        // Add new entry
                        du->addEntry();
                        char subOption1 = displaySubMenu1();
                        while (subOption1 == 'Y' || subOption1 == 'y'){
                            du->addEntry();
                            subOption1 = displaySubMenu1();
                        }
                        //cout<<"Outside if " << subOption << endl;
                        //du.displayEntryContent(id);
                    }
                    else if (subOption == 7){
                        // View all entries
                        du->displayEntries(username);

                    }
                }// end of while
            }
    //delete[] du;
    //du = nullptr;
    //cout<<"Outside loop " << subOption << endl;
    }


};

//////////////////////////////////////////////////////////////////////////
/////////////////// End of classes ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////





/*
void displayDiaries(diaryUser* diaries, int dCount){
    for (int i=0; i < dCount; i++)
        {
            cout << "User: " << diaries[i].getUsername() << "," << diaries[i].getPassword() << endl;
            int count = diaries[i].getCount();
            //cout << "Count of diary of " << diaries[i].getUsername() << ": " << count << endl;
            for (int j = 0; j < count; j++) {
                //cout << diaries[i].getTitle(j);
                cout << diaries[i].getID(j) << ", " << diaries[i].getDate(j) << ", " <<
                diaries[i].getTitle(j) << ", " << diaries[i].getContent(j) << endl;
            }
        }
}
*/


int displayMainMenu(){
    int option;
    bool invalid = true;
    while (invalid){
        cout << "\nMain menu: \n\tLogin (1), \n\tCreate new diary (2), \n\tDisplay all diaries (3), "
        << "\n\tExit (4): \nChoose an option?> ";
        cin >> option;
        if (option == 1 || option == 2 || option == 3|| option == 4){
            invalid = false;
        }
    }
    return option;
}

//////////////////////////////////////////////////////////////
int main() {
    string filename = "diaries.txt";
    // diary array size
    const int dSize = 10;
    // creating array of userDiaries
    //diaryUser *diaries = new diaryUser[dSize];
    diaryArray d(dSize);
    //int di = 0; // diary index
    bool more = true;
    int option;

    cout << "******************************************" << endl;
    cout << "******************************************" << endl;
    cout << "Welcome to Diary Management System" << endl;
    cout << "******************************************" << endl;
    cout << "******************************************" << endl;
    // load the file and create corresponding objects
    d.loadFile(filename);
    // displayDiaries(diaries, di);
    //exit(0);


	while (more)
    {
        option = displayMainMenu();
        //cout << option  << endl;
        if (option == 1){
             // add, edit, delete, update, search entries

            d.diaryOperations();

            //cout << "outside " << endl;
        }
        // creating new diary
        else if (option == 2){
            d.createDiary();
        }
        else if (option == 3){
                //cout << "displaying" << endl;
            d.displayDiaries();
        }
        else if (option == 4){
            more = false;
            cout << "Exiting ...." << endl;
        }
    }

    d.saveFile(filename);

    return 0;
}
