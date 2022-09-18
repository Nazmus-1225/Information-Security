#include<bits/stdc++.h>
using namespace std;
#define ul uint8_t
#define vul vector<ul>
#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))
#define pb push_back
uint8_t sbox[256];
const int GLFM=283;
uint16_t rc=1;
int ind=1;
const uint8_t cMat[4][4]={ {2,3,1,1}, {1,2,3,1}, {1,1,2,3}, {3,1,1,2}};
const uint8_t rcon[11] =
 {
    0x00000000,
    0x00000001,
    0x00000002,
    0x00000004,
    0x00000008,
    0x00000010,
    0x00000020,
    0x00000040,
    0x00000080,
    0x0000001B,
    0x00000036
 };
 string toHex(ul num){
    unordered_map<int, string> mp;
    mp[0] = "0";
    mp[1] = "1";
    mp[2] = "2";
    mp[3] = "3";
    mp[4] = "4";
    mp[5] = "5";
    mp[6] = "6";
    mp[7] = "7";
    mp[8] = "8";
    mp[9] = "9";
    mp[10] = "A";
    mp[11] = "B";
    mp[12] = "C";
    mp[13] = "D";
    mp[14] = "E";
    mp[15] = "F";
    ul left=num>>4;
    ul ft=15;
    ul right=num & ft;
    string retS=mp[(int)left];
    retS+=mp[(int)right];
    return retS;
}

void circular_shift(vul &tempWord,int shift){


	for(int i=0;i<shift;i++){
		ul tmp=tempWord[0];
		for(int j=0;j<3;j++){
			tempWord[j]=tempWord[j+1];
		}
		tempWord[3]=tmp;
	}
	//for(int i=0;i<4;i++)
	//if(tempWord[i]>=256)cout<<tempWord[i]<<endl;
}

void rcAdd(vul &tempWord){
	ul temp;
	temp=tempWord[0];
	(temp^=rcon[ind]);
	ind++;
	//if(temp>=256)temp^=GLFM;
	tempWord[0]=temp;
	//rc<<=1;
	/*if(rc>=256){
		rc^=GLFM;
	}
	for(int i=0;i<4;i++);
	//if(tempWord[i]>=256)cout<<tempWord[i]<<endl;*/
}
void fieldAdd(vul &word1, vul &word2, vul &wordF){

	for(int i=0;i<4;i++){
		wordF[i]=word1[i]^word2[i];
		if(wordF[i]>=256)wordF[i]^=283;
	}

}


void box() {
	uint8_t p = 1, q = 1;

	/* loop invariant: p * q == 1 in the Galois field */
	do {
		/* multiply p by 3 */
		p = p ^ (p << 1) ^ (p & 0x80 ? 0x11B : 0);

		/* divide q by 3 (equals multiplication by 0xf6) */
		q ^= q << 1;
		q ^= q << 2;
		q ^= q << 4;
		q ^= q & 0x80 ? 0x09 : 0;

		/* compute the affine transformation */
		uint8_t xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);

		sbox[p] = xformed ^ 0x63;
	} while (p != 1);

	/* 0 is a special case since it has no inverse */
	sbox[0] = 0x63;
}

void substituteK(vul &tempWord){
	for(int i=0;i<4;i++){

		tempWord[i]=(ul)sbox[tempWord[i]];
		if(tempWord[i]>=256)cout<<tempWord[i]<<endl;
	}
}

void toMatrix(string &input, vector<vul> &iMat){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			iMat[j][i]=input[4*i+j];
		}
	}
}

void keyScheduling(string &key, vul &keyVector){
	int size=0;
	for(int i=0;i<44;i++){
		if(i<4){
			for(int j=0;j<key.size();j++){
				keyVector.pb(key[j]);
			}
			size=16;
			i=3;
		}
		else if(i%4==0){
			vul wi_1;
			vul wi_4;
			for(int j=4;j>=1;j--){
				wi_1.pb(keyVector[size-j]);
				wi_4.pb(keyVector[size-12-j]);
			}
			circular_shift(wi_1,1);
			//for(auto x:wi_1)cout<<toHex(x)<<" ";
			//cout<<endl;
			substituteK(wi_1);
			//for(auto x:wi_1)cout<<toHex(x)<<" ";
			//cout<<endl;
			rcAdd(wi_1);
			vul w_f(4);
			//for(auto x:wi_1)cout<<toHex(x)<<" ";
			fieldAdd(wi_1,wi_4,w_f);
			for(int j=0;j<4;j++){
				//cout<<w_f[j]<<endl;
				keyVector.pb(w_f[j]);
			}
			//cout<<endl;
			/*for(auto x:w_f)cout<<toHex(x)<<" ";
			cout<<endl;
			for(auto x:w_f)cout<<(x)<<" ";
			cout<<endl;*/

			size+=4;
		}
		else{
			vul wi_1;
			vul wi_4;
			for(int j=4;j>=1;j--){
				wi_1.pb(keyVector[size-j]);
				wi_4.pb(keyVector[size-12-j]);
			}
			//circular_shift(wi_1);
			//substituteK(wi_1);
			//rcAdd(wi_1);
			vul w_f(4);
			fieldAdd(wi_1,wi_4,w_f);
			for(int j=0;j<4;j++){
				keyVector.pb(w_f[j]);
			}
			size+=4;
		}
	}
	/*for(int i=0;i<176;i++){
		cout<<toHex(keyVector[i])<<" ";
		//cout<<keyVector[i]<<" ";
	}
	cout<<endl;*/

}
void matXor(vector<vul> &iMat, vector<vul> &kMat, vector<vul> &stateMat){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			stateMat[i][j]= iMat[i][j] ^ kMat[i][j];
		}
	}
}
void wordMatgenerator(int offset, vul &words, vector<vul> &kMat){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			kMat[j][i]=words[offset+4*i+j];
		}
	}
}
void subBytes(vector<vul> &stateMat){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			stateMat[i][j]=sbox[stateMat[i][j]];
		}
	}
}

void rowShift(vector<vul> &stateMat){
	/*for(int i=0;i<4;i++){
		for(int k=0;k<i;k++){
			ul tmp=stateMat[0][i];
			for(int j=0;j<3;j++){
				stateMat[j][i]=stateMat[j+1][i];
			}
			stateMat[3][i]=tmp;
		}
	}*/
	int i=0;
	for(auto &x:stateMat){
		circular_shift(x,i++);
	}
}

ul gmul(ul a, ul b) {
	ul res = 0;
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
void mixColumn(vector<vul> &stateMat){
	vector<vul> res(4,vul(4));
	ul temp;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			ul temp=0;
			for(int k=0;k<4;k++){
				temp^=gmul(cMat[i][k],stateMat[k][j]);
				if(temp>=256)temp^=283;

			}
			res[i][j]=temp;

		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			stateMat[i][j]=res[i][j];
		}

	}
}
void addKey(vector<vul>&stateMat,vector<vul> &kMat){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			stateMat[i][j]^=kMat[i][j];
		}
	}
}
void print(vector<vul> iMat,
	vector<vul> kMat,vector<vul> stateMat){

	cout<<endl;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cout<<toHex(kMat[i][j])<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cout<<toHex(stateMat[i][j])<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void rounds(vul &words,vector<vul> &iMat,vector<vul> &cipherMat){
	vector<vul> stateMat(4,vul(4));
	vector<vul> kMat(4,vul(4));
	int offset=0;
	wordMatgenerator(offset,words,kMat);
	matXor(iMat,kMat,stateMat);
	offset=16;
	for(;offset<176;offset+=16){

			subBytes(stateMat);
			/*print(iMat,kMat,stateMat);
			cout<<"----";*/
			rowShift(stateMat);
			/*print(iMat,kMat,stateMat);
			cout<<"----";*/
		if(offset<160){
			mixColumn(stateMat);
			/*print(iMat,kMat,stateMat);
			cout<<"----";*/
		}
		wordMatgenerator(offset,words,kMat);
		addKey(stateMat,kMat);
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cipherMat[i][j]=stateMat[i][j];
		}
	}
}
void init(){
	box();
	vector<vul> iMat(4,vul(4));
	vul keyVector;
	string input="Two One Nine Two";
	string key= "Thats my Kung Fu";

	toMatrix(input,iMat);
	keyScheduling(key,keyVector);
	int roundno=0;

	cout<<endl;
	vector<vul> cipherMat(4,vul(4));
	rounds(keyVector,iMat,cipherMat);
	cout<<"input string: "<<input<<endl;
	cout<<"key: "<<key<<endl;
	cout<<"input in hexadecimal: ";
	for(int i=0;i<input.size();i++){
		cout<<toHex((int)input[i])<<" ";
	}
	cout<<endl;
	cout<<"Ciphertext: ";
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cout<<toHex(cipherMat[j][i])<<" ";
		}
	}

	cout<<endl;
		cout<<"Keys:\n";
	for(int i=0;i<keyVector.size();i++){

		if(i%16==0)cout<<"Round "<<roundno++<<": ";
		cout<<toHex(keyVector[i])<<" ";
		if(i%16==15)cout<<endl;

	}
}

int main(){
	init();
}

