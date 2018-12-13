//Umer Farooq 
//BCSF15M025	
//Hamza Sadiq 
//BCSF15M008

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include <string.h>
#include<ctype.h>

using namespace std;
int c_s, f, l_s, i_w_l_f_s_v, l_f_s_v, line_no;
string buffer="";
string lexeme="";
bool IsLexemeIdentified(){
	if(l_f_s_v>0)
		return true;
    else
        return false;
}

void extractAndStoreLexeme(){
	lexeme=buffer.substr(l_s,(i_w_l_f_s_v-l_s)+1);
	if(lexeme=="for" || lexeme=="int"){
		cout<<lexeme<<" is a Keyword"<<endl;
	}
	else if(lexeme=="=" || lexeme==";"){
		cout<<lexeme<<" is "<< lexeme<<endl;
	}
	else if(strstr(lexeme.c_str(),".")){
		cout<<lexeme<<" is Real"<<endl;
	}
	else{
		cout<<lexeme<<" is an Identifier"<<endl;
	}
    lexeme = "";
}
void ungetch(){
	f--;
	if(IsLexemeIdentified()){
		extractAndStoreLexeme();
		c_s=0;
		l_f_s_v=-1;
		l_s=i_w_l_f_s_v+1;
	}
}
void errorDetected(char errChar){
	ungetch();
	cout<<"Invalid character "<<errChar<<" at line "<<line_no<<endl;
	f++;
	l_s++;
	//i_w_l_f_s_v=f-1;
}
int main(){
	c_s=0;
	f=0;
	l_s=0;
	i_w_l_f_s_v=-1;
	l_f_s_v=-1;
	line_no=1;
	ifstream infile;
	infile.open("buffer.txt", ios::in);
	char a;

	while(!infile.eof()){
		buffer+=infile.get();;
	}
	buffer[buffer.length() - 1] = '\0';
	while (buffer[f]){
		a=buffer[f];
		f++;
		if((a>='a'&& a<='z') || a=='_' )
		{
			c_s=2;
			l_f_s_v=c_s;
			i_w_l_f_s_v = f - 1;
			while(buffer[f]){
				a=buffer[f];
				f++;
				if((a>='a'&& a<='z') || a=='_' || (a>='0'&& a<='9')){
					i_w_l_f_s_v=f-1;
				}else{
					ungetch();
					break;
				}
			}
		}
		else if(a=='\n' || a=='\r' || a=='\t' || a=='\b' || a==' '){
			l_s=f;
			if(a=='\n' || a=='\r'){
				line_no++;
			}
		}
		else if(a=='='){
			c_s=1;
			l_f_s_v=c_s;
			i_w_l_f_s_v=f-1;
			extractAndStoreLexeme();
		}
		else if(a==';'){
			c_s=6;
			l_f_s_v=c_s;
			i_w_l_f_s_v=f-1;
			extractAndStoreLexeme();
		}
		else if(a>='0'&& a<='9'){
			c_s=3;
			l_f_s_v=c_s;
			i_w_l_f_s_v = f - 1;
			while(buffer[f]!=0){
				a=buffer[f];
				f++;
				if(a>='0'&& a<='9'){
					i_w_l_f_s_v=f-1;
				}
				else if(a=='.'){
					c_s=4;
					i_w_l_f_s_v=f-1;
					while(buffer[f]){
						a=buffer[f];
						f++;
						if(a>='0'&& a<='9'){
							c_s=5;
							l_f_s_v=c_s;
							i_w_l_f_s_v=f-1;
						}
						else{
							ungetch();
							break;
						}
					}
				}
				else{
					ungetch();
					break;
				}
			}
		}
		else {
			errorDetected(a);
		}

	}

}
