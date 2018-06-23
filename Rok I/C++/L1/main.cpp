#include<iostream>
#include<string.h>
#include <cmath>

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

std::string bin2rzym (int x){
    std::string roman = "";
    if (x <= 3999){
        int i = 0;
        while (x > 0){
            if (x >= B[i]){
                roman += R[i];
                x -= B[i];
            }
            else{
                i++;
            }
        }
    }
    else{
        int l = floor(x / 100);
        int rest = x - (l * 100);
        roman = "|"+ bin2rzym(l) + "|" + bin2rzym(rest);
    }
    return roman;
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
