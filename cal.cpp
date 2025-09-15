#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Calculator {
private:
    double result;
    bool hasResult;
    
public:
    Calculator() : result(0.0), hasResult(false) {}
    
    // Perform calculation
    double calculate(double num1, char op, double num2) {
        switch(op) {
            case '+':
                return num1 + num2;
            case '-':
                return num1 - num2;
            case '*':
            case 'x':
            case 'X':
                return num1 * num2;
            case '/':
                if(num2 == 0) {
                    throw runtime_error("Error: Division by zero!");
                }
                return num1 / num2;
            case '%':
                if(num2 == 0) {
                    throw runtime_error("Error: Division by zero!");
                }
                return fmod(num1, num2);
            case '^':
                return pow(num1, num2);
            default:
                throw invalid_argument("Error: Invalid operator!");
        }
    }
    
    // Validate numeric input
    bool isValidNumber(const string& str) {
        if (str.empty()) return false;
        
        char* end;
        strtod(str.c_str(), &end);
        return end != str.c_str() && *end == '\0';
    }
    
    // Clear result
    void clear() {
        result = 0.0;
        hasResult = false;
        cout << "Calculator cleared." << endl;
    }
    
    // Display menu
    void displayMenu() {
        cout << "\n=== CALCULATOR MENU ===" << endl;
        cout << "Operations: +, -, *, /, %, ^ (power)" << endl;
        cout << "Commands:" << endl;
        cout << "  'c' or 'clear' - Clear calculator" << endl;
        cout << "  'h' or 'help'  - Show this menu" << endl;
        cout << "  'q' or 'quit'  - Exit calculator" << endl;
        cout << "  'ans'          - Use previous result" << endl;
        cout << "Examples:" << endl;
        cout << "  5 + 3" << endl;
        cout << "  ans * 2" << endl;
        cout << "  2.5 / 1.25" << endl;
        cout << "  2 ^ 8" << endl;
        cout << "======================" << endl;
    }
    
    // Format and display result
    void displayResult(double calcResult, const string& expression) {
        result = calcResult;
        hasResult = true;
        
        cout << fixed << setprecision(10);
        
        // Remove trailing zeros for cleaner display
        ostringstream oss;
        oss << calcResult;
        string resultStr = oss.str();
        
        cout << expression << " = " << calcResult << endl;
        cout << "Answer: " << calcResult << " (use 'ans' to reuse this value)" << endl;
    }
    
    // Main calculator loop
    void run() {
        string input, num1_str, num2_str;
        char op;
        double num1, num2, calcResult;
        
        cout << "=== Advanced C++ Calculator ===" << endl;
        cout << "Type 'help' for instructions or 'quit' to exit." << endl;
        displayMenu();
        
        while(true) {
            cout << "\nEnter calculation: ";
            getline(cin, input);
            
            // Handle empty input
            if(input.empty()) {
                cout << "Please enter a calculation or command." << endl;
                continue;
            }
            
            // Convert to lowercase for command checking
            string command = input;
            transform(command.begin(), command.end(), command.begin(), ::tolower);
            
            // Handle commands
            if(command == "quit" || command == "q") {
                cout << "Thank you for using the calculator. Goodbye!" << endl;
                break;
            }
            else if(command == "help" || command == "h") {
                displayMenu();
                continue;
            }
            else if(command == "clear" || command == "c") {
                clear();
                continue;
            }
            
            // Parse input
            stringstream ss(input);
            ss >> num1_str >> op >> num2_str;
            
            if(ss.fail() || num1_str.empty() || num2_str.empty()) {
                cout << "Error: Invalid input format. Use format: number operator number" << endl;
                cout << "Example: 5 + 3" << endl;
                continue;
            }
            
            // Handle 'ans' keyword for first number
            if(num1_str == "ans") {
                if(!hasResult) {
                    cout << "Error: No previous result available." << endl;
                    continue;
                }
                num1 = result;
            }
            else if(!isValidNumber(num1_str)) {
                cout << "Error: '" << num1_str << "' is not a valid number." << endl;
                continue;
            }
            else {
                try {
                    num1 = stod(num1_str);
                } catch(const exception& e) {
                    cout << "Error: Invalid number format for '" << num1_str << "'" << endl;
                    continue;
                }
            }
            
            // Handle 'ans' keyword for second number
            if(num2_str == "ans") {
                if(!hasResult) {
                    cout << "Error: No previous result available." << endl;
                    continue;
                }
                num2 = result;
            }
            else if(!isValidNumber(num2_str)) {
                cout << "Error: '" << num2_str << "' is not a valid number." << endl;
                continue;
            }
            else {
                try {
                    num2 = stod(num2_str);
                } catch(const exception& e) {
                    cout << "Error: Invalid number format for '" << num2_str << "'" << endl;
                    continue;
                }
            }
            
            // Create expression string for display
            string expr = (num1_str == "ans" ? to_string(num1) : num1_str) + " " + op + " " + 
                         (num2_str == "ans" ? to_string(num2) : num2_str);
            
            // Perform calculation
            try {
                calcResult = calculate(num1, op, num2);
                displayResult(calcResult, expr);
            }
            catch(const exception& e) {
                cout << e.what() << endl;
            }
        }
    }
};

// Function to demonstrate basic usage
void demonstrateCalculator() {
    Calculator calc;
    
    cout << "\n=== Calculator Demo ===" << endl;
    
    try {
        cout << "Basic Operations:" << endl;
        cout << "10 + 5 = " << calc.calculate(10, '+', 5) << endl;
        cout << "10 - 5 = " << calc.calculate(10, '-', 5) << endl;
        cout << "10 * 5 = " << calc.calculate(10, '*', 5) << endl;
        cout << "10 / 5 = " << calc.calculate(10, '/', 5) << endl;
        cout << "10 % 3 = " << calc.calculate(10, '%', 3) << endl;
        cout << "2 ^ 8 = " << calc.calculate(2, '^', 8) << endl;
        
        cout << "\nDecimal Operations:" << endl;
        cout << "3.14 + 2.86 = " << calc.calculate(3.14, '+', 2.86) << endl;
        cout << "7.5 / 2.5 = " << calc.calculate(7.5, '/', 2.5) << endl;
        cout << "2.5 ^ 3 = " << calc.calculate(2.5, '^', 3) << endl;
        
    } catch(const exception& e) {
        cout << "Error in demo: " << e.what() << endl;
    }
    
    cout << "\nDemo completed. Starting interactive mode..." << endl;
}

int main() {
    cout << "=== Advanced C++ Calculator Application ===" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Interactive Calculator (i)" << endl;
    cout << "2. Demo Mode (d)" << endl;
    cout << "Enter your choice: ";
    
    string choice;
    getline(cin, choice);
    
    Calculator calc;
    
    if(choice == "1" || choice == "i" || choice == "I") {
        calc.run();
    }
    else if(choice == "2" || choice == "d" || choice == "D") {
        demonstrateCalculator();
        calc.run();
    }
    else {
        cout << "Invalid choice. Starting interactive mode..." << endl;
        calc.run();
    }
    
    return 0;
}