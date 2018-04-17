
#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctype.h>
#include <cctype>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <bitset>

#define SIZE 100

using namespace std;
char line[SIZE];

vector <vector <string> > vec;
static string num_t[ 100 ];
static string sym_t[ 100 ];
static string mess_t[ 100 ];

static fstream fout;

struct ctable{
  string name ;
  string set ;
};

struct regtable{
  string name ;
  int set ;
};

struct pass1{
  int loc;
};

struct xepass1{
  int loc;
};

struct symbol_table{
  string label;
  int loc;
};

struct xesymbol_table{
  string label;
  int loc;
};

struct ctable ct[100];
struct regtable rt[7];
struct pass1 pass1[100];
struct xepass1 xepass1[100];
struct symbol_table sym_table[100];
struct xesymbol_table xesym_table[100];

void setregtable(){
  rt[0].name = "A"; rt[0].set = 0;
  rt[1].name = "X"; rt[1].set = 1;
  rt[2].name = "L"; rt[2].set = 2;
  rt[3].name = "B"; rt[3].set = 3;
  rt[4].name = "S"; rt[4].set = 4;
  rt[5].name = "T"; rt[5].set = 5;
  rt[6].name = "F"; rt[6].set = 6;
}

void settable(){
  ct[0].name = "ADD";		ct[0].set = "18";
  ct[1].name = "ADDF";		ct[1].set = "58";
  ct[2].name = "ADDR";		ct[2].set = "90";
  ct[3].name = "AND";		ct[3].set = "40";
  ct[4].name = "CLEAR";		ct[4].set = "B4";
  ct[5].name = "COMP";		ct[5].set = "28";
  ct[6].name = "COMPF";		ct[6].set = "88";
  ct[7].name = "COMPR";		ct[7].set = "A0";
  ct[8].name = "DIV";		ct[8].set = "24";
  ct[9].name = "DIVF";		ct[9].set = "64";
  ct[10].name = "DIVR";		ct[10].set = "9C";
  ct[11].name = "FIX";		ct[11].set = "C4";
  ct[12].name = "FLOAT";	ct[12].set = "C0";
  ct[13].name = "HIO";		ct[13].set = "F4";
  ct[14].name = "J";		ct[14].set = "3C";
  ct[15].name = "JEQ";		ct[15].set = "30";
  ct[16].name = "JGT";		ct[16].set = "34";
  ct[17].name = "JLT";		ct[17].set = "38";
  ct[18].name = "JSUB";		ct[18].set = "48";
  ct[19].name = "LDA";		ct[19].set = "00";
  ct[20].name = "LDB";		ct[20].set = "68";
  ct[21].name = "LDCH";		ct[21].set = "50";
  ct[22].name = "LDF";		ct[22].set = "70";
  ct[23].name = "LDL";		ct[23].set = "08";
  ct[24].name = "LDS";		ct[24].set = "6C";
  ct[25].name = "LDT";		ct[25].set = "47";
  ct[26].name = "LDX";		ct[26].set = "04";
  ct[27].name = "LPS";		ct[27].set = "D0";
  ct[28].name = "MUL";		ct[28].set = "20";
  ct[29].name = "MULF";		ct[29].set = "60";
  ct[30].name = "MULR";		ct[30].set = "98";
  ct[31].name = "NORM";		ct[31].set = "C8";
  ct[32].name = "OR";		ct[32].set = "44";
  ct[33].name = "RD";		ct[33].set = "D8";
  ct[34].name = "RMO";		ct[34].set = "AC";
  ct[35].name = "RSUB";		ct[35].set = "4C";
  ct[36].name = "SHIFTL";	ct[36].set = "A4";
  ct[37].name = "SHIFTR";	ct[37].set = "A8";
  ct[38].name = "SIO";		ct[38].set = "F0";
  ct[39].name = "SSK";		ct[39].set = "EC";
  
  ct[40].name = "STA";		ct[40].set = "0C";
  ct[41].name = "STB";		ct[41].set = "78";
  ct[42].name = "STCH";		ct[42].set = "54";
  ct[43].name = "STF";		ct[43].set = "80";
  ct[44].name = "STI";		ct[44].set = "D4";
  ct[45].name = "STL";		ct[45].set = "14";
  ct[46].name = "STS";		ct[46].set = "7C";
  ct[47].name = "STSW";		ct[47].set = "E8";
  ct[48].name = "STT";		ct[48].set = "84";
  ct[49].name = "STX";		ct[49].set = "10";
  ct[50].name = "SUB";		ct[50].set = "1C";
  ct[51].name = "SUBF";		ct[51].set = "5C";
  ct[52].name = "SUBR";		ct[52].set = "94";
  ct[53].name = "SVC";		ct[53].set = "B0";
  ct[54].name = "TD";		ct[54].set = "E0";
  ct[55].name = "TIO";		ct[55].set = "F8";
  ct[56].name = "TIX";		ct[56].set = "2C";
  ct[57].name = "TIXR";		ct[57].set = "B8";
  ct[58].name = "WD";		ct[58].set = "DC";
}

void cshow(){
  string a;
  cin >> a;
  for( int i = 0; i < 59; i++){
    if( a == ct[i].name ) cout << ct[i].set;
  }
  
}


void clear(){
  for( int i = 0; i < 100 ; i++ ){
    num_t[ i ] = "";
    sym_t[i] = "";
    mess_t[i] = "";
  }
}

void readtable( string name, vector<string>& foo ){
  fstream fin;
  
  fin.open( name.c_str(),ios::in);
  while(fin.getline(line,sizeof(line),'\n')){
    //cout << line << endl;
    foo.push_back(line);
  }
  
}


void tables_value( vector<string> foo ) {
  int i = 1;
  for (vector<string>::iterator it = foo.begin(); it != foo.end(); ++it){
    cout << i << " " << *it << "\n";
    i++;
  }
  
}


//******************************************

static int linecount = 1;
static int xelinecount = 1;

static int pc = 0;
static int sympc = 0;

bool check_t2( string a ){
  for (vector<string>::iterator it = vec[2].begin(); it != vec[2].end(); ++it){
    string s = *it;
    if( s == a ) return true;
  }
  return false;
}

void stat_clear( string (&stat)[4] ){
  for( int i = 0; i < 4; i++ ) stat[i] = "";
}

int check_Byte( string a ){
  const char *cstr = a.c_str();
  int first = 0;
  int count = 0;
  char oper = '\0';
  for( int i = 0; i <= a.length(); i++ ){
    if( i == 0 ) oper = cstr[i];
    
    else if( cstr[i] == '\'' ){
      if( first == 0 ) first = 1;
      else if( first == 1 )break;
    }
    else if( first == 1 ){
      count++;
    } // else
  }
  
  if( oper == 'C' )return count;
  else if( oper == 'X' ) return count/2;
  
  
  return count;
}
//*******************************************
//*******************************************


void show_label(){
  for( int i = 0; i < sympc; i++ ){
    cout << "label = " << sym_table[i].label;
    cout << "loc = " << sym_table[i].loc << "\n";
  }
}

//-------------------------all table
// ------------------------pass2
void show_all_table( string line, int c2 ){
  cout << dec << c2*5 << "\t";
  if( pass1[c2].loc != 0 ) cout << hex << uppercase << pass1[c2].loc << "\t";
  else if( pass1[c2].loc == 0 )cout << "\t" << line << "\t";
}

void show_loc(){
  for( int i = 0; i < linecount; i++ ){
    cout << dec << i*5 << " ";
    cout << hex << uppercase << pass1[i].loc << "\n";
  }
}

// ---------------------------------

string check_ct( string a ){
  for( int i = 0; i < 59; i++ ){
    if( a == ct[i].name )
      return ct[i].set;
  }
  return "";
}

// -----------------------------------


// ++++++++++++++++++++++++++++++++++++++++++

int check_label( string label ){
  for( int i = 0; i < sympc; i++ ){
    if( label == sym_table[i].label )
      return sym_table[i].loc ;
  }
  return 0;
}



// ******************************************
// ******************************************
// ******************************************
void check_Byte_pass2( string a ){    //pass2
  const char *cstr = a.c_str();
  int first = 0;
  char oper = '\0';
  for( int i = 0; i <= a.length(); i++ ){
    if( i == 0 ) oper = cstr[i];
    
    else if( cstr[i] == '\'' ){
      if( first == 0 ) first = 1;
      else if( first == 1 )break;
    }
    else if( first == 1 ){
      if( oper == 'X' ) {
        cout << cstr[i] ;  //***
        fout << cstr[i] ;
      }
      else if( oper == 'C' ){
        cout << hex << (int)cstr[i];  //**
        fout << hex << (int)cstr[i];  //**
      }
    } // else
  }
  
  cout << "\n";  //****
  fout << "\n";
  
}

bool check_x( string a ){    //pass2
  const char *cstr = a.c_str();
  for( int i = 0; i<= a.length(); i++ )
    if( cstr[i] == ',')
      return true;
  return false;
}

bool check_x_split( string &op ){     // pass2
  string op2 = op;
  const char *cstr = op.c_str();
  char a[10];
  int j = 0;
  for( int i = 0; i<= op.length(); i++ ){
    if( cstr[i] != ',') {
      a[j] = cstr[i];
      j++;
    }
    else if( cstr[i] == ','){
      a[j] = '\0';
      op = a;
    }
  }
  if( cstr[op2.length()-1] == 'X' ) return true;
  return false;
  
}

bool check_x_jump( string op ){     // pass2
  string op2 = op;
  const char *cstr = op.c_str();
  char a[10];
  int j = 0;
  for( int i = 0; i<= op.length(); i++ ){
    if( cstr[i] == ',') j = 1;
  }
  if( cstr[op2.length()-1] == 'X' && j == 1 ) return true;
  return false;
}

void stat_clear2( string (&stat)[10] ){
  for( int i = 0; i < 10; i++ ) stat[i] = "";
}

char Convert( int one ){
  char a ;
  if( one == 10 ) a = 'A';
  else if (one == 11 ) a = 'B';
  else if ( one == 12 ) a = 'C';
  else if ( one == 13 ) a = 'D';
  else if ( one == 14 ) a = 'E';
  else if ( one == 15 ) a = 'F';
  else a = (one + 48);
  return a;
}

string Turn_hex( string str){             //pass2
  char a[10];
  const char *cstr = str.c_str();
  int one = (cstr[0] - '0') + 8;
  for( int i = 0; i <= str.length(); i++ )a[i] = cstr[i];
  a[0] = Convert( one );
  a[str.length()] = '\0';
  return a;
}

void show_op( string stat[10], int num ){     //pass2
  stringstream ss;
  ostringstream os;
  int val = 0;
  
  if( num == 1 ) {
    cout << check_ct( stat[1] );
    cout << "0000" << "\n";
    fout << "\t";
    fout << check_ct( stat[1] );
    fout << "0000" << "\n";
  }
  
  if( num == 2 ){
    
    if( stat[1] == "END" );
    else {
      
      cout << check_ct( stat[1] );
      fout << check_ct( stat[1] );
      
      if(check_x(stat[2])== true){
        
        if( check_x_split( stat[2] ) ) {
          os << hex << check_label(stat[2]);
          string a = os.str();    //1039
          cout << Turn_hex(a) << "\n";
          fout << Turn_hex(a) << "\n";
        }
      }
      
      else {
        cout << check_label( stat[2]) << "\n";
        fout << check_label( stat[2]) << "\n";
      }
    }
  }
  else if( num == 3 ){
    if( check_t2( stat[2] ) == true ){
      string a;
      if( stat[2] == "WORD" ){
        
        ss << stat[3];   //string to int
        ss >> val;
        
        os << hex << val;  // hex int to string
        string a = os.str();
        
        const char *cstr = a.c_str(); //1
        char code[7];
        for( int i = 0; i <= 5 ; i++ ) code[i] = '0';
        int p = 0;
        for( int i = (6 - a.length()) ; i <= 5 ; i++ ) code[i] = cstr[p++];
        code[6] = '\0';
        cout << code << "\n";    //***
        fout << code << "\n";
      } // if word
      
      else if( stat[2] == "BYTE")
        check_Byte_pass2( stat[3]);
      
      else {
        cout << "\n";    //table2 nothing
        fout << "\n";
      }
      
    } // if
    else {
      cout << check_ct( stat[2] );
      cout << check_label( stat[3]) ;
      cout << "\n";
      fout << check_ct( stat[2] );
      fout << check_label( stat[3]) ;
      fout << "\n";
    } // else
  }
} // show_op



// +++++++++++++++++++++++++++++++++++++++++++++

void token2_pass2_line( string line, int &c2 ){   // pass2
  const char *cstr = line.c_str();
  char a[10];
  strcpy( a, "" );
  int j = 0;
  int num = 0;
  string op[4] ;
  stat_clear( op );
  int trash = 0;
  
  //if( line.length() != 0 )
  
  
  for( int i = 0; i <= line.length(); i++ ){
    
    if( cstr[i] == ' ' || cstr[i] == '\t' || i == line.length() ) {
      if( j != 0 ){
        a[j] = '\0';
        j = 0;
        num++;
        op[num] = a;
        strcpy( a, "" );
      }
    }
    
    else if( cstr[i] != ' ' ) {
      a[j] = cstr[i] ;
      j++;
      if( cstr[i] == '.' ) {
        trash = 1;
        break;
      }
    }
    
  } // for
  
  
  if( line.length() == 0 ) {
    c2 -= 1;
    cout << line << "\n";
    fout << line << "\n";
  }
  else {
    if( trash != 1 && line.length() != 0 ) {
      if( op[1] == "END"){                        //後面忽略
        cout << dec << c2*5 << "\t\t" << line << "\t\t";
        fout << dec << c2*5 << "\t\t" << line << "\t\t";
      }
      else {
        cout << dec << c2*5 << "\t";
        cout << hex << uppercase << pass1[c2].loc << "\t";
        cout << line << "\t\t";
        fout << dec << c2*5 << "\t";
        fout << hex << uppercase << pass1[c2].loc << "\t";
        if( num == 2 ){                                        //喬buffer,x位置
          if(check_x_jump( op[2] ) )fout << line << "\t";
          else fout << line << "\t\t";
        }
        
        else fout << line << "\t\t";
      }
    }
    else {
      cout << dec << c2*5 << "\t\t" << line << "\n";
      fout << dec << c2*5 << "\t\t" << line << "\n";
    }
  }
  
  
  if( trash != 1 && line.length() != 0 )
    show_op( op, num );
  
} // token2_pass2_line

// pass1
void show_stat( string stat[10], int num, int opc ){      // ----------pass1
  
  if( num == 2 || num == 1){
    pc = pc + 3;
  }
  
  else if( num == 3 ){
    if( check_t2( stat[2] ) == true ){
      stringstream ss;
      int n;
      
      if( stat[2] == "START" ) {
        ss << hex << stat[3];
        ss >> n;
        pc = n;
      }
      else if( stat[2] == "RESB" ){
        ss << dec << stat[3];
        ss >> n;
        pc += n;
      }
      else if( stat[2] == "BYTE"){
        pc += check_Byte( stat[3] );
      }
      
      else pc += 3;
    }
    else pc += 3;
    
    sym_table[sympc].label = stat[1];
    sym_table[sympc].loc = opc;
    
    sympc++;
    
  } // if
}


void token2_line( string line ){                          //  ----------pass 1
  const char *cstr = line.c_str();
  char a[10];
  strcpy( a, "" );
  int j = 0;
  //pass1[count].numline = count*5;
  int num = 0;
  string stat[10] ;
  stat_clear2( stat );
  int trash = 0;
  
  for( int i = 0; i <= line.length(); i++ ){
    
    if( cstr[i] == ' ' || cstr[i] == '\t' || i == line.length() ) {
      if( j != 0 ){
        a[j] = '\0';
        j = 0;
        num++;
        
        stat[num] = a;
        strcpy( a, "" );
      }
    }
    
    else if( cstr[i] != ' ' ) {
      a[j] = cstr[i] ;
      j++;
      if( cstr[i] == '.' ) {
        trash = 1;
        break;
      }
    }
    
  } // for
  
  
  if( trash == 0 && line.length() != 0 ){    //
    
    //cout << "line " << dec << pass1[count].numline << " " ;
    if( stat[2] == "START" ) {
      stringstream ss;   int n;
      ss << hex << stat[3];
      ss >> n;
      pass1[linecount].loc = n;
    } // if
    
    else pass1[linecount].loc = pc;
    int opc = pc;
    show_stat( stat, num, opc );
    
  }
  else if( line.length() == 0 ) {
    //cout << "null";
    linecount -= 1;
  }
}

//*********************************************************************six-xe
//**********************************************************************

static int xepc = 0;
static int xesympc = 0;

bool checkreg( string reg ) {
  string s = reg;
  transform(s.begin(), s.end(), s.begin(),::toupper);  // 轉大寫
  for( int i = 0; i < 7; i++ ){
    
    if( reg == rt[i].name || s == rt[i].name ) {
      //cout << " reg yes! ";
      return true;
    }
  }
  return false;
}

string xe_fix( string res ){
  char a[6] ;
  const char *cstr = res.c_str();
  int len = res.length();
  int num = 4 - len;
  int i = 0;
  for( i = 0; i < num; i++ )a[i] = '0';
  a[num] = '\0';
  strcat( a, cstr);
  return a;
}

string xe_fix5( string res ){
  char a[6] ;
  const char *cstr = res.c_str();
  int len = res.length();
  int num = 5 - len;
  int i = 0;
  for( i = 0; i < num; i++ )a[i] = '0';
  a[num] = '\0';
  strcat( a, cstr);
  return a;
}

void show_xe_label(){
  //stringstream res;
  for( int i = 0; i < xesympc; i++ ){
    cout << "label =  " <<  xesym_table[i].label;
    stringstream res;
    res << hex << uppercase << xesym_table[i].loc;
    cout << "loc = " << xe_fix( res.str() ) << "\n";
    //cout << "loc = " << xesym_table[i].loc << "\n";
  }
}

bool check_sic_table( string s1 ){
  string s = s1;
  transform(s.begin(), s.end(), s.begin(),::toupper);  // 轉大寫
  for( int i = 0; i < 59; i++)
    if( s == ct[i].name ) return true;
  return false;
}


bool checkin_show_label( string label ){
  for( int i = 0; i < xesympc; i++ ){
    if(xesym_table[i].label == label) return true;
  }
  return false;
}

static int def = 0;

void show_stat_xe( string stat[10], int num, int opc ){      // ----------xe pass1----show_stat_xe
  //cout << "line " << dec << xelinecount << " " ;
  stringstream ss;
  int n;
  def = 0;
  if( num == 1 ) {
    if( check_sic_table( stat[1] ) )xepc += 1;
    else def = -1;
  }
  
  else if( num == 2) {
    
    const char *cstr = stat[1].c_str();
    
    if(cstr[0] == '+') {
      // cout << "plus + 4 ";
      char str[10];
      int i = 0;
      for( i = 0; i < stat[1].length(); i++ )str[i] = cstr[i+1];
      str[i] = '\0';
      string s = str ;
      
      if( checkin_show_label(stat[2]) && check_sic_table( s )) xepc += 4;
      else def = -1;
    }
    else {
      int format2 = 0;
      const char *cstr = stat[2].c_str();
      for( int i = 0; i < stat[2].length(); i++ ) if( cstr[i] == ',') format2 = 1;
      if( format2 == 1 || checkreg( stat[2] ) ) {
        xepc += 2;
        //cout << " format2 + 2";
      }
      else {
        if( check_sic_table( stat[1] ) ) xepc += 3;
        else if( stat[1] == "END");
        else def = -1;
      }
    }
    
    
  }
  
  else if( num == 3 ){
    if( stat[2] == "START") {
      ss << dec << stat[3];
      ss >> n;
      xepc = n;
    }
    /*
     else if(stat[2]== "RESW") {
     ss << dec << stat[3];
     ss >> n;
     xepc += n;
     }*/
    else if(stat[2] == "RESB") {
      ss << dec << stat[3];
      ss >> n;
      xepc = n;
    }
    else xepc += 3;
    
    xesym_table[xesympc].label = stat[1];
    xesym_table[xesympc].loc = opc;
    xesympc++;
  }
  
  else def = -1;
  //for( int i = 1; i <= num ; i++ ) cout << "!" << stat[i] << "\n";
  
  
  
  //xepass1[xelinecount].loc = xepc;//********
  //cout << "!!!!= " << hex << xepc << "!!!!";
}

void xe_show_loc(){
  for( int i = 1; i < xelinecount ; i++ ){
    cout << i*5 << "\t"; //"loc = " << xepass1[i].loc << "\n";
    stringstream res;
    res << hex << uppercase << xepass1[i].loc;
    cout << xe_fix( res.str() ) << "\n";
  }
  
}

void xe_show_table( int currline ){
  cout << currline*5 << "\t";
  stringstream res;
  res << hex << uppercase << xepass1[currline].loc;
  cout << xe_fix( res.str() ) << "\t";
}




int check_xe_label( string name ){
  for( int i = 0; i < xesympc ; i++ ){
    if( name == xesym_table[i].label )
      return xesym_table[i].loc;
  }
  return -1;
}

int Convert_char( char a ){
  if( a == 'A' ) return 10;
  else if( a == 'B' ) return 11;
  else if( a == 'C' ) return 12;
  else if ( a == 'D' )return 13;
  else if( a == 'E' )return 14;
  else if ( a == 'F' )return 15;
  else return (int)a - 48;
  return 0;
}


int check_loc_noterror( int curr ){
  for( int i = curr; i < xelinecount-1 ; i++ )
    if( xepass1[i].loc != -1 ) return xepass1[i].loc;
  return 0;
}

string int_to_hex( int j )
{
  stringstream sstream;
  sstream << hex << uppercase  << j;
  string s = sstream.str();
  const char *cstr = s.c_str();
  char a[ 10 ];
  for( int i = 0; i < 10 ; i++ ) a[i] = '0';
  int p = 0;
  for( int i = s.length() - 3 ; i < s.length(); i++ ) {
    a[p] =  cstr[i] ;
    p++;
  }
  a[p] = '\0';
  return a;
}

void xe_format3( string stat[4], int num, int currline ){
  string s = stat[1];
  transform(s.begin(), s.end(), s.begin(),::toupper);  // 轉大寫
  string opcode = check_ct( s );
  const char *cstr = opcode.c_str();
  
  int n = Convert_char(cstr[1]);  //(int)cstr[1] - 48;
  n += 3;
  
  int ta = check_xe_label( stat[2] );   //check xe label return location
  //int pc = xepass1[currline+1].loc; // return location (pc)
  int pc = check_loc_noterror( currline+1 );
  
  stringstream res;
  res << hex << uppercase << pc;
  if( ta == -1 ){
    string spc = xe_fix( stat[2] );   //0000
    cout << cstr[0] << hex << uppercase << n << spc;
    fout << cstr[0] << hex << uppercase << n << spc;
  }
  else {
    string spc = xe_fix( res.str() );   //0000
    const char *cspc = spc.c_str();
    int count = ta-pc ;
    
    cout << cstr[0] << hex << uppercase << n << 2 ;
    cout << int_to_hex(count);
    
    fout << cstr[0] << hex << uppercase << n << 2 ;
    fout << int_to_hex(count);
    
    
  }
  // cout << "currline " << currline;
  // cout << "op = " << opcode << " n = " << n << " " << "ta = " << ta; //<< "pc = " << spc;
  
}

void xe_format4( string stat[10] ){   // +addf     var2                5B100003
  const char *cstr = stat[1].c_str();
  char str[10]; int i;
  for( i = 0; i < stat[1].length() ; i++ ) str[i] = cstr[i+1];
  str[i] = '\0';
  //cout << str;
  
  string s = str;
  transform(s.begin(), s.end(), s.begin(),::toupper);  // 轉大寫
  string opcode = check_ct( s );
  //cout << opcode;
  cstr = opcode.c_str();
  int n = Convert_char(cstr[1]);  //(int)cstr[1] - 48;
  n += 3;
  
  int address = check_xe_label( stat[2] );
  
  stringstream res;
  res << hex << uppercase << address;
  string spc = xe_fix5( res.str() );
  
  cout << cstr[0] << hex << uppercase << n << 1 << spc;
  fout << cstr[0] << hex << uppercase << n << 1 << spc;
  
  //xe_fix5();
}

int check_regtable( string a ){
  for( int i = 0; i < 7; i++ )
    if( a == rt[i].name ) return rt[i].set;
  return 0;
}

void xe_format2( string stat[10] ){  // addr      a,b
  string s = stat[1];
  transform(s.begin(), s.end(), s.begin(),::toupper);  // 轉大寫
  
  string s2 = stat[2];
  transform(s2.begin(), s2.end(), s2.begin(),::toupper);  // 轉大寫
  
  string opcode = check_ct( s );
  cout << opcode;
  fout << opcode;
  if( s2.length() == 1 )cout << check_regtable( s2 ) << "0";
  else {
    const char *str = s2.c_str();
    stringstream res;
    res << str[0] ;
    cout << check_regtable( res.str() );
    fout << check_regtable( res.str() );
    stringstream res2;
    res2 << str[2] ;
    cout << check_regtable( res2.str() ) ;
    fout << check_regtable( res2.str() ) ;
  }
}

void xe_format1( string stat[10] ){
  string s = stat[1];
  transform(s.begin(), s.end(), s.begin(),::toupper);  // 轉大寫
  string opcode = check_ct( s );
  cout << opcode;
  fout << opcode;
}

void show_stat_format( string stat[10], int num, int currline ){      // ----------xe pass2 -------show_stat_format
  //cout << "line " << xelinecount << " " ;
  
  stringstream ss;
  int n;
  if( num == 1 ){
    //cout << "format 1 ";
    xe_format1( stat );
  }
  
  else if( num == 2) {
    
    const char *cstr = stat[1].c_str();
    if(cstr[0] == '+') {
      //cout << "format 4 ";
      xe_format4( stat );
    }
    else {
      int format2 = 0;
      const char *cstr = stat[2].c_str();
      for( int i = 0; i < stat[2].length(); i++ ) if( cstr[i] == ',') format2 = 1;
      if( format2 == 1 ) {
        //cout << " format2 ";
        xe_format2( stat );
      }
      else {
        if( checkreg( stat[2] )) {
          //cout << " format2 ";
          xe_format2( stat );
        }
        else {
          //cout << " format3 ";
          xe_format3( stat, num, currline );
        }
        
      }
    }
    
  } // else if
  
  
}  //show_stat_format


void token_line_xe2( string line, int currline ){                          //  ----------pass 2  xe ----token_line_xe2
  const char *cstr = line.c_str();
  char a[10];
  strcpy( a, "" );
  int j = 0;
  //pass1[count].numline = count*5;
  int num = 0;
  string stat[10] ;
  stat_clear2( stat );
  int trash = 0;
  
  for( int i = 0; i <= line.length(); i++ ){
    
    if( cstr[i] == ' ' || cstr[i] == '\t' || i == line.length() ) {
      if( j != 0 ){
        a[j] = '\0';
        j = 0;
        num++;
        
        stat[num] = a;
        strcpy( a, "" );
      }
    }
    
    else if( cstr[i] != ' ' ) {
      a[j] = cstr[i] ;
      j++;
      if( cstr[i] == '.' ) {
        trash = 1;
        break;
      }
    }
    
  } // for
  
  //for( int i = 1; i <= num ; i++ ) cout << "!" << stat[i] << "\n";
  
  cout << dec << currline*5 << "\t";
  fout << dec << currline*5 << "\t";
  
  if( trash == 0 && line.length() != 0 ){
    //xe_show_table( currline );
    
    stringstream res;
    if( xepass1[currline].loc != -1 ){
      res << hex << uppercase << xepass1[currline].loc;
      if( stat[1] != "END" ){
        cout << xe_fix( res.str() ) << "\t";
        fout << xe_fix( res.str() ) << "\t";
      }
      else {
        cout << "\t";
        fout << "\t";
      }
    }
    else {
      cout << "error message ! ";
      fout << "error message ! ";
    }
    
    cout << line << "\t\t";
    fout << line << "\t\t";
    
    if( stat[1] != "END" && xepass1[currline].loc != -1 )show_stat_format( stat , num, currline );
  }
  if( trash == 1 ) {
    cout << "\t\t" << line ;
    fout << "\t\t" << line ;
  }
  else if( line.length() == 0 ) {
    xelinecount -= 1;
  }
}




void token_line_xe( string line ){                          //  ----------pass 1  xe-----token_line_xe
  const char *cstr = line.c_str();
  char a[10];
  strcpy( a, "" );
  int j = 0;
  //pass1[count].numline = count*5;
  int num = 0;
  string stat[10] ;
  stat_clear2( stat );
  int trash = 0, start = 0;
  
  for( int i = 0; i <= line.length(); i++ ){
    
    if( cstr[i] == ' ' || cstr[i] == '\t' || i == line.length() ) {
      if( j != 0 ){
        a[j] = '\0';
        j = 0;
        num++;
        
        stat[num] = a;
        if( stat[num] == "START" )start = 1; //*****
        strcpy( a, "" );
      }
    }
    
    else if( cstr[i] != ' ' ) {
      a[j] = cstr[i] ;
      j++;
      if( cstr[i] == '.' ) {
        trash = 1;
        break;
      }
    }
    
  } // for
  
  if( start == 1 && num == 3 ){
    //int opc = stat[num];
    stringstream ss;
    int opc =  0;
    ss << stat[num];
    ss >> opc;
    ss << hex << uppercase << opc;
    //cout << xe_fix( ss.str() );
    show_stat_xe( stat, num, opc );
    xepass1[xelinecount].loc = opc;//********xepc
    
  }
  
  
  else if( trash == 0 && line.length() != 0 ){    //
    
    //cout << "line " << dec << pass1[count].numline << " " ;
    
    int opc = xepc;
    // cout << "pc = ";
    //cout << hex << uppercase << opc;
    //  stringstream res;
    //  res << hex << uppercase << opc;
    //  cout << xe_fix( res.str() );
    
    show_stat_xe( stat, num, opc );
    
    xepass1[xelinecount].loc = opc;//********xepc
    if( def == -1 )xepass1[xelinecount].loc = -1;
    
  }
  else if( line.length() == 0 ) {
    //cout << "null";
    xelinecount -= 1;
  }
}
//-----------------------------------------------------------------------

void readfile( string name ){
  fstream fin;
  //int count = 1;
  fin.open( name.c_str(),ios::in);
  fout << "Line\tLoc\tSource statement\t\tObject code\n";
  while(fin.getline(line,sizeof(line),'\n')){
    token2_line( line );
    linecount++;
  }
}

void readfile2( string name ){
  fstream fin;
  int c2 = 1;
  fin.open( name.c_str(),ios::in);
  while(fin.getline(line,sizeof(line),'\n')){
    token2_pass2_line( line, c2 );
    c2++;
  }
}

void readfile_xe( string name ){
  fstream fin;
  fin.open( name.c_str(),ios::in);
  //cout << "\n";
  while(fin.getline(line,sizeof(line),'\n')){
    token_line_xe( line );
    //cout << line << "\n";
    xelinecount++;
  }
}

void readfile_xe2( string name ){
  fstream fin;
  fin.open( name.c_str(),ios::in);
  int currline = 1;
  cout << "Line  Location  Source code                              Object code\n";
  cout << "----  -------- -------------------------                 -----------\n";
  
  fout << "Line  Location  Source code                              Object code\n";
  fout << "----  -------- -------------------------                 -----------\n";
  
  while(fin.getline(line,sizeof(line),'\n')){
    token_line_xe2( line, currline );
    currline++;
    cout << "\n";
    fout << "\n";
  }
}

int main(){
  
  
  
  clear();
  
  //
  
  
  vec.resize(5);
  
  cout << "開始讀入Table1~4.table 檔 : ";
  
  for( int i = 1; i <= 4; i++ ){
    stringstream ss, t;
    ss << "Table" << i << ".table" ;
    //cout << ss.str() << "\n";
    readtable( ss.str() , vec[i] );
  }
  
  
  cout << "\n";
  settable();
  setregtable();
  string a ;
  int choose = 0;
  cout << "選擇測試檔案 1.SIC 2.SICXE :";
  cin >> choose;
  if( choose == 1 ){
    fout.open( "SIC_output.txt", ios::out);
    
    cout << "輸入測試SIC檔案 :";
    cin >> a;
    readfile( a );
    readfile2( a );
    fout.close();
  }
  
  //show_xe_label();
  //xe_show_loc();
  else if( choose == 2 ){
    fout.open( "SICXE_output.txt", ios::out);
    
    //readfile_xe( "SICXE_input.txt" );
    //readfile_xe2( "SICXE_input.txt" );
    cout << "輸入測試SICXE檔案 :";
    cin >> a;
    //readfile( a );
    //readfile2( a );
    readfile_xe( a);
    readfile_xe2( a );
    fout.close();
  }
  else cout << "no this option!";
  
  system("pause");
  return 0;
}
