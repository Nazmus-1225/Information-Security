#include<bits/stdc++.h>
#include<cstring>
#include<bitset>
#define ul unsigned long long int
using namespace std;

ul word[80];

ul k[80]=
        {0x428a2f98d728ae22, 0x7137449123ef65cd,
        0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
        0x3956c25bf348b538, 0x59f111f1b605d019,
        0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
        0xd807aa98a3030242, 0x12835b0145706fbe,
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
        0x9bdc06a725c71235, 0xc19bf174cf692694,
        0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
        0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
        0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210,
        0xb00327c898fb213f, 0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70,
        0x27b70a8546d22ffc, 0x2e1b21385c26c926,
        0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8,
        0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001,
        0xc24b8b70d0f89791, 0xc76c51a30654be30,
        0xd192e819d6ef5218, 0xd69906245565a910,
        0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
        0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc, 0x78a5636f43172f60,
        0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9,
        0xbef9a3f7b2c67915, 0xc67178f2e372532b,
        0xca273eceea26619c, 0xd186b8c721c0c207,
        0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
        0x06f067aa72176fba, 0x0a637dc5a2c898a6,
        0x113f9804bef90dae, 0x1b710b35131c471b,
        0x28db77f523047d84, 0x32caab7b40c72493,
        0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
        0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
        0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };

ul a=0x6A09E667F3BCC908;
ul b=0XBB67AE8584CAA73B;
ul c=0x3C6EF372FE94F82B;
ul d=0XA54FF53A5F1D36F1;
ul e=0x510E527FADE682D1;
ul f=0x9B05688C2B3E6C1F;
ul g=0x1F83D9ABFB41BD6B;
ul h=0x5BE0CD19137E2179;

ul res[8]={0x6A09E667F3BCC908,
0XBB67AE8584CAA73B,
0x3C6EF372FE94F82B,
0XA54FF53A5F1D36F1,
0x510E527FADE682D1,
0x9B05688C2B3E6C1F,
0x1F83D9ABFB41BD6B,
0x5BE0CD19137E2179};



ul rotate_right(ul x, int shift)  {return (x >> shift) | (x << (64 - shift));}
ul shift_right(ul x, int shift)   {return (x >> shift);}
ul maj(ul a, ul b, ul c) {return (a & b) ^ (b & c) ^ (c & a);}
ul Ch(ul e, ul f, ul g)  {return (e & f) ^ (~e & g);}
ul sigma_b(ul x)   {return rotate_right(x, 1)^ rotate_right(x, 8)^ shift_right(x, 7);}
ul sigma_a(ul x)   {return rotate_right(x, 19)^ rotate_right(x, 61)^ shift_right(x, 6);}
ul sigmaA(ul a)   {return rotate_right(a, 28)^ rotate_right(a, 34)^ rotate_right(a, 39);}
ul sigmaE(ul e)   {return rotate_right(e, 14)^ rotate_right(e, 18)^ rotate_right(e, 41);}
void Func(int round)
{
	// Find the Hash Code
	ul T1 = h + Ch(e, f, g) + sigmaE(e) + word[round] + k[round];
	ul T2 = sigmaA(a) + maj(a, b, c);

           h=g;
           g=f;
           f=e;
           e=d+T1;
           d=c;
           c=b;
           b=a;
           a=T1+T2;

}

string processing(string input,  int n){

    int i,j,padding=n-input.length()*8-128;
    stringstream ss;
for(i=0;i<input.length();i++){
        ss<<bitset<8>(input.at(i));
    }
string input1=ss.str();
input1+="1";
padding--;
for(i=0;i<padding;i++){
    input1+="0";
}
 string length=bitset<128>(input.length()*8).to_string();

 for(j=0;j<128;j++){
    input1+=length.at(j);
}

//cout<<input1;
return input1;
}


void wordGenerator(string text,int block){
    int i=block*1024;
    int j=i+1024;
    stringstream ss;
    for(;i<j;i++){
        ss<<text[i];
    }
    int k=0;
    i=block*1024;
    for(;i<j;i+=64,k++){
        string temp=text.substr(i,64);
        word[k]=bitset<64>(temp).to_ullong();
        //cout<<word[k]<<endl;
    }
    for(i=16;i<80;i++){
    word[i]=sigma_a(word[i-2])+word[i-7]+sigma_b(word[i-15])+word[i-16];
    //cout<<word[i]<<endl;}
    }}

    void SHA(){

    int i=0;
    for(i=0;i<80;i++){
        Func(i);}

    a+=res[0];
    b+=res[1];
    c+=res[2];
    d+=res[3];
    e+=res[4];
    f+=res[5];
    g+=res[6];
    h+=res[7];

    res[0]=a;
    res[1]=b;
    res[2]=c;
    res[3]=d;
    res[4]=e;
    res[5]=f;
    res[6]=g;
    res[7]=h;

    }

int main(){
string input;
getline(cin,input);
int i,n=input.length();

n=n*8;
n=n+128;
int blocks;
blocks=n/1024;
blocks++;
n=blocks*1024;
unsigned char pText[n];
input=processing(input,n);

for(i=0;i<blocks;i++){
wordGenerator(input,i);
SHA();}

for(i=0;i<8;i++){
printf("%llx",res[i]);}


}
