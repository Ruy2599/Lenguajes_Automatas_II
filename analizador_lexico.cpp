#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stack>
 
using namespace std;
 
int es_PR(char buffer[]){
char palabras_reservadas[40][10] = {
	"begin", "bool", "break", "case", "catch", "char", "class", "const", 
	"decimal", "default", "do", "double", "else", "end", "false", "float", 
	"for", "foreach", "goto", "if", "int", "interface", "main","new", "null", 
	"object", "out", "print", "private", "protected", "public", "return",
	"static", "string", "switch", "this", "true", "try", "void", "while"
	};
	
int i, flag = 0;
for(i = 0; i < 40; ++i){
if(strcmp(palabras_reservadas[i], buffer) == 0){
flag = 1;
break;
}
}
return flag;
}

bool esNumero(char* str){
    int i, len = strlen(str),numero = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0 ; i < len ; i++)
    {
        if (numero > 1 && str[i] == '.')
        {
            return false;
        } else if (numero <= 1)
        {
            numero++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0)) 
        {
            return false;
        }
    }
    return true;
}

void PrintStack(stack<char> o){
	int i=0;
	if(!o.empty()){
		if(o.size() == 1){
			cout << o.top() << " ===> es un operador simple\n";
		}else{
			stack<char> temp;
			while(o.empty()==false){
				temp.push(o.top());
				o.pop();
			}
			while(temp.empty()==false){
				char t = temp.top();
				cout << t;
				temp.pop();
			}
		cout << " ===> es un operador compuesto\n";
		}
	}
}

 
int main(){
char ch, buffer[15], operadores[] = "+-*/%=<>^";
// bufferOp[3], 
char simbolos[] = "!@?;.,:_(){}[]";  
//char numeros[]="0123456789";

ifstream fin("hola_Lenguaje.txt");
int i, k,j=0;
stack<char> o;
int Bop;
if(!fin.is_open()){
cout<<"Error al abrir el archivo\n";
exit(0);
}


while(!fin.eof()){
   ch = fin.get();

//for(i = 0; i < 9; ++i){	
//   if(ch == operadores[i] && ch == operadores[i++]){
//   	cout<< ch <<" ===> es un operador compuesto\n";	
//	goto validacion;       	
//    	
//    }
//   else{   
//	for(i = 0; i < 9; ++i)
//    if(ch == operadores[i] &&  ch != operadores[++i] && ch != operadores[i++])
//    cout<<ch<<" ===> es un operador\n";
//}
//   }


validacion: 	

if(isalnum(ch)){
   buffer[j++] = ch;
   }
else if((ch == ' ' || ch == '\n') && (j != 0)){
   buffer[j] = '\0';
   j = 0;  
   
   
   if(esNumero(buffer))
        cout<<buffer<<" ===> es un numero\n";            
   if(es_PR(buffer) == 1)
   		cout<<buffer<<" ===> es una palabra reservada\n"; 	   						 
   if(esNumero(buffer) != 1  && es_PR(buffer) != 1 )
   		cout<<buffer<<" ===> es un identificador\n";    
   }  	

if(ch == '"')
   cout<<ch<<" ===> es un simbolo\n";

for(i = 0; i < 14; ++i){
   if(ch == simbolos[i])
   cout<<ch<<" ===> es un simbolo\n";
   }

	if(ch == '"' && es_PR(buffer) != 1)
   		cout<<buffer<<" ===> string\n";
	
	Bop =2 ;
	for(i = 0; i<9; ++i){
		if(ch == operadores[i]){
			o.push(ch);
			Bop = 1;
		}		
	}

	if (Bop == 2 && !o.empty()){
		PrintStack(o);
		for(k=0; k<=o.size(); k++){
			o.pop();
		}
	}
}
fin.close();
return 0;
}