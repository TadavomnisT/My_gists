// A very messy custom encryption algorithm that I wrote when I was a teen.
// The algorithm is a block cipher method
// Using example: 
// g++ encryption.cpp
// ./a.out -dec file.ext key

#include <iostream>
#include <fstream>
#include <vector>
#include "md5.cpp"
using namespace std; 

#define BUFFER_SIZE 1

void encrypt( string , string);
void decrypt( string , string);
string * hash_Key( string );
long filesize( string );
vector<string> str_split( string , int );
unsigned char hex2byte( string );

int main(int argc, char** argv) 
{ 

    string type = argv[1]; 
    string inputName = argv[2]; 
    string key = argv[3];
     
    if (type == "-enc" )
    {
        encrypt( inputName , key );
    }
    else if (type == "-dec" )
    {
        decrypt( inputName , key );
    }
    else
    {
        cout<<"ERROR type argument."<<endl;
    }

    return 0; 
} 


void encrypt(string inputName ,string key  )
{
    string * hashKey = hash_Key(key);
    int uniqueNumber = stoi(hashKey[1]);
    unsigned char uniqueNumber1 = hex2byte( hashKey[1] + to_string(0)) ;
    unsigned char uniqueNumber2 = hex2byte(to_string(0) + hashKey[1]) ;
    vector<string> keyHexes = str_split( hashKey[0] , 2 );
    vector<unsigned char> keyBytes1 , keyBytes2 ;
    for (int  i = 0; i <= 15; i++)
    keyBytes1.push_back( hex2byte( keyHexes[i] ) );
    for (int  i = 15; i >= 0; i--)
    keyBytes2.push_back( hex2byte( keyHexes[i] ) );
    int counter = 0 , percent = 0 , shiftCounter =  0;
    bool flag = false;
    int shiftLimit = key.length(); 
    fstream input (inputName, fstream::in);
    if ( input )
    {
        unsigned char buffer[BUFFER_SIZE];
        while (input.read((char *)buffer, BUFFER_SIZE))
        {   
            *buffer = *buffer ^ (flag? keyBytes2[ counter ]:keyBytes1[ counter ] );
            if(counter == uniqueNumber )*buffer = *buffer ^ (flag? uniqueNumber1 : uniqueNumber2 );
            if(flag) *buffer = ~ *buffer ;
            *buffer = flag? (*buffer<<(shiftCounter%8)) | (*buffer>>(8-shiftCounter%8)) :  (*buffer>>(shiftCounter%8)) | (*buffer<<(8-shiftCounter%8));
            flag = !flag;
            ++shiftCounter;
            ++counter;
            if(counter > 15) counter = 0;
            if(shiftCounter > shiftLimit) shiftCounter = 0;
            cout << buffer[0];
        }
        input.close();
    }
    else
    {
        cout<< "Error while opening files. "<<endl;
        cerr << "Error: " << strerror(errno);
    }
}

void decrypt(string inputName ,string key  )
{
    string * hashKey = hash_Key(key);
    int uniqueNumber = stoi(hashKey[1]);
    unsigned char uniqueNumber1 = hex2byte( hashKey[1] + to_string(0)) ;
    unsigned char uniqueNumber2 = hex2byte(to_string(0) + hashKey[1]) ;
    vector<string> keyHexes = str_split( hashKey[0] , 2 );
    vector<unsigned char> keyBytes1 , keyBytes2 ;
    for (int  i = 0; i <= 15; i++)
    keyBytes1.push_back( hex2byte( keyHexes[i] ) );
    for (int  i = 15; i >= 0; i--)
    keyBytes2.push_back( hex2byte( keyHexes[i] ) );
    int counter = 0 , percent = 0 , shiftCounter =  0;
    bool flag = false;
    int shiftLimit = key.length(); 
    fstream input (inputName, fstream::in);
    if ( input )
    {
        unsigned char buffer[BUFFER_SIZE];
        while (input.read((char *)buffer, BUFFER_SIZE))
        {   
            *buffer = flag? (*buffer>>(shiftCounter%8)) | (*buffer<<(8-shiftCounter%8)) :  (*buffer<<(shiftCounter%8)) | (*buffer>>(8-shiftCounter%8));
            if(flag) *buffer = ~ *buffer ;
            if(counter == uniqueNumber )*buffer = *buffer ^ (flag? uniqueNumber1 : uniqueNumber2 );
            *buffer = *buffer ^ (flag? keyBytes2[ counter ]:keyBytes1[ counter ] );
            flag = !flag;
            ++shiftCounter;
            ++counter;
            if(counter > 15) counter = 0;
            if(shiftCounter > shiftLimit) shiftCounter = 0;
            cout << buffer[0];
        }
        input.close();
    }
    else
    {
        cout<< "Error while opening files. "<<endl;
        cerr << "Error: " << strerror(errno);
    }
}

string * hash_Key(string key)
{
    int uniqueNumber = 0 ;
    string tempKey;
    for (int i=0; i < key.length() ; i++)uniqueNumber += (int) key[i] ;
    while (uniqueNumber >= 10) {
        tempKey = to_string(uniqueNumber);
        uniqueNumber = 0;
        for (int i=0; i < tempKey.length() ; i++)
        {
            uniqueNumber += (((int) tempKey[i]) - 48);
        }
    }
    static string result[] = {
        md5(key) , 
        to_string(uniqueNumber)
    }; 
    return result;
}

long filesize(string filename)
{
    long size;
    FILE * pFile = fopen ( filename.c_str(),"rb");
    if (pFile==NULL) perror ("Error opening file");
    else
    {
        fseek (pFile, 0, SEEK_END);   // non-portable
        size=ftell (pFile);
        fclose (pFile);
        return size;
    }
    return false;
}

vector<string> str_split(string str, int splitLength)
{
   int NumSubstrings = str.length() / splitLength;
   vector<string> ret;
   for (auto i = 0; i < NumSubstrings; i++)
   {
        ret.push_back(str.substr(i * splitLength, splitLength));
   }
   if (str.length() % splitLength != 0)
   {
        ret.push_back(str.substr(splitLength * NumSubstrings));
   }
   return ret;
}


unsigned char hex2byte( string s)
{
    return
    (((s[0] >= 'A' && s[0] <= 'Z') ? (10 + s[0] - 'A') : 
    (s[0] >= 'a' && s[0] <= 'z') ? (10 + s[0] - 'a') : 
    (s[0] >= '0' && s[0] <= '9') ? (s[0] - '0') : 0) << 4) |
    ((s[1] >= 'A' && s[1] <= 'Z') ? (10 + s[1] - 'A') : 
    (s[1] >= 'a' && s[1] <= 'z') ? (10 + s[1] - 'a') : 
    (s[1] >= '0' && s[1] <= '9') ? (s[1] - '0') : 0);
}
