#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> //formatting
#include <ctime>; //date & random number
#pragma warning(disable:4996) //disable system warning for ctime library

using namespace std;

//----------------------------------------------------------------------------------------------------------------------------
//Structs 
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

struct bookingInformation {

    //Name
    string CustFirstName;
    string CustLastName;
    //Date
    int BDateDay;
    int BDateMonth;
    int BDateYear;
    //Pickup Address
    string PickupAddressStreet;
    string PickupAddressSuburb;
    string PickupAddressTownCity;
    int PickupAddressPcode;
    //Dropoff Address
    string DropAddressStreet;
    string DropAddressSuburb;
    string DropAddressTownCity;
    int DropAddressPcode;
    //Distance + Cost
    int DistanceBAddresses;
    double TripCost;

    //Constructor
    bookingInformation
    (
        //Name
        string CustFirstName,
        string CustLastName,
        //Date
        int BDateDay,
        int BDateMonth,
        int BDateYear,
        //Pickup Address
        string PickupAddressStreet,
        string PickupAddressSuburb,
        string PickupAddressTownCity,
        int PickupAddressPcode,
        //Dropoff Address
        string DropAddressStreet,
        string DropAddressSuburb,
        string DropAddressTownCity,
        int DropAddressPcode,
        //Distance + Cost
        int DistanceBAddresses,
        double TripCost
    )
    {
        this->CustFirstName = CustFirstName;
        this->CustLastName = CustLastName;

        this->BDateDay = BDateDay;
        this->BDateMonth = BDateMonth;
        this->BDateYear = BDateMonth;

        this->PickupAddressStreet = PickupAddressStreet;
        this->PickupAddressSuburb = PickupAddressSuburb;
        this->PickupAddressTownCity = PickupAddressTownCity;
        this->PickupAddressPcode = PickupAddressPcode;

        this->DropAddressStreet = DropAddressStreet;
        this->DropAddressSuburb = DropAddressSuburb;
        this->DropAddressTownCity = DropAddressTownCity;
        this->DropAddressPcode = DropAddressPcode;

        this->DistanceBAddresses = DistanceBAddresses;
        this->TripCost = TripCost;
    }
};

//----------------------------------------------------------------------------------------------------------------------------
//Global variables

bool IsAdminUser = false;
double costPerKm = 1.90;

//----------------------------------------------------------------------------------------------------------------------------
//Prototype functions

//Load & write
void LoadUsersCSV(vector<userInformation>&, string);
void LoadBookingInfoCSV(vector<bookingInformation>&, string);

void WriteUserCSV(vector<userInformation>&, string);
void WriteBookTaxiCSV(vector<bookingInformation>&, string);

//Misc
void Line(int, char, bool); //length, character, dropline after called t/f

//Menus
void DisplayMainMenu();
void DisplayUserMenu();
void DisplayBookingMenu();

//User functions
void CreateNewUser();
void ViewExistingUser(vector<userInformation>&);
void RemoveUser(vector<userInformation>&);

//Book taxi functions
void BookRide(vector<bookingInformation>&);
void ViewPastBookings();


//----------------------------------------------------------------------------------------------------------------------------
//Main

int main()
{
    // Load in existing user data at program start into vector structures
    //------------------------------------------------------------------------------------

    vector<userInformation> users; //Create vector
    LoadUsersCSV(users, "users.csv"); // Load users 

    vector<bookingInformation> bookingInfo; //Create vector
    LoadBookingInfoCSV(bookingInfo, "bookinginfo.csv"); // Load users 


    //------------------------------------------------------------------------------------
    // Display login screen

    cout << "Taxi Management System " << endl;
    Line(60, '=', true);
    cout << endl;
    cout << "Please login to continue." << endl;

    // init variables for input
    string username;
    string password;

    //Check three attempts loop
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
    return 0;


    // Display main menu
mainmenu:
    system("CLS"); //Clear console
    DisplayMainMenu();

    // user input
    int mainMenuSelection;
    cin >> mainMenuSelection;

    switch (mainMenuSelection)
    {
    case 1:
        //Book Taxi, View past bookings
    booktaximenu:

        system("CLS"); //Clear console
        DisplayBookingMenu();

        // user input
        int taxiBookingMenu;
        cin >> taxiBookingMenu;

        switch (taxiBookingMenu) {
        case 1:
            system("CLS");
            BookRide(bookingInfo);
            break;
        case 2:
            ViewPastBookings();
            break;
        }


    case 4:
        // Add, remove and view existing users
    usermanagementmenu:

        system("CLS"); //Clear console
        DisplayUserMenu();

        // user input
        int userManagementMenu;
        cin >> userManagementMenu;

        //Sub menu selection
        switch (userManagementMenu) {
        case 1:

            //Create new user

            system("CLS");
            CreateNewUser();

            //Reload users vector contents to reflect any changes
            users.clear();
            LoadUsersCSV(users, "users.csv"); // Load users 

            cout << endl;
            Line(60, '-', true);
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
            break;

        case 2:
            //View existing users
            ViewExistingUser(users);

            //Reload users vector contents to reflect any changes
            users.clear();
            LoadUsersCSV(users, "users.csv"); // Load users 

            int vieworremoveexistingusersSelection;
            cin >> vieworremoveexistingusersSelection;

            switch (vieworremoveexistingusersSelection)
            {
            case 1:
                goto usermanagementmenu;
            case 2:
                goto mainmenu;
            case 3:
                system("CLS");
                RemoveUser(users);
                goto mainmenu;
            }
        }
    }

}


//----------------------------------------------------------------------------------------------------------------------------
// User functions

//Book taxi functions
void DisplayBookingMenu() {
    cout << endl;
    cout << "Book Taxi, View past bookings\n";
    Line(60, '=', true);
    cout << endl;
    cout << "1) Book new taxi ride" << endl;
    cout << "2) View past taxi bookings" << endl;
    cout << endl;
    cout << "Enter selection : ";
}

void BookRide(vector<bookingInformation>& bookingInfo) {

    //Init vars to load data into
    //Name
    string CustFirstName;
    string CustLastName;
    //Date
    int BDateDay;
    int BDateMonth;
    int BDateYear;
    //Pickup Address
    string PickupAddressStreet;
    string PickupAddressSuburb;
    string PickupAddressTownCity;
    int PickupAddressPcode;
    //Dropoff Address
    string DropAddressStreet;
    string DropAddressSuburb;
    string DropAddressTownCity;
    int DropAddressPcode;
    //Distance + Cost
    int DistanceBAddresses;
    double TripCost;


    //Display booking screen - enter new customer
    cout << endl;
    cout << "Book taxi for customer" << endl;
    Line(60, '=', true);
    cout << endl;

    cout << "Enter new customer\n";
    Line(60, '-', true);
    cout << "Name\n";
    cout << "Enter person's first name: ";
    cin >> CustFirstName;
    cout << "Enter person's last name: ";
    cin >> CustLastName;
    cout << endl;
    cout << "Customer added to database!\n";
    Line(60, '-', true);


    //Date using ctime library
    time_t curr_time;
    curr_time = time(NULL);

    char date[20];
    char day[20];
    char month[20];
    char year[20];

    //Using strftime to format output
    time_t t = time(0);
    strftime(date, 20, "%d/%m/%Y", localtime(&t)); 
    strftime(day, 20, "%d", localtime(&t));
    strftime(month, 20, "%m", localtime(&t));
    strftime(year, 20, "%Y", localtime(&t));

    //Char array to string
    string tempD = day;
    string tempM = month;
    string tempY = year;

    int selectDateMenu;

    //Date submenu
    cout << "Select one of the following options:" << endl;
    cout << "1) Book today, " << date << endl;
    cout << "2) Select another date" << endl;
    cin >> selectDateMenu;
    cout << endl;

    switch (selectDateMenu) {
    case 1:
        //String to integer - update var
        BDateDay = stoi(tempD.c_str());
        BDateMonth = stoi(tempM.c_str());
        BDateYear = stoi(tempY.c_str());
        cout << "Today's date added!\n";
    case 2:
        cout << "Enter day (dd): " << endl;
        cin >> BDateDay;
        cout << "Enter month (mm): " << endl;
        cin >> BDateMonth;
        cout << "Enter year (yy): " << endl;
        cin >> BDateYear;
        cout << "Selected date added!\n";
    }

    //Add pickup & dropoff address
    cout << endl;
    cout << "Add addresses\n";
    Line(60, '-', true);
    cout << endl;

    //Pickup Address
    cout << "Pickup address\n";
    cout << "Enter address number/street) : ";
    cin >> PickupAddressStreet;
    cout << "Enter suburb : ";
    cin >> PickupAddressSuburb;
    cout << "Enter town/city : ";
    cin >> PickupAddressTownCity;
    cout << "Enter Postcode: ";
    cin >> PickupAddressPcode;

    //Dropoff Address
    cout << "Dropoff address\n";
    cout << "Enter address number/street) : ";
    cin >> DropAddressStreet;
    cout << "Enter suburb : ";
    cin >> DropAddressSuburb;
    cout << "Enter town/city : ";
    cin >> DropAddressTownCity;
    cout << "Enter Postcode: ";
    cin >> DropAddressPcode;
    cout << endl;

    cout << "Addresses added!\n";

    cout << endl;
    cout << "Calculate Taxi Fare\n";
    Line(60, '-', true);
    cout << endl;

    //Generate random distance between 1 - 20kms

    srand(time(NULL)); //Reset number seed
    //Set up the boundary
    int min = 1;
    int max = 20 + 1; //Add +1 to include 20 in range
    DistanceBAddresses = rand() % (min - max) + min;

    cout << "Distance between addresses ";
   



    ////Push information to vector
    //vector<bookingInformation> addTodaysDate;
    //addTodaysDate.push_back(bookingInformation());

}

void ViewPastBookings() {

}

//----------------------------------------------------------------------------------------------------------------------------
// User functions

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

void CreateNewUser() {

    string newuserFirstName;
    string newuserLastName;
    string newuserUserName;
    string newuserPassword;
    int newuserAdminRights;

    // show screen to create a new user.
    cout << endl;
    cout << "Add new user account" << endl;
    Line(60, '=', true);
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
}

void ViewExistingUser(vector<userInformation>& users) {
    // Display all users
    cout << "Current user database contents\n";
    Line(60, '-', true);
    for (int i = 0; i < users.size(); i++)
    {
        cout << "(" << i << ") " << users[i].FirstName << " " << users[i].LastName << "|" << users[i].UserName << "|" << "Admin: ";
        if (users[i].IsAdmin == 1)
        {
            cout << "True";
        }
        else
        {
            cout << "False";
        }

        cout << endl;
    }
    Line(60, '-', true);
    cout << endl;
    cout << "Select one of the following options:" << endl;
    cout << "1) Return to previous menu" << endl;
    cout << "2) Return to main menu" << endl;
    cout << "3) Remove a user" << endl;

}

void RemoveUser(vector<userInformation>& users) {

    int userToRemove;

    cout << "Remove a user\n";
    Line(60, '-', true);
    cout << endl;
    // display all users
    Line(60, '-', true);
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
    WriteUserCSV( users, "users.csv");
}

//----------------------------------------------------------------------------------------------------------------------------
// Main menu functions

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

//Draw line
void Line(int nChar, char c, bool dropline) {
    for (int i = 1; i <= nChar; i++) {
        cout << c;
    }
    if (dropline == true) {
        cout << endl;
    }

}

//----------------------------------------------------------------------------------------------------------------------------
//Functions

//Load CSV functions
//Use reference so it doesn't make a copy of the vector and edits the original

void LoadUsersCSV(vector<userInformation>& users,string filename) {

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

void LoadBookingInfoCSV(vector<bookingInformation>& bookingInfo, string filename) {

    ifstream inputFile;
    inputFile.open(filename);
    string line = "";

        while (getline(inputFile, line))
        {

            //Init vars to load data into
            //Name
            string CustFirstName;
            string CustLastName;
            //Date
            int BDateDay;
            int BDateMonth;
            int BDateYear;
            //Pickup Address
            string PickupAddressStreet;
            string PickupAddressSuburb;
            string PickupAddressTownCity;
            int PickupAddressPcode;
            //Dropoff Address
            string DropAddressStreet;
            string DropAddressSuburb;
            string DropAddressTownCity;
            int DropAddressPcode;
            //Distance + Cost
            int DistanceBAddresses;
            double TripCost;

            //Takes string and separates data using comma delimiter
            string tempString;
            stringstream inputString(line);
            //Name
            getline(inputString, CustFirstName, ',');
            getline(inputString, CustLastName, ',');
            //Date
            getline(inputString, tempString, ',');
            BDateDay = stoi(tempString.c_str());
            getline(inputString, tempString, ',');
            BDateMonth = stoi(tempString.c_str());
            getline(inputString, tempString, ',');
            BDateYear = stoi(tempString.c_str());
            //Pickup Address
            getline(inputString, PickupAddressStreet, ',');
            getline(inputString, PickupAddressSuburb, ',');
            getline(inputString, PickupAddressTownCity, ',');
            getline(inputString, tempString, ',');
            PickupAddressPcode = stoi(tempString.c_str());
            //Dropoff Address
            getline(inputString, DropAddressStreet, ',');
            getline(inputString, DropAddressSuburb, ',');
            getline(inputString, DropAddressTownCity, ',');
            getline(inputString, tempString, ',');
            DropAddressPcode = stoi(tempString.c_str());
            //Distance + Cost
            getline(inputString, tempString, ',');
            DistanceBAddresses = stoi(tempString.c_str());
            getline(inputString, tempString, ',');
            TripCost = stod(tempString.c_str()); //stod method for converting to double


            //Load data into vector using structure constructor
            bookingInformation bInfo(
                //Name
                CustFirstName,
                CustLastName,
                //Date
                BDateDay,
                BDateMonth,
                BDateYear,
                //Pickup Address
                PickupAddressStreet,
                PickupAddressSuburb,
                PickupAddressTownCity,
                PickupAddressPcode,
                //Dropoff Address
                DropAddressStreet,
                DropAddressSuburb,
                DropAddressTownCity,
                DropAddressPcode,
                //Distance + Cost
                DistanceBAddresses,
                TripCost
            );


            bookingInfo.push_back(bInfo);
            line = "";
        }

    }

//Write CSV function - Need to update to use same switch case for directing information

void WriteUserCSV(vector<userInformation>& users, string filename )
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

void WriteBookTaxiCSV(vector<bookingInformation>& bookingInfo, string filename )
{
    int i = 0; //Starts at vector index of first driver
    ofstream appfile;
    appfile.open(filename, ios::out);

    for (auto itr = bookingInfo.begin(); itr != bookingInfo.end(); itr++) {

        appfile << bookingInfo[i].CustFirstName << "," << bookingInfo[i].CustLastName << "," << bookingInfo[i].BDateDay << "," << bookingInfo[i].BDateMonth << "," << bookingInfo[i].BDateYear << ","
            << bookingInfo[i].PickupAddressStreet << "," << bookingInfo[i].PickupAddressSuburb << "," << bookingInfo[i].PickupAddressTownCity << "," << bookingInfo[i].PickupAddressPcode << ","
            << bookingInfo[i].DropAddressStreet << "," << bookingInfo[i].DropAddressSuburb << "," << bookingInfo[i].DropAddressTownCity << bookingInfo[i].DropAddressPcode << "," << bookingInfo[i].DistanceBAddresses << "," << bookingInfo[i].TripCost << endl;
        i++;
    }

    appfile.close();

    //Init vars to load data into
//Name
    string CustFirstName;
    string CustLastName;
    //Date
    int BDateDay;
    int BDateMonth;
    int BDateYear;
    //Pickup Address
    string PickupAddressStreet;
    string PickupAddressSuburb;
    string PickupAddressTownCity;
    int PickupAddressPcode;
    //Dropoff Address
    string DropAddressStreet;
    string DropAddressSuburb;
    string DropAddressTownCity;
    int DropAddressPcode;
    //Distance + Cost
    int DistanceBAddresses;
    double TripCost;




}

//----------------------------------------------------------------------------------------------------------------------------
//Code snippets

//Testing member creation
//string FirstName = "test";
//string LastName = "test";
//string UserName = "test";
//string Password = "test";
//int IsAdmin = 0;
//userInformation user(FirstName, LastName, UserName, Password, IsAdmin);