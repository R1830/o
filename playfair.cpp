#include <bits/stdc++.h>
#define SIZE 30
using namespace std;

//function to convert text into lower case
void tolowercase(char text[], int l)
{
    int i;
    for(i=0; i<l; i++)
        if(text[i]>64 && text[i]<91)
            text[i] += 32;
}

//function to remove spaces
int removespaces(char* text,int l)
{
    int i, count = 0;
    for(i=0; i<l; i++)
    {
        if(text[i] != ' ')
            text[count++] = text[i];
    }
    text[count] = '\0';

    return count;
}

//function to make text even
int prepare(char text[], int ptr)
{
    if(ptr % 2 != 0)
    {
        text[ptr++] = 'x';
        text[ptr] = '\0';
    }

    return ptr;
}

//function to create key matrix
void keytable(char key[], int kl, char matrix[5][5])
{
    int i, j, k;

    //a 26 character hashmap
    // to store count of the alphabet

    int dict[26] = {0};
    for(i=0; i<kl; i++)
    {
        if(key[i] != 'j')
        {
           dict[key[i] - 97] = 2;
        }

    }
    dict['j' - 97] = 1;

    i=0;
    j=0;

    for(k=0; k < kl; k++)
    {
        if(dict[key[k] - 97] == 2)
        {
           dict[key[k] - 97] -= 1;
            matrix[i][j] = key[k];
            j++;
            if(j==5)
            {
                i++;
                j=0;
            }
        }

    }
    for(k=0; k<26; k++)
    {
        if(dict[k]==0)
        {
            matrix[i][j] = char(k+97);
            j++;
            if(j==5)
            {
               i++;
                j=0;
            }

        }

    }
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<"\n";
    }
}
//function to find modulus with 5
int mod5(int a){return (a%5); }

// Function to search for the characters of a digraph
// in the key square and return their position
void searchkey(char matrix[5][5], char a, char b, int arr[])
{
    int i,j;
    if(a == 'j')
        a = 'i';
    else if(b == 'j')
        b = 'i';

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(matrix[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (matrix[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}
//function to encrypt the plain text
void encrypt(char str[], char matrix[5][5], int pl)
{
    int i, a[4];

    for(i=0; i<pl; i+=2)
    {
        searchkey(matrix, str[i], str[i+1], a);

        if(a[0]==a[2])
        {
            str[i] = matrix[a[0]][mod5(a[1] + 1)];
            str[i+1] = matrix[a[0]][mod5(a[3] + 1)];
        }
        else if(a[1]==a[3])
        {
            str[i] = matrix[mod5(a[0]+1)][a[1]];
            str[i+1] = matrix[mod5(a[2]+1)][a[1]];
        }
        else
        {
            str[i] = matrix[a[0]][a[3]];
            str[i+1] = matrix[a[2]][a[1]];
        }
    }
}
//function for play fair cipher
void playfair(char text[], char key[])
{
        char kl, pl, matrix[5][5];

        pl = strlen(text);
        tolowercase(text, pl);
        pl = removespaces(text, pl);

        kl = strlen(key);
        tolowercase(key, kl);
        kl = removespaces(key, kl);

        pl = prepare(text, pl);

        keytable(key, kl, matrix);

        encrypt(text, matrix, pl);

}
// Function to find the modulus with 5
int mod(int a)
{
    if (a < 0)
        a += 5;
    return (a % 5);
}

//function to decrypt
void decrypt(char str[], char keyT[5][5], int ps)
{
    int i, a[4];
    for (i = 0; i < ps; i += 2) {
        searchkey(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod(a[1] - 1)];
            str[i + 1] = keyT[a[0]][mod(a[3] - 1)];
        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod(a[0] - 1)][a[1]];
            str[i + 1] = keyT[mod(a[2] - 1)][a[1]];
        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

//function to call decrypt
void decryptByPlayfairCipher(char str[], char key[])
{
    char ps, ks, keyT[5][5];

    // Key
    ks = strlen(key);
    ks = removespaces(key, ks);
    tolowercase(key, ks);

    // ciphertext
    ps = strlen(str);
    tolowercase(str, ps);
    ps = removespaces(str, ps);

    keytable(key, ks, keyT);

    decrypt(str, keyT, ps);
}
int main()
{
    int ch;
    char plain_text[SIZE], key[SIZE],cipher_text[SIZE];
    cout<<"******************** PLAY-FAIR CIPHER ***********************"<<endl;
    do
    {
        cout<<"\n\nSELECT THE OPTION:";
        cout<<"\n1.ENCRYPTION\n2.DECRYPTION\n3.EXIT\n";
        cin>>ch;
        switch(ch)
        {
        case 1:
            cout<<"ENTER THE PLAIN TEXT: \n";
            cin>>plain_text;
            cout<<"\nENTER THE KEY: \n";
            cin>>key;
            cout<<"\nYOUR TEXT IS: "<<plain_text<<endl;

            playfair(plain_text,key);

            cout<<"\nCIPHER TEXT: "<< plain_text<<"\n";
            break;
        case 2:
            cout<<"ENTER THE CIPHER TEXT: \n";
            cin>>cipher_text;
            cout<<"\nENTER THE KEY: \n";
            cin>>key;
            cout<<"\nTHE CIPHER TEXT IS: "<<plain_text<<endl;

            decryptByPlayfairCipher(cipher_text, key);

            cout<<"\nTHE PLAIN TEXT IS: "<< cipher_text;
            break;
        case 3:
            exit(0);
        default:


            cout<<"\nENTER CORRECT OPTION!!!!!!";
        }
    }while(1);

    return 0;
}

