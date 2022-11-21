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
        this->BDateYear = BDateYear;

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

struct lostItems {
    //Status 
    int ReportStatus;
    //Name
    string CustFirstName;
    string CustLastName;
    //Trip
    int TripBookingID;
    //Items
    int nItemsLost;
    vector<string> ItemsLostVect; //Create vector for storing multiple items

    //Constructor
    lostItems(
        int ReportStatus,
        string CustFirstName,
        string CustLastName,
        int TripBookingID,
        int nItemsLost,
        vector<string> ItemsLostVect)
    {
        this->ReportStatus = ReportStatus;
        this->CustFirstName = CustFirstName;
        this->CustLastName = CustLastName;
        this->TripBookingID = TripBookingID;
        this->nItemsLost = nItemsLost;
        this->ItemsLostVect = ItemsLostVect;
    }

};

//----------------------------------------------------------------------------------------------------------------------------
//Global variables

enum itemStatus { lost, found };
bool IsAdminUser = false;
double costPerKm = 1.90;

//----------------------------------------------------------------------------------------------------------------------------
//Prototype functions

//Load & write
void LoadUsersCSV(vector<userInformation>&, string);
void LoadBookingInfoCSV(vector<bookingInformation>&, string);
void LoadLostItemsCSV(vector<lostItems>&, string);

void WriteUserCSV(vector<userInformation>&, string);
void WriteBookTaxiCSV(vector<bookingInformation>&, string);
void WriteLostItemsCSV(vector<lostItems>&, string);

//Misc
void Line(int, char, bool); //length, character, dropline after called t/f

//Menus
void DisplayUserMenu();
void DisplayBookingMenu();
void DisplayLostItemMenu();

//User functions
void CreateNewUser(vector<userInformation>&);
void ViewExistingUser(vector<userInformation>&);
void RemoveUser(vector<userInformation>&);

//Book taxi functions
void BookRide(vector<bookingInformation>&);
void ViewPastBookings(vector<bookingInformation>&);

//Lost item functions
void ReportLostItem(vector<lostItems>&, vector<bookingInformation>&);
void ViewLostItemsReports(vector<lostItems>&, vector<bookingInformation>&);


//----------------------------------------------------------------------------------------------------------------------------
//Main

int main()
{

    // Load in existing user data at program start into vector structures
    //------------------------------------------------------------------------------------

    vector<userInformation> users; //Create member vector of users
    LoadUsersCSV(users, "users.csv"); // Load users 

    vector<bookingInformation> bookingInfo; //Create member vector of users
    LoadBookingInfoCSV(bookingInfo, "bookinginfo.csv"); // Load booking info 

    vector<lostItems> itemReport; //Create member vector of users
    LoadLostItemsCSV(itemReport, "itemslost.csv"); // Load lost item database 

    //------------------------------------------------------------------------------------
    // Display login screen

    cout << endl;
    cout << "Taxi Management System " << endl;
    Line(80, '=', true);
    cout << endl;
    cout << "Please login to continue." << endl;

    // init variables for input
    string username;
    string password;

    //Check three attempts loop
    //Loop three attempts
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

    //------------------------------------------------------------------------------------
    // Display main menu

mainmenu:
    system("CLS"); //Clear console
    cout << endl;
    cout << "Main menu" << endl;
    Line(80, '=', true);
    cout << endl;
    cout << "Please select one of the following options\n\n";
    cout << "1) Book a Taxi" << endl;
    cout << "2) Lodge Complaint" << endl;
    cout << "3) Report and view lost items" << endl;
    cout << "4) Exit Program" << endl;
    if (IsAdminUser)
    {
        cout << "5) Add, view or remove users - Admin only" << endl;
    }

    cout << endl;
    cout << "Enter selection : ";

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

            itemReport.clear();
            LoadLostItemsCSV(itemReport, "itemslost.csv"); // Load lost item database 

            Line(80, '-', true);
            cout << endl;
            cout << "Select one of the following options:" << endl;
            cout << "1) Return to previous menu" << endl;
            cout << "2) Return to main menu" << endl;

            int bookRideMenu;
            cin >> bookRideMenu;

            switch (bookRideMenu)
            {
            case 1:
                goto booktaximenu;
            case 2:
                goto mainmenu;
            }

        case 2:
            system("CLS");
            ViewPastBookings(bookingInfo);


            Line(80, '-', true);
            cout << endl;
            cout << "Select one of the following options:" << endl;
            cout << "1) Return to previous menu" << endl;
            cout << "2) Return to main menu" << endl;

            cin >> bookRideMenu;

            switch (bookRideMenu)
            {
            case 1:
                goto booktaximenu;
            case 2:
                goto mainmenu;
            }

        }
        break;

    case 3:

    lostitemsmenu:

        system("CLS"); //Clear console
        DisplayLostItemMenu();

        //Reload users vector contents to reflect any changes
        itemReport.clear();
        LoadLostItemsCSV(itemReport, "itemslost.csv"); // Load users 

        int lostItemMenu;
        cin >> lostItemMenu;

        switch (lostItemMenu) {
        case 1:
            ReportLostItem(itemReport, bookingInfo);
            break;
        case 2:
            ViewLostItemsReports(itemReport, bookingInfo);
            break;
        }

        Line(80, '-', true);
        cout << endl;
        cout << "Select one of the following options:" << endl;
        cout << "1) Return to previous menu" << endl;
        cout << "2) Return to main menu" << endl;

        cin >> lostItemMenu;

        switch (lostItemMenu)
        {
        case 1:
            goto lostitemsmenu;
        case 2:
            goto mainmenu;
        }

        break;


    case 5:
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
            CreateNewUser(users);

            //Reload users vector contents to reflect any changes
            users.clear();
            LoadUsersCSV(users, "users.csv"); // Load users 

            cout << endl;
            Line(80, '-', true);
            cout << "Select one of the following options:" << endl;
            cout << "1) Return to previous menu" << endl;
            cout << "2) Return to main menu" << endl;

            int newuserAccountMenu;
            cin >> newuserAccountMenu;

            switch (newuserAccountMenu)
            {
            case 1:
                goto usermanagementmenu;
            case 2:
                goto mainmenu;
            }

        case 2:
            //View existing users
            ViewExistingUser(users);

            //Reload users vector contents to reflect any changes
            users.clear();
            LoadUsersCSV(users, "users.csv"); // Load users 

            Line(80, '-', true);
            cout << endl;
            cout << "Select one of the following options:" << endl;
            cout << "1) Return to previous menu" << endl;
            cout << "2) Return to main menu" << endl;
            cout << "3) Remove a user" << endl;

            int viewUserMenu;
            cin >> viewUserMenu;

            switch (viewUserMenu)
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
        break;
    }

}

//----------------------------------------------------------------------------------------------------------------------------
//Lost items functions

void DisplayLostItemMenu() {
    cout << endl;
    cout << "Report and view lost items\n";
    Line(80, '=', true);
    cout << endl;
    cout << "1) Report a new lost item/s" << endl;
    cout << "2) View lost item reports" << endl;
    cout << endl;
    cout << "Enter selection : ";
}

void ReportLostItem(vector<lostItems>& itemReport, vector<bookingInformation>& bookingInfo) {

    //Init vars to load data into
    //Status 
    int ReportStatus = lost; //Default to lost
    //Name
    string CustFirstName;
    string CustLastName;
    //Trip
    int TripBookingID;
    //Items
    int nItemsLost;
    vector<string> ItemsLostVect; //Create vector for storing multiple items

    //Display booking screen - enter new customer
    cout << endl;
    cout << "Create lost item report" << endl;
    Line(80, '=', true);
    cout << endl;

    cout << "Select a past booking to attach report to using the ""Trip #"" number \n";
    Line(80, '-', true);
    cout << endl;
    cout << endl;

    for (int i = 0; i < bookingInfo.size(); i++)
    {
        cout << "Trip # " << i << " " << "Trip date : " << bookingInfo[i].BDateDay << "/" << bookingInfo[i].BDateMonth << "/" << bookingInfo[i].BDateYear
            << " Customer name : " << bookingInfo[i].CustFirstName << " " << bookingInfo[i].CustLastName << endl;

        cout << "|" << setw(40) << left << "Pickup address" << "|" << setw(40) << left << "Dropoff address" << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressStreet << right << "|" << setw(40) << left << bookingInfo[i].DropAddressStreet << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressSuburb << right << "|" << setw(40) << left << bookingInfo[i].DropAddressSuburb << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressTownCity << right << "|" << setw(40) << left << bookingInfo[i].DropAddressTownCity << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressPcode << right << "|" << setw(40) << left << bookingInfo[i].DropAddressPcode << "|" << "\n";

        cout << "Fare cost : " << bookingInfo[i].TripCost << "\t" << "Distance : " << bookingInfo[i].DistanceBAddresses << "km";
        cout << endl;
        Line(80, '-', true);
    }

    //Add booking number to itemReport ID
    cout << endl;
    cout << endl;

reenterTripID:

    cout << "Select past booking ""Trip #"" number : ";
    cin >> TripBookingID;

    if (TripBookingID >= bookingInfo.size()) {
        cout << "Booking ID outside of range, please reenter booking ID\n";
        goto reenterTripID;
    }

    cout << endl;
    system("CLS");

    //Confirm selected booking to attach lost item report to
    cout << "Booking number " << TripBookingID << " selected!\n";
    cout << endl;

    //Assign customer name details to lost item database
    CustFirstName = bookingInfo[TripBookingID].CustFirstName;
    CustLastName = bookingInfo[TripBookingID].CustLastName;

    cout << "Add lost item details\n";
    Line(80, '-', true);
    cout << endl;

    //Get lost item input from user
    cout << "Enter the number of lost items : ";
    cin >> nItemsLost;
    cout << endl;

    cin.clear();
    cin.ignore();

    //Clear existing items in vector
    ItemsLostVect.clear();

    //Loop number of items add to vector
    string tempString;
    for (int i = 0; i < nItemsLost; i++) {
        cout << "Enter details of lost item #" << i << "\n";
        getline(cin, tempString);
        ItemsLostVect.push_back(tempString);
    }

    //Display lost item report
    system("CLS");
    cout << nItemsLost << " items added!\n";
    cout << endl;

    cout << "Trip # " << TripBookingID << " " << "Trip date : " << bookingInfo[TripBookingID].BDateDay << "/" << bookingInfo[TripBookingID].BDateMonth << "/" << bookingInfo[TripBookingID].BDateYear
        << " Customer name : " << CustFirstName << " " << CustLastName << " Report status :";

    if (ReportStatus == lost) {
        cout << "lost";
    }
    else {
        cout << "found";
    }
    cout << endl;

    Line(83, '-', true);
    cout << "|" << setw(40) << left << "Pickup address" << "|" << setw(40) << left << "Dropoff address" << "|" << "\n";
    cout << "|" << setw(40) << bookingInfo[TripBookingID].PickupAddressStreet << right << "|" << setw(40) << left << bookingInfo[TripBookingID].DropAddressStreet << "|" << "\n";
    Line(83, '-', true);
    cout << "|" << setw(40) << left << "Item number" << "|" << setw(40) << left << "Item description" << "|" << "\n";
    Line(83, '-', true);

    //Print out items added to vector
    for (int i = 0; i < nItemsLost; i++) {
        cout << "|" << setw(40) << left << i << "|" << setw(40) << left << ItemsLostVect[i] << "|" << "\n";
    }
    Line(83, '-', true);

    // Push new user into vector
    lostItems newreport(
        ReportStatus,
        CustFirstName,
        CustLastName,
        TripBookingID,
        nItemsLost,
        ItemsLostVect
    );

    itemReport.push_back(newreport);

    WriteLostItemsCSV(itemReport, "itemslost.csv");
}


void ViewLostItemsReports(vector<lostItems>& itemReport, vector<bookingInformation>& bookingInfo) {

    //Display booking screen - enter new customer
    cout << endl;
    cout << "View lost item reports" << endl;
    Line(80, '=', true);
    cout << endl;


    for (int i = 0; i < itemReport.size(); i++) {

        //Display header for each report - pull data from both itemReport and bookingInfo vectors
        cout << "Trip # " << itemReport[i].TripBookingID << " " << "Trip date : " << bookingInfo[itemReport[i].TripBookingID].BDateDay << "/" << bookingInfo[itemReport[i].TripBookingID].BDateMonth << "/" << bookingInfo[itemReport[i].TripBookingID].BDateYear
            << " Customer name : " << itemReport[i].CustFirstName << " " << itemReport[i].CustLastName << " Report status :";

        //Display status
        if (itemReport[i].ReportStatus == lost) {
            cout << "lost";
        }
        else {
            cout << "found";
        }
        cout << endl;

        Line(83, '-', true);
        cout << "|" << setw(40) << left << "Pickup address" << "|" << setw(40) << left << "Dropoff address" << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressStreet << right << "|" << setw(40) << left << bookingInfo[i].DropAddressStreet << "|" << "\n";
        Line(83, '-', true);
        cout << "|" << setw(40) << left << "Item number" << "|" << setw(40) << left << "Item description" << "|" << "\n";
        Line(83, '-', true);

        //Print out items added to vector
        for (int j = 0; j < itemReport[i].nItemsLost; j++) {
            cout << "|" << setw(40) << left << j << "|" << setw(40) << left << itemReport[i].ItemsLostVect[j] << "|" << "\n";
        }

        Line(83, '-', true);
        cout << endl;

    }

    int lostItemMenu;

    cout << endl;
    cout << "Select one of the following options:" << endl;
    cout << "1) Change item status found/lost" << endl;
    cout << "2) Clear reports" << endl;
    cout << "3) Exit" << endl;

    cin >> lostItemMenu;
    cout << endl;

    switch (lostItemMenu) {
    case 1:
    reenterTripID:

        int TripBookingID;

        cout << "Select past booking ""Trip #"" number to change report status : ";
        cin >> TripBookingID;

        if (TripBookingID > itemReport.size() - 1) {
            cout << "Booking ID outside of range, please reenter booking ID\n";
            goto reenterTripID;
        }

        int statusMenu;

        cout << endl;
        cout << "Change report status of Trip # : " << TripBookingID << endl;
        cout << "1) Found" << endl;
        cout << "2) Lost" << endl;

        cin >> statusMenu;
        cout << endl;

        switch (statusMenu) {
        case 1:
            itemReport[TripBookingID].ReportStatus = found;
            cout << "Status changed : found!" << endl;
            break;
        case 2:
            itemReport[TripBookingID].ReportStatus = lost;
            cout << "Status changed : lost!" << endl;
            break;
        }
        break;
    case 2:
        itemReport.clear();
        cout << "Reports cleared!" << endl;
        break;
    case 3:
        break;
    }

    WriteLostItemsCSV(itemReport, "itemslost.csv");
}


//----------------------------------------------------------------------------------------------------------------------------
//Book taxi functions

void DisplayBookingMenu() {
    cout << endl;
    cout << "Book Taxi, View past bookings\n";
    Line(80, '=', true);
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
    int BDateDay = 0;
    int BDateMonth = 0;
    int BDateYear = 0;
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
    Line(80, '=', true);
    cout << endl;

    cout << "Enter new customer\n";
    Line(80, '-', true);
    cout << "Name\n";
    cout << "Enter person's first name: ";
    cin >> CustFirstName;
    cout << "Enter person's last name: ";
    cin >> CustLastName;
    cout << endl;
    cout << "Customer added to database!\n";
    Line(80, '-', true);


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

        cout << BDateDay << "/" << BDateMonth << "/" << BDateYear << "\n\n";

        break;
    case 2:
        cout << "Enter day (dd): " << endl;
        cin >> BDateDay;
        cout << "Enter month (mm): " << endl;
        cin >> BDateMonth;
        cout << "Enter year (yy): " << endl;
        cin >> BDateYear;
        cout << "Selected date added!\n";
        break;
    }

    //Add pickup & dropoff address
    cout << endl;
    cout << "Add addresses\n";
    Line(80, '-', true);


    //Clear datastream before using getline
    cin.clear();
    cin.ignore();

    //Pickup Address
    cout << "Pickup address\n";
    cout << "Enter address number/street): ";
    getline(cin, PickupAddressStreet);
    cout << "Enter suburb: ";
    getline(cin, PickupAddressSuburb);
    cout << "Enter town/city: ";
    getline(cin, PickupAddressTownCity);
    cout << "Enter Postcode: ";
    cin >> PickupAddressPcode;
    cout << endl;

    cin.clear();
    cin.ignore();

    //Dropoff Address
    cout << "Dropoff address\n";
    cout << "Enter address number/street) : ";
    getline(cin, DropAddressStreet);
    cout << "Enter suburb : ";
    getline(cin, DropAddressSuburb);
    cout << "Enter town/city : ";
    getline(cin, DropAddressTownCity);
    cout << "Enter Postcode: ";
    cin >> DropAddressPcode;
    cout << endl;

    cin.clear();
    cin.ignore();

    cout << "Addresses added!\n";

    cout << endl;
    cout << "Calculate Taxi Fare\n";
    Line(80, '-', true);
    cout << endl;

    //Generate random distance between 1 - 20kms

    srand(time(NULL)); //Reset number seed
    //Set up the boundary
    int min = 1;
    int max = 20 + 1; //Add +1 to include 20 in range
    DistanceBAddresses = rand() % (min - max) + min;

    TripCost = costPerKm * DistanceBAddresses;

    cout << "Distance calculated between addresses = " << DistanceBAddresses << "km" << endl;
    cout << "Cost per Km = $" << costPerKm << endl;
    cout << "Taxi fare cost = $" << TripCost << endl;

    // Push new user into vector
    bookingInformation newbooking(
        CustFirstName,
        CustLastName,
        BDateDay,
        BDateMonth,
        BDateYear,
        PickupAddressStreet,
        PickupAddressSuburb,
        PickupAddressTownCity,
        PickupAddressPcode,
        DropAddressStreet,
        DropAddressSuburb,
        DropAddressTownCity,
        DropAddressPcode,
        DistanceBAddresses,
        TripCost);

    bookingInfo.push_back(newbooking);

    //Update CSV
    WriteBookTaxiCSV(bookingInfo, "bookinginfo.csv");

}

void ViewPastBookings(vector<bookingInformation>& bookingInfo) {
    //Display all past bookings 
    cout << endl;
    cout << "View past taxi bookings" << endl;
    Line(80, '=', true);
    cout << endl;

    cout << "Current user database contents\n";
    Line(83, '-', true);
    for (int i = 0; i < bookingInfo.size(); i++)
    {
        cout << "Trip # " << i << " " << "Trip date : " << bookingInfo[i].BDateDay << "/" << bookingInfo[i].BDateMonth << "/" << bookingInfo[i].BDateYear
            << " Customer name : " << bookingInfo[i].CustFirstName << " " << bookingInfo[i].CustLastName << endl;

        cout << "|" << setw(40) << left << "Pickup address" << "|" << setw(40) << left << "Dropoff address" << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressStreet << right << "|" << setw(40) << left << bookingInfo[i].DropAddressStreet << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressSuburb << right << "|" << setw(40) << left << bookingInfo[i].DropAddressSuburb << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressTownCity << right << "|" << setw(40) << left << bookingInfo[i].DropAddressTownCity << "|" << "\n";
        cout << "|" << setw(40) << bookingInfo[i].PickupAddressPcode << right << "|" << setw(40) << left << bookingInfo[i].DropAddressPcode << "|" << "\n";

        cout << "Fare cost $: " << bookingInfo[i].TripCost << "\t" << "Distance : " << bookingInfo[i].DistanceBAddresses << "km";
        cout << endl;
        Line(83, '-', true);
    }
}

//----------------------------------------------------------------------------------------------------------------------------
// User functions

void DisplayUserMenu() {
    cout << endl;
    cout << "Add, view and remove existing users\n";
    Line(80, '=', true);
    cout << endl;
    cout << "1) Add new user" << endl;
    cout << "2) View or remove existing users and account privledges" << endl;
    cout << endl;
    cout << "Enter selection : ";
}

void CreateNewUser(vector<userInformation>& users) {

    string newuserFirstName;
    string newuserLastName;
    string newuserUserName;
    string newuserPassword;
    int newuserAdminRights;

    // show screen to create a new user.
    cout << endl;
    cout << "Add new user account" << endl;
    Line(80, '=', true);
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

    // Push new user into vector
    userInformation newuser(newuserFirstName, newuserLastName, newuserUserName, newuserPassword, newuserAdminRights);
    users.push_back(newuser);

    // Return data to test if the user data has been recorded at back of vector
    cout << endl;
    cout << "New user account created!";
    cout << endl;
    cout << "Name: " << users.back().FirstName << " " << users.back().LastName << endl;
    cout << "Username: " << users.back().UserName << "   Password: " << users.back().Password;

    if (users.back().IsAdmin == true) {
        cout << "   Admin account: true" << endl;
    }
    else {
        cout << "   Admin account: false" << endl;
    }

    //Update csv
    WriteUserCSV(users, "users.csv");

}

void ViewExistingUser(vector<userInformation>& users) {

    // Display all users
    cout << endl;
    cout << "Current user database contents\n";
    Line(80, '-', true);
    for (int i = 0; i < users.size(); i++)
    {
        cout << " (" << i << ") " << users[i].FirstName << " " << users[i].LastName << "    Username : " << users[i].UserName << "\tAdmin : ";

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
}

void RemoveUser(vector<userInformation>& users) {

    int userToRemove;

    cout << "Remove a user\n";
    Line(80, '=', true);
    cout << endl;
    cout << endl;
    // display all users
    Line(80, '-', true);
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
    Line(80, '-', true);
    cout << endl;
    cout << endl;

    cout << "Enter the number assocated with the user: ";
    cin >> userToRemove;

    // Remove the user. It's as simple as this one line.
    users.erase(users.begin() + userToRemove);
    // Update the CSV file
    WriteUserCSV(users, "users.csv");
}

//----------------------------------------------------------------------------------------------------------------------------
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

void LoadLostItemsCSV(vector<lostItems>& itemReport, string filename) {
    ifstream inputFile;
    inputFile.open(filename);
    string line = "";

    while (getline(inputFile, line))
    {
        //Init vars to load data into
        //Status 
        int ReportStatus;
        //Name
        string CustFirstName;
        string CustLastName;
        //Trip
        int TripBookingID;
        //Items
        int nItemsLost;
        vector<string> ItemsLostVect; //Create vector for storing multiple items

        //Takes string and separates data using comma delimiter
        string tempString;
        stringstream inputString(line);

        getline(inputString, tempString, ',');
        ReportStatus = stoi(tempString.c_str());

        getline(inputString, CustFirstName, ',');
        getline(inputString, CustLastName, ',');

        getline(inputString, tempString, ',');
        TripBookingID = stoi(tempString.c_str());

        getline(inputString, tempString, ',');
        nItemsLost = stoi(tempString.c_str());

        //Loop and read the last elements into there own vector to push to structure. 
        for (int i = 0; i < nItemsLost; i++) {
            getline(inputString, tempString, ',');
            ItemsLostVect.push_back(tempString);
        }

        //Load data into vector using structure constructor
        lostItems reportItems(ReportStatus, CustFirstName, CustLastName, TripBookingID, nItemsLost, ItemsLostVect);
        itemReport.push_back(reportItems);
        line = "";
    }
}

void LoadUsersCSV(vector<userInformation>& users, string filename) {

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

void WriteUserCSV(vector<userInformation>& users, string filename)
{
    int i = 0; //Starts at vector index of first user
    ofstream appfile;
    appfile.open(filename, ios::out);

    for (auto itr = users.begin(); itr != users.end(); itr++) {

        appfile << users[i].FirstName << "," << users[i].LastName << "," << users[i].UserName << "," << users[i].Password << "," << users[i].IsAdmin << endl;
        i++;
    }

    appfile.close();
}

void WriteBookTaxiCSV(vector<bookingInformation>& bookingInfo, string filename)
{
    int i = 0; //Starts at vector index of first driver
    ofstream appfile;
    appfile.open(filename, ios::out);

    for (auto itr = bookingInfo.begin(); itr != bookingInfo.end(); itr++) {

        appfile << bookingInfo[i].CustFirstName << "," << bookingInfo[i].CustLastName << "," << bookingInfo[i].BDateDay << "," << bookingInfo[i].BDateMonth << "," << bookingInfo[i].BDateYear << ","
            << bookingInfo[i].PickupAddressStreet << "," << bookingInfo[i].PickupAddressSuburb << "," << bookingInfo[i].PickupAddressTownCity << "," << bookingInfo[i].PickupAddressPcode << ","
            << bookingInfo[i].DropAddressStreet << "," << bookingInfo[i].DropAddressSuburb << "," << bookingInfo[i].DropAddressTownCity << "," << bookingInfo[i].DropAddressPcode << "," << bookingInfo[i].DistanceBAddresses << "," << bookingInfo[i].TripCost << endl;
        i++;
    }

    appfile.close();

}

void WriteLostItemsCSV(vector<lostItems>& itemReport, string filename)
{
    int i = 0; //Starts at vector index of first user
    ofstream appfile;
    appfile.open(filename, ios::out);

    //Nested for loop

    for (auto itr = itemReport.begin(); itr != itemReport.end(); itr++) {

        appfile << itemReport[i].ReportStatus << "," << itemReport[i].CustFirstName << "," << itemReport[i].CustLastName << "," << itemReport[i].TripBookingID << "," << itemReport[i].nItemsLost;

        //Loop and write the last elements from vector to end of csv. 

        for (int j = 0; j < itemReport[i].ItemsLostVect.size(); j++) {
            appfile << "," << itemReport[i].ItemsLostVect[j];
        } //Fifth element of vector is the number of items

        appfile << endl;

        i++;
    }

    appfile.close();
}

//----------------------------------------------------------------------------------------------------------------------------
//Code snippets