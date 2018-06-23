#include<iostream>
#include<string.h>

const int B[] = {1000,
                900, 500, 400, 100,
                90, 50, 40, 10,
                9, 5, 4, 1};

const std::string R[] = {"M",
                        "CM", "D", "CD", "C",
                        "XC", "L", "XL", "X",
                        "IX", "V", "IV", "I"};

int arab2bin (const char *x){
    if (x[0] == '0'){
        std::cerr << "Zero at first position" << std::endl;
        return 0;
    }
    else{
        int i = 0;
        while(x[i] != '\0'){
            if ((int)x[i] < 48 || (int)x[i] > 57 || i >= 4){
                std::cerr << "Invalid data" << std::endl;
                return 0;
            }
            i++;
        }
    }
    return std::stoi(x);
}

int main(int argc, char *argv[]){
    int check;
    if (argc > 1){
        for (int i=1; i<argc; i++){
            check = arab2bin(argv[i]);
            if (check == 0){
                std::cerr << "Error" << std::endl;
                return 0;
            }
            std::cout << bin2rzym(check) << std::endl;
        }
    }
    return 0;
}
