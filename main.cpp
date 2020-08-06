#include <fstream>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<string>

#include "KeyGen.h"

void ShowContentDebug (int contentLength, long int content[]) {
    for (int i=0; i<contentLength; i++) {
        cout<<content[i]<<",";
    }
    cout<<endl;
}

//Calculate bigger integer
long int EncryptDecrypt (long int t, long int EorD, long int n) {
    long int rem;
    long int x = 1;
    long int plain = t;
    int counter=0;
    if(plain>n){
        while(plain>n){
            counter++;
            plain=plain-n;
        }
        while (EorD != 0) {
            rem = EorD % 2;
            EorD = EorD / 2;

            if (rem == 1) {
                x = (x * t) % n;
            }

            t = (t * t) % n;
        }
        return x+(n*counter);
    }else{
        while (EorD != 0) {
            rem = EorD % 2;
            EorD = EorD / 2;

            if (rem == 1) {
                x = (x * t) % n;
            }

            t = (t * t) % n;
        }
        return x;
    }
}

long int EncryptInteger(long int c,long int e1, long int d1, long int n1,long int e2, long int d2, long int n2){

    //encrypt with Set 2 public key
    long int C_ = EncryptDecrypt(c, e1, n1); //set 1 public key encrypt
    //encrypt with Set 1 private key
    long int C = EncryptDecrypt(C_, d2, n2); //set 2 private key encrypt

    return C;
}

long int DecryptInteger(long int c,long int e1, long int d1, long int n1,long int e2, long int d2, long int n2){


    //follow lecture video
    //decrypt with Set 2 public key
    long int M_ = EncryptDecrypt(c, e2, n2);
    //decrypt with Set 1 private key
    long int M = EncryptDecrypt(M_, d1, n1);

/*
    //follow the question
    long int M_ = EncryptDecrypt(c, d2, n2);
    long int M = EncryptDecrypt(M_, e1, n1);
*/
    return M;
}

void EncryptString(long int e1, long int d1, long int n1, long int e2, long int d2, long int n2){
    fstream file;
    string content;

    //open content from text file
    file.open("PlainTextString.txt",ios::in);
    while(file>>noskipws>>content){
        cout << "\nFrom PlainText File: " << content;
    }
    file.close();
    cout << endl;


    int contentLength = content.length();
    cout<<"Plaintext length:"<<contentLength<<endl;
    long int converted[contentLength];
    long int C[contentLength];

    for(int i=0;i<contentLength;i++){
        converted[i] = (int)content[i];
        C[i] = EncryptInteger(converted[i],e1,d1,n1,e2,d2,n2);
        //cout<<"Converted: "<<converted[i]<<",";
        //cout<<"Encrypted: "<<C[i]<<",";
    }

    //print out the results
    cout<<"\nConverted: ";
    ShowContentDebug(contentLength,converted);
    cout<<"\nEncrypted: ";
    ShowContentDebug(contentLength,C);

    //write on another file
    file.open("EncryptedTextString.txt",ios::trunc|ios::out);
    for(int i=0;i<contentLength;i++){
        file<<C[i]<<",";
    }
    file.close();
}

void DecryptString(long int e1, long int d1, long int n1, long int e2, long int d2, long int n2){
    fstream file;
    char content[1000];
    long int M[1000];

    //read from the previous file
    file.open("EncryptedTextString.txt",ios::in);
    while(file>>noskipws>>content){
        cout << "\nFrom EncryptedTextString File: " << content;
    }
    file.close();
    cout << endl;

    char *token = strtok(content,",");
    long int contentArr[1000];

    int counter = 0;
    while (token != NULL){
        //cout<<token<<endl;
        contentArr[counter]=stoi(token);
        token = strtok(NULL,",");
        counter++;
    }

    for(int j=0;j<counter;j++){
        M[j] = DecryptInteger(contentArr[j],e1,d1,n1,e2,d2,n2);
    }

    cout<<"\nDecrypted(from integer):";
    ShowContentDebug(counter,M);

    cout<<"\nDecrypted Text:";
    for(int j=0;j<counter;j++){
        cout<<(char)M[j];
    }

    //Write to file
    file.open("DecryptedTextString.txt",ios::trunc|ios::out);
    for(int j=0;j<counter;j++){
        file<<(char)M[j];
    }
    file.close();
}

int main()
{
    cout << "RSA Experimental Version 0.1" <<endl;
    long int e1, d1, n1;
    cout << "Set 1" << endl;
    KeyGen(e1, d1, n1);
    cout << "Public Key: (" << e1 << "," << n1 << ")" << endl;
    cout << "Private Key: (" << d1 << "," << n1 << ")" << endl;

    long int e2, d2, n2;
    cout << "\nSet 2" << endl;
    KeyGen(e2, d2, n2);
    cout << "Public Key: (" << e2 << "," << n2 << ")" << endl;
    cout << "Private Key: (" << d2 << "," << n2 << ")" << endl;

    cout << "\n------------------------------------------";
    cout << "\nEncryption";
    EncryptString(e1,d1,n1,e2,d2,n2);

    cout << "\nPress any key to proceed to decryption.\n" <<endl;
    getch();

    cout << "------------------------------------------";
    cout << "\nDecryption";
    DecryptString(e1,d1,n1,e2,d2,n2);
    getch();

    return 0;
}
