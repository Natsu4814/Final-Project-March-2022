#include "header.h"

class My_String : std::string
{

    int count = 1;
    std::string* strs;
public:
    std::string* tok(std::string str ,char delim)
    {
        int len_of_str = str.length();
        int len_of_part = 0;
        int start_of_for = 0;
        for (int i = 0; i < len_of_str; i++)
        {
            if (str[i] == delim)
                count += 1;
        }
        strs = new std::string[count];


        do
        {
            len_of_part++;
        } while (str[len_of_part] != delim);


        for(int q = 0; q < count;q++)
        { 

            for (int i = start_of_for; i < start_of_for + len_of_part; i++)
            {
                strs[q] += str[i];
            }
            start_of_for = start_of_for + len_of_part + 1;
            len_of_part = 0;
            for (int i = start_of_for; i < len_of_str; i++)
            {
                if (str[i] != delim)
                    len_of_part++;
                else if(str[i] == delim) break;
            }
        }

        return strs;
    }

    std::string* return_strs()
    {
        return strs;
    }

    void print()
    {
        for (int i = 0; i < count; i++)
            std::cout << strs[i] << " ";
    }
    
    ~My_String()
    {
        delete[] strs;
    }
};