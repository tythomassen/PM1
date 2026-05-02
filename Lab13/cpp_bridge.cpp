#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// RAII Resource class - demonstrates automatic cleanup
class Resource {
private:
    int* data;
    size_t size;
public:
    Resource(size_t n) : size(n) {
        data = new int[n];
        cout << "Resource constructed: allocated " << n << " integers" << endl;
    }
    
    ~Resource() {
        delete[] data;
        cout << "Resource destructed: memory automatically freed" << endl;
    }
    
    void fill(int value) {
        for (size_t i = 0; i < size; i++) data[i] = value;
    }
    
    void print() const {
        cout << "Data: ";
        for (size_t i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }
};

// Reference-based swap (NOT pointer-based)
void swap_ref(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void string_demo();
void vector_demo();
void reference_demo();
void raii_demo();

int main() {
    int choice;
    cout << "=== C++ Bridge Lab ===" << endl;
    cout << "1. std::string" << endl;
    cout << "2. std::vector" << endl;
    cout << "3. References" << endl;
    cout << "4. RAII Class" << endl;
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1: string_demo(); break;
        case 2: vector_demo(); break;
        case 3: reference_demo(); break;
        case 4: raii_demo(); break;
        default: cout << "Invalid choice" << endl;
    }
    return 0;
}

void string_demo() {
    string s; // declare std::string (not char[])
    cout << "\n--- String Demo ---" << endl;
    cout << "Enter a string: ";
    getline(cin, s); // read full line including spaces into std::string

    cout << "Original string: " << s << endl; // show the original input
    cout << "Length: " << s.length() << " characters" << endl; // .length() returns number of chars

    string upper = s; // copy original so we can transform without changing s
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper); // convert every char to uppercase
    cout << "Uppercase: " << upper << endl; // show the uppercase version

    if (s.length() >= 3) { // guard against empty/short strings before calling substr
        cout << "First 3 chars (substr): " << s.substr(0, 3) << endl; // substr(pos, len) extracts a slice
    }
    cout << "Last char: " << s.back() << endl; // .back() returns the final character
}

void vector_demo() {
    vector<int> v; // declare std::vector (not a C array)
    int n, val;
    cout << "\n--- Vector Demo ---" << endl;
    cout << "How many integers to enter? ";
    cin >> n; // read how many values the user wants to store

    for (int i = 0; i < n; i++) {
        cout << "Enter value " << (i + 1) << ": ";
        cin >> val;
        v.push_back(val); // push_back dynamically grows the vector by one element
    }

    cout << "Original values (" << v.size() << " elements): "; // .size() reports current element count
    for (int x : v) cout << x << " "; // print every element before sorting
    cout << endl;

    sort(v.begin(), v.end()); // std::sort from <algorithm> sorts in ascending order in-place

    cout << "Sorted values: ";
    for (int x : v) cout << x << " "; // print sorted sequence
    cout << endl;
}

void reference_demo() {
    int a, b;
    cout << "\n--- Reference Demo ---" << endl;
    cout << "Enter first integer: ";
    cin >> a; // read first value
    cout << "Enter second integer: ";
    cin >> b; // read second value

    cout << "Before swap (ref &): a = " << a << ", b = " << b << endl; // show values before the swap

    swap_ref(a, b); // passes a and b by reference (&) — no copies, no pointers

    cout << "After swap  (ref &): a = " << a << ", b = " << b << endl; // show swapped values
}

void raii_demo() {
    cout << "\n--- RAII Demo ---" << endl;
    
    int n;
    cout << "Enter array size: ";
    cin >> n;
    
    {  // Create a nested scope
        cout << "\nEntering scope..." << endl;
        Resource res(n);  // Constructor called
        res.fill(42);
        res.print();
        cout << "Leaving scope..." << endl;
    }  // Destructor called AUTOMATICALLY here!
    
    cout << "\nScope exited - no manual free needed!" << endl;
    cout << "This is RAII: Resource Acquisition Is Initialization" << endl;
}
