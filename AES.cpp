#include<bits/stdc++.h>
#include<cstring>
using namespace std;

unsigned char state[4][4];
unsigned char gResult[4];
unsigned char mcMatrix[4][4]={{0x02,0x03,0x01,0x01},{0x01,0x02,0x03,0x01},{0x01,0x01,0x02,0x03},{0x03,0x01,0x01,0x02}};
unsigned char expanded_key[44][4];
unsigned char roundConstants[]={0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x080,0x1B,0x36};
string plainText,key,cipherText;
unsigned char sbox[16][16]={{0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
                            {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
                            {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
                            {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
                            {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
                            {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
                            {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
                            {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
                            {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
                            {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
                            {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
                            {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
                            {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
                            {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
                            {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
                            {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}};


void padding(unsigned char* pText,int n){
    int i=0;
    for(;i<plainText.length();i++){
        pText[i]=plainText.at(i);
    }
    if(n!=plainText.length()){
            i=plainText.length();
            pText[i]=0x80;
            i++;
            for(;i<n;i++){
                pText[i]=0x00;
            }}

}

void blockToState(unsigned char* pText,int block){
    int i=block*16;
    int j=i+16;
    int k=0,l=0;

        for(;k<4;k++){
            for(l=0;l<4;l++){
                state[l][k]=pText[i];
                i++;}}

}


void keyToBox(string x){
    int i,j,k=0;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){{
                expanded_key[i][j]=x.at(k);
                k++;
            }
        }}}

unsigned char galoisMultiply(unsigned char a, unsigned char b) {
	unsigned char res = 0;
	while (a && b) {
            if (b & 1==1){
                res ^= a;
                }
            if (a & 0x80){
                a = (a << 1) ^ 283;
                }
            else{
                a <<= 1;
		}
            b >>= 1;

	}
	return res;
}


void keyLeftCircularShift(int round){
    unsigned char temp;
    int row=round*4-1;
    int i;
    temp=expanded_key[row][0];
    for(i=1;i<4;i++){gResult[i-1]=expanded_key[row][i];}
    gResult[3]=temp;

}

void stateLeftCircularShift(int row){
    unsigned char temp;
    int i;
    temp=state[row][0];
    for(i=1;i<4;i++){state[row][i-1]=state[row][i];}
    state[row][3]=temp;

}

void substitueBytes(int round){
    int i,row,column;
    row=round*4-1;
    for(i=0;i<4;i++){
        row=gResult[i]/16;
        column=gResult[i]%16;
        gResult[i]=sbox[row][column];
    }
}

void addRC(int round){
    int row=round*4-1;
    gResult[0]=gResult[0]^roundConstants[round];
    if(gResult[0]>=256)
        gResult[0]=gResult[0]^283;
    }

void gFunc(int round){
    keyLeftCircularShift(round);
    substitueBytes(round);
    addRC(round);

}

void substitueBox(){
    int i,row,column,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            row=state[i][j]/16;
            column=state[i][j]%16;
            state[i][j]=sbox[row][column];
    }
}}

void shiftRow(){
    int i,j;
    for(i=1;i<4;i++){
        for(j=0;j<i;j++){
            stateLeftCircularShift(i);
        }
    }}

void mixColumn(){
    int i,j,k;
    unsigned char temp[4][4];
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            temp[i][j]=0x00;
        }
    }

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
                for(k=0;k<4;k++){
                    temp[i][j]=temp[i][j]^galoisMultiply(mcMatrix[i][k],state[k][j]);

                    if(temp[i][j]>=256)
                        temp[i][j]=temp[i][j]^283;
        }
       }
    }

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            state[i][j]=temp[i][j];
        }
    }}


void addRoundKey(int round){
    int i,j,k,r=0;
    i=round*4;
    k=(round+1)*4;

    for(;i<k;i++){
        for(j=0;j<4;j++){
            state[r][j]=state[r][j]^expanded_key[i][j];
        }
        r++;}}

void transposeKey(){
    int i,j,k,r,c,round=0;
    unsigned char temp[4][4];

    for(;round<=10;round++){
        r=0;
        i=round*4;
        k=i+4;

        for(;i<k;i++){
            for(j=0;j<4;j++){
                temp[r][j]=expanded_key[i][j];}
        r++;}

        i=round*4;
        k=i+4;

        for(;i<k;i++){
            r=i%4;
            for(j=0;j<4;j++){
                c=j;
                expanded_key[i][j]=temp[c][r];
}}
    }

}

void keyExpansion(){
    int round=1,i,j,k,t;

    for(;round<=10;round++){
        i=round*4;
        k=(round+1)*4;
        gFunc(round);

        for(;i<k;i++){
            if(i%4==0){
                for(j=0;j<4;j++){
                expanded_key[i][j]=expanded_key[i-4][j]^gResult[j];}}

            else for(j=0;j<4;j++){
                expanded_key[i][j]=expanded_key[i-1][j]^expanded_key[i-4][j];}
        }
    }
    transposeKey();
}



void Encryption(unsigned char* cText,int block){
    int round=0,i,j,k,l;

    for(;round<=10;round++){
        if(round==0){
            addRoundKey(round);}
        else if(round==10){
            substitueBox();
            shiftRow();
            addRoundKey(round);}
        else
            {substitueBox();
            shiftRow();
            mixColumn();
            addRoundKey(round);}}

    i=block*16;
    j=i+16;
    k=0;

        for(;k<4;k++){
            for(l=0;l<4;l++){
                    cText[i]=state[l][k];
            i++;
            }}

}


void print(unsigned char* cText,int n){
     int i,j;
     cout<<"KEYS"<<endl;
    for(i=0;i<44;i++){
        if(i%4==0){cout<<"Round "<<i/4<<endl;}
            for(j=0;j<4;j++)
                printf("%X  ",expanded_key[i][j]);
    cout<<endl;
    if(i%4==3){cout<<endl;}}

   cout<<endl<<"Plain Text:"<<endl;
   for(i=0;i<plainText.length();i++){
                printf("%X  ",plainText.at(i));}
    cout<<endl<<"Cipher Text:"<<endl;
    for(i=0;i<n;i++){
                printf("%X  ",cText[i]);}}




int main(){

plainText="Two One Nine Two";
key="Thats my Kung Fu";

int i,j,n=plainText.length();
if(n%16!=0){
    n=n/16;
    n++;
    n=n*16;
}
keyToBox(key);
keyExpansion();

unsigned char pText[n];
unsigned char cText[n];
padding(pText,n);



    int block=n/16;

    for(i=0;i<block;i++){
    blockToState(pText,i);
   Encryption(cText,i);}
   print(cText,n);

return 0;

}
