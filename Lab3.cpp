// malicious_logic2.cpp

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// --- Helper to append to a log file quietly
void stealthLog(const string &msg) {
  ofstream f("hidden.log", ios::app);
  f << msg << endl;
}

// --- 1) Trojan-horse: “secret” command hidden in menu
bool checkTrojan(const string &cmd) {
  if (cmd == "vvip") {
    // Secret backdoor: spawn a “shell” (simulation)
    cout << "\n*** Welcome, super-user! ***\n";
    cout << "Launching diagnostics...\n";
    cout << "[Diagnostics OK]\n";
    stealthLog("Trojan accessed by super-user");
    return true;
  }
  return false;
}

// --- 2) Logic-bomb: on a specific date, corrupt the log
void logicBomb() {
  time_t now = time(nullptr);
  tm *t = localtime(&now);
  // If it’s the 13th of any month at 00:00–00:05
  if (t->tm_mday == 7 && t->tm_hour == 18 && t->tm_min <= 40) {
    ofstream f("hidden.log"); // truncate file
    f << "SYSTEM COMPROMISED!\n";
    cout << "\n!!! Logic bomb triggered: log corrupted !!!\n";
    exit(1);
  }
}

// --- 3) Credential harvester: logs any “username/password” attempts
void harvestCreds() {
  string u, p;
  cout << "\n[Admin only] Enter username: ";
  cin >> u;
  cout << "[Admin only] Enter password: ";
  cin >> p;
  stealthLog("CREDS-> " + u + ":" + p);
  cout << "Credentials received. Access Denied.\n";
}

// --- Main “benign” calculator interface
int main() {
  logicBomb(); // check the bomb every run

  cout << "=== Simple Calculator ===\n"
       << "Commands: add, sub, mul, div, quit\n";
  //  << " (hint: try 'vvip' or 'creds')\n\n";

  string cmd;
  while (true) {
    cout << "> ";
    cin >> cmd;

    // Trojan check
    if (checkTrojan(cmd))
      continue;

    // Hidden creds command
    if (cmd == "creds") {
      harvestCreds();
      continue;
    }

    if (cmd == "quit")
      break;

    double a, b;
    cout << " Enter two numbers: ";
    cin >> a >> b;

    if (cmd == "add")
      cout << "  = " << (a + b) << "\n";
    else if (cmd == "sub")
      cout << "  = " << (a - b) << "\n";
    else if (cmd == "mul")
      cout << "  = " << (a * b) << "\n";
    else if (cmd == "div") {
      if (b != 0)
        cout << "  = " << (a / b) << "\n";
      else
        cout << "  Division by zero!\n";
    } else {
      cout << "Unknown command.\n";
    }
  }

  return 0;
}
