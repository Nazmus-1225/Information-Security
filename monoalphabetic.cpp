#include<bits/stdc++.h>
using namespace std;

void Encrypt(int key,string text){
    int i;
    char output[1000];
    char t;
    int length=text.length();

    for(i=0;i<length;i++){
        t=text.at(i);
        if(t>96&&t<123){t+=key;
            if(t>122){t-=26;}}
        else if(t>64&&t<91){t+=key;
            if(t>90){t-=26;}}
        output[i]=t;}

        output[length]='\0';
        string encrypted(output);
        cout<<encrypted;
}

void Decrypt(int key,string text){
    int i;
    char output[1000];
    char t;
    int length=text.length();

    for(i=0;i<length;i++){
        t=text.at(i);
        if(t>96&&t<123){t-=key;
            if(t<97){t+=26;}}
        else if(t>64&&t<91){t-=key;
            if(t<65){t+=26;}}
        output[i]=t;}

        output[length]='\0';
        string decrypted(output);
        cout<<decrypted;
}

int main(){
    int i,j,t,key;
    string text;

    cout<<"1.Encrypt or 2.Decrypt"<<endl;
    cin>>t;

    cout<<"Key: ";
    cin>>key;

    cout<<"Text: ";
    cin>>text;

    if(t==1){Encrypt(key,text);}
    else if (t==2){Decrypt(key,text);}

    return 0;
}
