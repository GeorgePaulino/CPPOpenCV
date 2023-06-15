#include "OpenCVSource.hpp"
// #include"SDLSource.hpp"
#include "SDLCodeTutorial.hpp"
#include "TankGame.hpp"
#include "OpenCV.hpp"
#include <string>

int main(int argc, char *args[])
{
    while (true)
    {
        int choice;
        std::cout << "[0] Start Game With The Current Field" << std::endl
                  << "[1] Capture a New Field" << std::endl
                  << "[2] exit" << std::endl
                  << std::endl;
        std::cin >> choice;
        std::cin.ignore();
        if(choice == 0){
            int **field = OpenCVCore("images/lines.jpeg");
            maingame(field);
        }
        else if(choice == 1){
            std::cout << "Write the IP of the Camera: ";
            std::string ip;
            std::getline(std::cin, ip);
            CapturePhoto(ip.c_str());
        }
        else{
            break;
        }
    }

    return 0;
}