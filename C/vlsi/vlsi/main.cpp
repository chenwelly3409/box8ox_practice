//
//  main.cpp
//  vlsi
//
//  Created by 陳建誌 on 2016/12/23.
//  Copyright © 2016年 陳建誌. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// struct
struct s_vector {
  string name = "";
  string start ;
  string end ;
  int length;
  
};

struct node {
  bool visit = false;
  string name = "";
  string last = "";
  int length = 99999;
  
};
node Node[50];
s_vector Vec[50];

// var

int node_count = 0;
int vec_count = 0;

// function
void read_file();
string get_nodeName( string test );
string get_vecName( string test );
bool get_vecInOut ( string test );
int get_vecLength ( string test );
bool find_sameVec ( string name, int & where_vec );
void printVec();
void DFS();
bool go_all_node();
void print_stack( vector<string> stack );
void go_node( vector<string> & stack, vector<string> & ans, string node_name );
bool find_goVec( string node_name , int & goVec );
bool Is_visit( string node_name );
void init_node();
void Sort();
int getNodeLen( string node_name );
void intoVec( vector<string> & stack, string node_name, int i );
void intoNode( vector<string> & stack, string node_name );
bool findsameNode( vector<string> stack, string node_name );
void printNode();
void printShortAns( string node_name );

#define SIZE 100
char line[SIZE];


int main() {
  read_file();
  //printVec();
  
  DFS();
  init_node();
  Sort();
  
  system("PAUSE");
  return 0;
}


/********read_file************/

void read_file() {
  fstream fin;
  fin.open("/Users/chenjianzhi/8oxbox_practice/C/vlsi/vlsi/test.txt",ios::in);
  int count = 1;

  
  while(fin.getline(line,sizeof(line),'\n')){
    if( count > 3 ) {
      
      if(  strcmp( line , "ENDCIRCUIT" ) != 0 ) {
        
        Node[node_count].name = get_nodeName( line );
        
        //cout << Node[node_count].name << " _ " << node_count <<endl;
        
        fin.getline(line,sizeof(line),'\n');
        
        char *test = strtok(line, " ");
        
        while( test ) {
          
          string temp_vecName = get_vecName(test);
          int where_vec = -1;
          
          bool temp_InOut = get_vecInOut( test );
          int temp_vecLength = get_vecLength( test );
          
          if ( find_sameVec( temp_vecName, where_vec ) ) {
            if ( temp_InOut ) {
              Vec[where_vec].end = Node[node_count].name;
              Vec[where_vec].length = temp_vecLength;
            } // if
            else {
              Vec[where_vec].start = Node[node_count].name;
              Vec[where_vec].length = temp_vecLength;
            } // else
          } // if
          else {
            Vec[vec_count].name = get_vecName( test );
            if ( temp_InOut ) {
              Vec[vec_count].end = Node[node_count].name;
              Vec[vec_count].length = temp_vecLength;
            } // if
            else {
              Vec[vec_count].start = Node[node_count].name;
              Vec[vec_count].length = temp_vecLength;
            } // else
            vec_count ++ ;
          } // else
          
          
          test = strtok(NULL, " ");
        } // while
        
        node_count ++;
        
      } // if
      
    } // if
    
    count ++;
  } // while

} // read_file

string get_nodeName( string test ) {
  string temp_name = "";
  temp_name = test.substr(9,3);
  temp_name = temp_name.substr(0,temp_name.find(" "));
  temp_name = temp_name.substr(0,temp_name.find("	"));
  
  return temp_name;
} // get_nodeName

string get_vecName( string test ) {
  //cout << test << endl;
  
  string temp = "";

  long find = test.find("(");
  temp = test.substr(0,find);
  
  return temp;
} // get_vecName()

bool get_vecInOut ( string test ) {
  string temp = "";
  
  if( test.find("i") != -1) {
    temp = test[test.find("i")];
    return true;
  }
  else {
    temp = test[test.find("o")];
    return false;
  }
  
  
} // get_vecInOut

int get_vecLength ( string test ) {
  string temp = "";
  long find1 = test.find(",");
  long find2 = test.find("(");
  temp = test.substr(find2+1,find1-find2-1);
  
  return atoi(temp.c_str());
} // get_vecLength

bool find_sameVec ( string name, int & where_vec ) {
  
  for ( int i = 0 ; i < vec_count ; i++ ) {
    if ( Vec[i].name == name ) {
      where_vec = i;
      return true;
    }
  }
  
  return false;
} // find_sameVec

void printVec() {
  for( int i = 0 ; i < vec_count ; i++ ) {
    cout << i << " : " ;
    cout << Vec[i].name << " _ " << Vec[i].start << " -> " << Vec[i].end << " - " << Vec[i].length <<endl;
  }
}

/********read_file************/
/********DFS***************/

void DFS() {
  vector<string> stack;
  vector<string> ans;


  go_node( stack, ans, "S");
  
  while( go_all_node() ) {
    int goVec = -1;
    if ( find_goVec( stack[stack.size()-1], goVec ) ) {
      go_node( stack, ans, Vec[goVec].end ) ;
    }
    else {
      stack.pop_back();
    }
    
    //print_stack(stack);
    
  } // while
  
  print_stack(ans);
  
} // DFS

bool go_all_node() {
  for ( int i = 0 ; i < node_count ; i ++ ) {
    if( Node[i].visit == false ) {
      return true;
    }
  }
  return false;
} // Is_go_all_node

void print_stack( vector<string> stack ) {
  for( int i = 0 ; i < stack.size() ; i++ ) {
    cout << stack[i] << " ";
  }
  cout << endl;
} // print_stack

void go_node( vector<string> & stack, vector<string> & ans, string node_name ) {
  stack.push_back( node_name );
  ans.push_back( node_name );
  
  for( int i = 0 ; i < node_count ; i++ ) {
    if( Node[i].name == node_name ) {
      Node[i].visit = true;
      i = node_count;
    }
  }
} // go_node

bool find_goVec( string node_name , int & goVec ) {
  vector<int> temp;
  
  for ( int i = 0 ; i < vec_count ; i++ ) {
    if ( Vec[i].start == node_name ) {
      if( Is_visit( Vec[i].end ) == false ) {
        temp.push_back(i);
      }
      
    }
  }
  
  if( temp.empty() ) {
    return false;
  }
  else {
    int min = Vec[temp[0]].length;
    int where_min = temp[0];
    
  
    
    for( int i = 0 ; i < temp.size() ; i++ ) {
      if( Vec[temp[i]].length < min ) {
        min = Vec[temp[i]].length;
        where_min = temp[i];
      }
    }
    
    goVec = where_min;
    return true;
  }
  
}

bool Is_visit( string node_name ) {
  for( int i = 0 ; i < node_count ; i++ ) {
    if( Node[i].name == node_name ) {
      if( Node[i].visit == true) {
        return true;
      }
      else {
        return false;
      }
    }
  }
  
  return false;
} // Is_visit

/********DFS***************/

/********Shortest***************/

void Sort() {
  vector<string> stack;
  
  stack.push_back("S");
  
  while( go_all_node() ) {
    intoNode( stack, stack[0] );
    
  } // while
  
  printShortAns( "D" );
  
  
} // Sort()

void init_node() {
  
  for( int i = 0 ; i < node_count ; i++ ) {
    Node[i].visit = false;
  }
  
} // init_node()

void intoNode( vector<string> & stack, string node_name ) {
  
  for( int i = 0 ; i < node_count ; i++ ) {
    if( Node[i].name == node_name ) {
      if( Node[i].last == "" ) {
        Node[i].length = 0;
        intoVec( stack, node_name, i );
      }
      else {
        intoVec( stack, node_name, i );
      }
      Node[i].visit = true;
      i = node_count;
    }
  }
  
  stack.erase( stack.begin() );
  
  
} // into_node

void intoVec( vector<string> & stack, string node_name, int i ) {
  
  for ( int j = 0 ; j < vec_count ; j++ ) {
    
    if ( Vec[j].start == node_name ) {
      
      int temp = Node[i].length + Vec[j].length;
      int endNode = getNodeLen( Vec[j].end );
      
      if ( temp < Node[endNode].length ) {
        Node[endNode].length = temp;
        Node[endNode].last = Node[i].name;
      }
      
      if( findsameNode( stack, Vec[j].end ) == false ) {
        if ( Node[endNode].visit == false ) {
          stack.push_back( Vec[j].end );
          
        }
      }
      
      
    }
    
  }
  
} // intoVec()

int getNodeLen( string node_name ) {
  
  
  for( int i = 0 ; i < node_count ; i++ ) {
    if( Node[i].name == node_name ) {
      return i;
    }
  }
  return -1;
} // getNodeLen

bool findsameNode( vector<string> stack, string node_name ) {
  for( int i = 0 ; i < stack.size() ; i++ ) {
    if( stack[i] == node_name )
      return true;
  }
  return false;
} // findsameNode()

void printNode() {
  for( int i = 0 ; i < node_count ; i++ ) {
    cout << Node[i].name << " " << Node[i].last << " " << Node[i].length << endl;
  }
  
  cout << "======" <<endl;
} // printNode()

void printShortAns( string node_name ) {
  for( int i = 0 ; i < node_count ; i++ ) {
    if( Node[i].name == node_name ) {
      cout << node_name << " ";
      printShortAns( Node[i].last );
      
    }
  }
  
  cout << endl ;
}

