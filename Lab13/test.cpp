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
    // TODO: Demonstrate std::string
    // - getline to read
    // - .length() for size
    // - transform with toupper for uppercase
    // - .substr() for substrings
}

void vector_demo() {
    // TODO: Demonstrate std::vector
    // - push_back to add elements
    // - std::sort to sort
    // - .size() for size
}

void reference_demo() {
    // TODO: Demonstrate references
    // - Read two numbers
    // - Show before swap
    // - Call swap_ref (uses references, not pointers)
    // - Show after swap
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
