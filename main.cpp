  #include <iostream>
#include <fstream>

enum class Type
{
    Double,
    Int,
    String
};

union Values
{ 
    int integerV;
    char arr[50];
    double doubleV;
};

Type determineType(const std::string& str)
{ 
        int comma = 2;

        if (str != "")
        {
            for  (int i = 0; i < str.length(); ++i)
            {
                if (!(str[i] >= '0' && str[i] <= '9') && str[i] != ',')
                {   
                    return Type::String;
                } 

                if (str[i] == ',')
                {
                        --comma;
                }
            }

            if (comma <= 0)
            {   
                return Type::String;
            } 
            

            if (comma == 2)
            {
               return Type::Int;
            }

            if (comma ==  1)
            {
               return Type::Double;
            }
        }
        return Type::String;
}

int stringToInteger(const std::string& str)
{
    int value = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        value = value * 10 + (str[i] - '0');
    }
    
    return value;
}

double stringToDouble(const std::string& str)
{
    double result = 0.0;
    double sign = 1.0;
    int i = 0;

    if (str[i] == '-') {
        sign = -1.0;
        ++i;
    } else if (str[i] == '+') {
        ++i;
    }

    while (i < str.size() && std::isdigit(str[i])) {
        result = result * 10.0 + (str[i] - '0');
        ++i;
    }

    if (i < str.size() && str[i] == ',') {
        ++i;
        double fraction = 1.0;
        while (i < str.size() && std::isdigit(str[i])) {
            fraction *= 0.1;
            result += (str[i] - '0') * fraction;
            ++i;
        }
    }

    return result * sign;
}

void stringCopy(char* const ptr,const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        ptr[i] = str[i];
    }
    
}


void print(const Values& vals,const Type& type)
{
    switch (type)
    {
    case Type::Int:
        std::cout<<"Integer: "<< vals.integerV<<std::endl;
        break;

    case Type::Double:
        std::cout<<"Double: "<< vals.doubleV<<std::endl;
        break;

    case Type::String:
        std::cout<<"String: "<< vals.arr<<std::endl;
        break;
    }
}

void Data(const std::string& str)
{
    Type type = determineType(str);
    Values vals;

    switch (type)
    {
    case Type::Int:
        vals.integerV = stringToInteger(str);
        break;

    case Type::Double:
        vals.doubleV = stringToDouble(str);
        break;

    case Type::String:
        stringCopy(vals.arr,str);
        break;
    }
    print(vals,type);
}


int main()
{
    std::ifstream fin;

    std::string str;

    fin.open("TXT.txt");

    while(getline(fin,str))
    {
        Data(str);
    }
    
    fin.close();
    return 0;
}
