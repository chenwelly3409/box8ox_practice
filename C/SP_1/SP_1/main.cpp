//
//  main.cpp
//  SP_1
//
//  Created by 陳建誌 on 2017/8/16.
//  Copyright © 2017年 陳建誌. All rights reserved.
//

# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <iostream>
# include <fstream>
using namespace std;

static string table1[117], table2[19], table3[20], table4[13]; // 指令 特殊字串 暫存器 符號
static string table5[100] = {}, table6[100] = {}, table7[100] = {}; // 宣告 數字 字串
static FILE *finput = NULL, *foutput;

void CreateFourTable();
void CutToken( char chtemp[] );
void CheckToken( string strList[] );
void TableListCount( int &tableList, string strList[], int listNum );
void CheckTable( int &tableNum, int &tableList, string strList[], int listNum );

int main() {
  string inputfile, outputfile;
  
  do {
    cout << endl << "Input a file name : ";
    cin >> inputfile;
    finput = fopen( inputfile.c_str(), "r" );
    if ( finput == NULL )
      cout << endl << "File does not exist!" << endl;
  } while ( finput == NULL );
  
  outputfile = inputfile;
  outputfile.erase( outputfile.end()-4, outputfile.end() );
  outputfile = outputfile + "_output.txt";
  foutput = fopen( outputfile.c_str(), "w" );
  
  CreateFourTable();
  
  char chtemp[100] = {};
  while ( !feof( finput ) ) {
    fgets( chtemp, 100, finput );
    cout << chtemp;
    fprintf( foutput, "%s", chtemp );
    if ( feof( finput ) ) {
      cout << "\n";
      fprintf( foutput, "\n" );
    } // if()
    CutToken( chtemp );
  } // while()
  
  fclose( finput );
  fclose( foutput );
  exit(0);
} // main()

void CreateFourTable() {
  string tablefile, stemp;
  int itemp = 0;
  
  ifstream itable1( "Table1.table", ifstream::in );
  for ( int i = 0 ; i < 117 ; i++ ) {
    getline( itable1, stemp );
    char *pch = strchr( stemp.c_str(), ' ' );	// 以' '間隔
    if ( pch != NULL ) {
      itemp = pch-stemp.c_str()+1;
    } // if()
    else {
      pch = strchr( stemp.c_str(), '\t' );	// 或許以'\t'間隔
      itemp = pch-stemp.c_str()+1;
    } // else()
    stemp.erase( 0, itemp );
    table1[i] = stemp;
  } // for()
  itable1.close();
  
  ifstream itable2( "Table2.table", ifstream::in );
  for ( int i = 0 ; i < 19 ; i++ ) {
    getline( itable2, stemp );
    char *pch = strchr( stemp.c_str(), ' ' );	// 以' '間隔
    if ( pch != NULL ) {
      itemp = pch-stemp.c_str()+1;
    } // if()
    else {
      pch = strchr( stemp.c_str(), '\t' );	// 或許以'\t'間隔
      itemp = pch-stemp.c_str()+1;
    } // else()
    stemp.erase( 0, itemp );
    table2[i] = stemp;
  } // for()
  itable2.close();
  
  ifstream itable3( "Table3.table", ifstream::in );
  for ( int i = 0 ; i < 20 ; i++ ) {
    getline( itable3, stemp );
    char *pch = strchr( stemp.c_str(), ' ' );	// 以' '間隔
    if ( pch != NULL ) {
      itemp = pch-stemp.c_str()+1;
    } // if()
    else {
      pch = strchr( stemp.c_str(), '\t' );	// 或許以'\t'間隔
      itemp = pch-stemp.c_str()+1;
    } // else()
    stemp.erase( 0, itemp );
    table3[i] = stemp;
  } // for()
  itable3.close();
  
  ifstream itable4( "Table4.table", ifstream::in );
  for ( int i = 0 ; i < 13 ; i++ ) {
    getline( itable4, stemp );
    char *pch = strchr( stemp.c_str(), ' ' );	// 以' '間隔
    if ( pch != NULL ) {
      itemp = pch-stemp.c_str()+1;
    } // if()
    else {
      pch = strchr( stemp.c_str(), '\t' );	// 或許以'\t'間隔
      itemp = pch-stemp.c_str()+1;
    } // else()
    stemp.erase( 0, itemp );
    table4[i] = stemp;
  } // for()
  itable4.close();
  
} // CreateFourTable()

void CutToken( char chtemp[] ) {
  string strList[20] = {};
  int listNum = 0;
		
  for ( int i = 0 ; chtemp[i] != '\0' ; i++ ) {
    if ( chtemp[i] == ' ' || chtemp[i] == '\t' || chtemp[i] == '\n' )
      ;
    else if ( ( chtemp[i] >= 'a' && chtemp[i] <= 'z' ) || ( chtemp[i] >= 'A' && chtemp[i] <= 'Z' ) ) {
      string stemp;
      while ( ( chtemp[i] >= 'a' && chtemp[i] <= 'z' ) || ( chtemp[i] >= 'A' && chtemp[i] <= 'Z' ) ) {
        stemp += chtemp[i];
        i++;
      } // while()
      
      strList[listNum] = stemp;
      listNum++, i--;
    } // else if()
    
    else if ( chtemp[i] >= '0' && chtemp[i] <= '9' ) {
      string stemp;
      while ( ( chtemp[i] >= '0' && chtemp[i] <= '9' ) ||
             ( chtemp[i] >= 'a' && chtemp[i] <= 'z' ) || ( chtemp[i] >= 'A' && chtemp[i] <= 'Z' ) ) {
        stemp += chtemp[i];
        i++;
      } // while()
      
      strList[listNum] = stemp;
      listNum++, i--;
    } // else if()
    
    else {
      strList[listNum] = chtemp[i];
      listNum++;
      
      if ( chtemp[i] == '\'' ) {
        string stemp;
        i++;
        while ( chtemp[i] != '\'' ) {
          stemp += chtemp[i];
          i++;
        } // while()
        
        strList[listNum] = stemp, listNum++;
        strList[listNum] = chtemp[i];
        listNum++;
      } // if()
    } // else()
  } // for()
  /*
   for ( int i = 0 ; i < listNum ; i++ ) {
   cout << strList[i] << endl;
   } // for()
   */
  
  CheckToken( strList );
} // CutToken()

void CheckToken( string strList[] ) {
  int listNum = 0;
  for ( int i = 0 ; strList[i] != "" ; i++ )
    listNum++;
  bool nextStr = false, end = false;
  
  int tableNum, tableList, value;
  for ( int i = 0 ; i < listNum && !end ; i++ ) {
    tableNum = 0, tableList = 0, value = 0;
    char ch = strList[i].c_str()[0];
    
    if ( ch == ';' ) {
      end = true;
      tableNum = 4;
      tableList = 9;
    } // if()
    
    else if ( ch == '\'' ) {
      if ( !nextStr )
        nextStr = true;
      else
        nextStr = false;
      tableNum = 4;
      tableList = 13;
    } // else if()
    
    else if ( ch >= '0' && ch <= '9' ) {
      tableNum = 6;
      TableListCount( tableList, strList, i );
    } // else if()
    
    else {
      if ( nextStr ) {	// 字串
        tableNum = 7;
        TableListCount( tableList, strList, i );
      } // if()
      
      else if ( ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E' || ch == 'F' ||
               ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' ) {
        char checkBack = strList[i].c_str()[ strList[i].length()-1 ];
        
        if ( checkBack == 'H' || checkBack == 'h' ) {	// table6
          tableNum = 6;
          TableListCount( tableList, strList, i );
        } //if()
        
        else {
          CheckTable( tableNum, tableList, strList, i );
        } // else()
      } // else if()
      
      else if ( ch == '[' || ch == ']' || ch == ',' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
               ch == ':' || ch == '?' || ch == '(' || ch == ')' ) {
        tableNum = 4;
        if ( ch == '[' )	tableList = 1;
        if ( ch == ']' )	tableList = 2;
        if ( ch == ',' )	tableList = 3;
        if ( ch == '+' )	tableList = 4;
        if ( ch == '-' )	tableList = 5;
        if ( ch == '*' )	tableList = 6;
        if ( ch == '/' )	tableList = 7;
        if ( ch == ':' )	tableList = 8;
        if ( ch == '?' )	tableList = 10;
        if ( ch == '(' )	tableList = 11;
        if ( ch == ')' )	tableList = 12;
      } // else if()
      
      else {
        CheckTable( tableNum, tableList, strList, i );
      } // else()
    } // else()
    
    if ( tableNum == 5 || tableNum == 6 || tableNum == 7 ) {	// 檢查是否存在
      if ( tableNum == 5 ) {
        if ( table5[tableList] == "" ) {
          table5[tableList] = strList[i];
        } // if()
        
        else if ( table5[tableList] != strList[i] ) {
          for ( int t = tableList+1 ; table5[t] != strList[i] && table5[t] != "" ; t++ )
            tableList++, tableList %= 100;
          if ( table5[tableList] == "" ) {
            table5[tableList] = strList[i];
          } // if()
        } // else if()
      } // if()
      
      else if ( tableNum == 6 ) {
        if ( table6[tableList] == "" ) {
          table6[tableList] = strList[i];
        } // if()
        
        else if ( table6[tableList] != strList[i] ) {
          for ( int t = tableList+1 ; table6[t] != strList[i] && table6[t] != "" ; t++ )
            tableList++, tableList %= 100;
          if ( table6[tableList] == "" ) {
            table6[tableList] = strList[i];
          } // if()
        } // else if()
      } // else if()
      
      else if ( tableNum == 7 ) {
        if ( table7[tableList] == "" ) {
          table7[tableList] = strList[i];
        } // if()
        
        else if ( table7[tableList] != strList[i] ) {
          for ( int t = tableList+1 ; table7[t] != strList[i] && table7[t] != "" ; t++ )
            tableList++, tableList %= 100;
          if ( table7[tableList] == "" ) {
            table7[tableList] = strList[i];
          } // if()
        } // else if()
      } // else if()
    } // if()
    
    cout << "(" << tableNum << "," << tableList << ")";
    fprintf( foutput, "(%d,%d)", tableNum , tableList );
  } // for()
  
  cout << endl;
  fprintf( foutput, "\n" );
} // CheckToken()

void TableListCount( int &tableList, string strList[], int listNum ) {
  int value = 0;
  char charArray[50] = {};
  strcpy( charArray, strList[listNum].c_str() );
  
  for ( int c = 0 ; charArray[c] != '\0' ; c++ ) {
    value += (int)charArray[c];
  } // for()
  
  tableList = value % 100;
} // TableListCount()

void CheckTable( int &tableNum, int &tableList, string strList[], int listNum ) {
  bool isExist = false;
  char charArray[50] = {};
  strcpy( charArray, strList[listNum].c_str() );
  char upperCase[50] = {};
  for ( int i = 0 ; charArray[i] != '\0' ; i++ )
    upperCase[i] = toupper(charArray[i]);
		
  for ( int t = 0 ; t < 117 && !isExist ; t++ )
    if ( strcmp( upperCase, table1[t].c_str() ) == 0 ) {
      isExist = true;
      tableNum = 1;
      tableList = t+1;
    } // if()
  
  for ( int t = 0 ; t < 19 && !isExist ; t++ )
    if ( strcmp( upperCase, table2[t].c_str() ) == 0 ) {
      isExist = true;
      tableNum = 2;
      tableList = t+1;
    } // if()
  
  for ( int t = 0 ; t < 20 && !isExist ; t++ )
    if ( strcmp( upperCase, table3[t].c_str() ) == 0 ) {
      isExist = true;
      tableNum = 3;
      tableList = t+1;
    } // if()
  
  if ( !isExist ) {
    tableNum = 5;
    TableListCount( tableList, strList, listNum );
  } // if()
} // CheckTable()

