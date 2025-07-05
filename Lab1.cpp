#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Simulate user database (username:password)
const string storedUsername = "admin";
const string storedPassword = "password123";

// Generate CAPTCHA
string generateCaptcha(int length = 4)
{
    string captcha = "";
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(0));
    for (int i = 0; i < length; i++)
    {
        captcha += chars[rand() % chars.length()];
    }
    return captcha;
}

// Simulate OTP
string generateOTP()
{
    srand(time(0));
    int otp = 100000 + rand() % 900000; // 6-digit number
    return to_string(otp);
}

// Password-based authentication
bool passwordLogin()
{
    string username, password;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if (username == storedUsername && password == storedPassword)
    {
        cout << "✅ Password verified.\n";
        return true;
    }
    else
    {
        cout << "❌ Invalid username or password.\n";
        return false;
    }
}

// CAPTCHA check
bool captchaVerification()
{
    string captcha = generateCaptcha();
    string userInput;

    cout << "CAPTCHA: " << captcha << endl;
    cout << "Enter CAPTCHA: ";
    cin >> userInput;

    if (userInput == captcha)
    {
        cout << "✅ CAPTCHA verified.\n";
        return true;
    }
    else
    {
        cout << "❌ CAPTCHA incorrect.\n";
        return false;
    }
}

// OTP check (simulate sending via console)
bool twoFactorAuth()
{
    string otp = generateOTP();
    string userInput;

    cout << "📲 Simulated OTP sent to your phone/email: " << otp << endl;
    cout << "Enter OTP: ";
    cin >> userInput;

    if (userInput == otp)
    {
        cout << "✅ OTP verified.\n";
        return true;
    }
    else
    {
        cout << "❌ OTP incorrect.\n";
        return false;
    }
}

int main()
{
    cout << "===== Authentication System =====" << endl;

    // Step 1: Password login
    if (!passwordLogin())
        return 0;

    // Step 2: CAPTCHA
    if (!captchaVerification())
        return 0;

    // Step 3: 2FA (OTP)
    if (!twoFactorAuth())
        return 0;

    // All steps passed
    cout << "🎉 Access Granted! You are logged in.\n";

    return 0;
}
