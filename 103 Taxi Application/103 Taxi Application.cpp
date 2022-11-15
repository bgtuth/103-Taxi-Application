#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


struct userInformation
{
    //Structure variables
    string FirstName;
    string LastName;
    string UserName;
    string Password;
    int IsAdmin;

    //Constructor
    userInformation(string FirstName, string LastName, string UserName, string Password, int IsAdmin) {
        this->FirstName = FirstName; //References original var names so you don't need two sets of names
        this->LastName = LastName;
        this->UserName = UserName;
        this->Password = Password;
        this->IsAdmin = IsAdmin;
    }
};



bool IsAdminUser = false;

//Prototype functions

//Load & write
void LoadCSV(string, vector<userInformation>&);
void WriteCSV(string, vector<userInformation>&);

//Misc
void Line(int, char, bool); //length, character, dropline after called t/f

//Menus
//Main menu
void DisplayMainMenu();
void DisplayUserMenu();



//----------------------------------------------------------------------------------------------------------------------------
//Main

int main()
{

    // Load in existing user data from users.csv at start of program
loadalldata:
    vector<userInformation> users;
    LoadCSV("users.csv", users); //"users.csv" is the file location so just adjust this as required. 

    // Display login screen
login:

    cout << "Taxi Management System " << endl;
    Line(60, '=', true);
    cout << endl;
    cout << "Please login to continue." << endl;

    // init variables for input
    string username;
    string password;

    for (int i = 0; i < 3; i++)
    {
        cout << "Username : ";
        cin >> username;

        cout << "Password : ";
        cin >> password;

        // check username and password against login database.
        for (int j = 0; j < users.size(); j++)
        {
            // if the username and password match what is in the file, let the user login.
            // scan each row until a match is found, if this be the case.
            if (users[j].UserName == username && users[j].Password == password)
            {
                if (users[j].IsAdmin == 1)
                {
                    IsAdminUser = true;
                }
                goto mainmenu;
            }
            else
            {
                continue;
            }
        }

        if (i == 2)
        {
            // maximum three attempts.
            // inform locked out.
            cout << "You have made three incorrect login attempts.";
            goto loginfail;
        }
        else
        {
            cout << "Incorrect username and/or password. Try again. " << i << endl;
        }
    }
    // Failed login message
loginfail:
    cout << "You failed to login." << endl;
    exit;

    // Display main menu
mainmenu:
    system("CLS"); //Clear console
    DisplayMainMenu();

    // user input
    int mainMenuSelection;
    cin >> mainMenuSelection;

    switch (mainMenuSelection)
    {
    case 4:

        // Display user management menu
    usermanagementmenu:
        system("CLS"); //Clear console
        DisplayUserMenu();

        // user input
        int userManagementMenu;
        cin >> userManagementMenu;

        //Sub menu selection
        switch (userManagementMenu) {
        case 1:
            //CreateNewUser();
            goto createnewuser;
            break;
        case 2:
            goto viewexistingusers;
            break;
        }

    }

viewexistingusers:

    // display all users
    Line(60, '-', true);
    for (int b = 0; b < users.size(); b++)
    {
        cout << "(" << b << ") " << users[b].FirstName << " " << users[b].LastName << "|" << users[b].UserName << "|" << "Admin: ";
        if (users[b].IsAdmin == 1)
        {
            cout << "True";
        }
        else
        {
            cout << "False";
        }
    }
    Line(60, '-', true);
    cout << endl;
    cout << "Select one of the following options:" << endl;
    cout << "1) Return to previous menu" << endl;
    cout << "2) Return to main menu" << endl;
    cout << "3) Remove a user";

    int vieworremoveexistingusersSelection;
    cin >> vieworremoveexistingusersSelection;

    switch (vieworremoveexistingusersSelection)
    {
    case 1:
        goto usermanagementmenu;
    case 2:
        goto mainmenu;
    case 3:
        goto removeauser;
    }

removeauser:

    int userToRemove;

    cout << "Remove a user";
    cout << "-------------";
    cout << endl;
    cout << endl;
    // display all users
    cout << "--------------------------------------" << endl;
    for (int b = 0; b < users.size(); b++)
    {
        cout << "(" << b << ") " << users[b].FirstName << " " << users[b].LastName << "|" << users[b].UserName << "|" << "Admin: ";
        if (users[b].IsAdmin == 1)
        {
            cout << "True" << endl;
        }
        else
        {
            cout << "False" << endl;
        }
    }
    cout << "--------------------------------------" << endl;
    cout << endl;
    cout << endl;

    cout << "Enter the number assocated with the user: ";
    cin >> userToRemove;

    // Remove the user. It's as simple as this one line.
    users.erase(users.begin() + userToRemove);
    // Update the CSV file
    WriteCSV("users.csv", users);

createnewuser:

    string newuserFirstName;
    string newuserLastName;
    string newuserUserName;
    string newuserPassword;
    int newuserAdminRights;

    // show screen to create a new user.
    cout << endl;
    cout << "Add new user account" << endl;
    cout << endl;
    cout << endl;
    cout << "Enter person's first name: ";
    cin >> newuserFirstName;
    cout << "Enter person's last name: ";
    cin >> newuserLastName;
    cout << "Enter a unique username: ";
    cin >> newuserUserName;
    cout << "Enter your account password: ";
    cin >> newuserPassword;
    cout << "Give Admin rights? ('0' for no. '1' for yes): ";
    cin >> newuserAdminRights;
    cout << endl;

    // Create the record.
    vector<userInformation> newuser;
    newuser.push_back(userInformation(newuserFirstName, newuserLastName, newuserUserName, newuserPassword, newuserAdminRights));

    // Return data to test if the user data has been recorded ok.
    cout << newuser[0].FirstName << "," << newuser[0].LastName << "," << newuser[0].UserName << "," << newuser[0].Password << "," << newuser[0].IsAdmin << endl;

    // Save to file system.
    ofstream appfile;
    appfile.open("users.csv", ios::app);
    appfile << newuser[0].FirstName << "," << newuser[0].LastName << "," << newuser[0].UserName << "," << newuser[0].Password << "," << newuser[0].IsAdmin << endl;
    appfile.close();

    cout << endl;
    cout << "New user account created!";
    cout << endl;
    cout << "Name: " << newuserFirstName << " " << newuserLastName << endl;
    cout << "Username: " << newuserUserName << "   Password: " << newuserPassword << endl;
    cout << endl;
    cout << endl;
    cout << "-------------------------" << endl;
    cout << "Select one of the following options:" << endl;
    cout << "1) Return to previous menu" << endl;
    cout << "2) Return to main menu" << endl;

    int newuserAccountMenuOptions;
    cin >> newuserAccountMenuOptions;

    switch (newuserAccountMenuOptions)
    {
    case 1:
        goto usermanagementmenu;
    case 2:
        goto mainmenu;
    }




}


//----------------------------------------------------------------------------------------------------------------------------
// Menu Functions

void DisplayMainMenu() {

    cout << "Main menu" << endl;
    Line(60, '=', true);
    cout << endl;
    cout << "Please select one of the following options\n\n";
    cout << "1) Book a Taxi" << endl;
    cout << "2) Lodge Complaint" << endl;
    cout << "3) Report and view lost items" << endl;
    if (IsAdminUser)
    {
        cout << "4) Add, view or remove users - Admin only" << endl;
    }

    cout << endl;
    cout << "Enter selection : ";
}

void DisplayUserMenu() {
    cout << endl;
    cout << "Add, view and remove existing users\n";
    Line(60, '=', true);
    cout << endl;
    cout << "1) Add new user" << endl;
    cout << "2) View or remove existing users and account privledges" << endl;
    cout << endl;
    cout << "Enter selection : ";
}



//----------------------------------------------------------------------------------------------------------------------------
//Functions


//Load CSV function
void LoadCSV(string filename, vector<userInformation>& users) { //Use reference so it doesn't make a copy of the vector and edits the original

    ifstream inputFile;
    inputFile.open(filename);
    string line = "";
    while (getline(inputFile, line))
    {
        //Init vars to load data into
        string FirstName;
        string LastName;
        string UserName;
        string Password;
        int IsAdmin;

        //Takes string and separates data using comma delimiter
        string tempString;
        stringstream inputString(line);
        getline(inputString, FirstName, ',');
        getline(inputString, LastName, ',');
        getline(inputString, UserName, ',');
        getline(inputString, Password, ',');
        // getting IsAdmin convert string to integer val
        getline(inputString, tempString, ',');
        IsAdmin = stoi(tempString.c_str());

        //Load data into vector using structure constructor
        userInformation user(FirstName, LastName, UserName, Password, IsAdmin);
        users.push_back(user);
        line = "";
    }
}

//Write CSV function
void WriteCSV(string filename, vector<userInformation>& users)
{
    int i = 0; //Starts at vector index of first driver
    ofstream appfile;
    appfile.open(filename, ios::out);

    for (auto itr = users.begin(); itr != users.end(); itr++) {

        appfile << users[i].FirstName << "," << users[i].LastName << "," << users[i].UserName << "," << users[i].Password << "," << users[i].IsAdmin << endl;
        i++;
    }

    appfile.close();
}

//Draw line
void Line(int nChar, char c, bool dropline) {
    for (int i = 1; i <= nChar; i++) {
        cout << c;
    }
    if (dropline == true) {
        cout << endl;
    }

}