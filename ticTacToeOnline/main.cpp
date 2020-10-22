#include <iostream>

void server();
void client();

int main()
{
    char typeOfConnection;
    std::cout << "Enter type of connection. ";
    std::cin >> typeOfConnection;
    if(typeOfConnection == 's') {
       server();
    } else if(typeOfConnection == 'c') {
       client();
    } else {
        std::cout << std::endl << "Incorrect input.";
    }
    return 0;
}
