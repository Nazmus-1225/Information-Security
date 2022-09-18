#include<bits/stdc++.h>
using namespace std;

void Encrypt(string text){
    int i;
    char output[1000];
    char t;
    int length=text.length();

    for(i=0;i<length;i++){
        t=text.at(i);
        if(t>96&&t<123){t+=i;
            if(t>122){t-=26;}}
        else if(t>64&&t<91){t+=i;
            if(t>90){t-=26;}}
        output[i]=t;}

        output[length]='\0';
        string encrypted(output);
        cout<<encrypted;
}

void Decrypt(string text){
    int i;
    char output[1000];
    char t;
    int length=text.length();

    for(i=0;i<length;i++){
        t=text.at(i);
        if(t>96&&t<123){t-=i;
            if(t<97){t+=26;}}
        else if(t>64&&t<91){t-=i;
            if(t<65){t+=26;}}
        output[i]=t;}

        output[length]='\0';
        string decrypted(output);
        cout<<decrypted;
}

int main(){
    int i,j,t;
    string text;

    cout<<"1.Encrypt or 2.Decrypt"<<endl;
    cin>>t;

    cout<<"Text: ";
    cin>>text;

    if(t==1){Encrypt(text);}
    else if (t==2){Decrypt(text);}

    return 0;
}


