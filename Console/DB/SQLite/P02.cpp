// Date: 12-28-2013
// ref, cp_sqitecpptest (from cp_SQLiteWithCPPDemo.zip)
// included following sources inside the dir
//  sqlite3.dll
//  sqlite3.h
//  sqlite3.lib
// linked against sqlite3.lib
// Output DB file Name: 'sea.s3db'
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "sqlite3.h"
#define DB "sea.s3db"

bool isOpenDB = false;
sqlite3 *dbfile;

bool ConnectDB ();
void DisonnectDB ();

class student
{
private:
  int id;
  string name;
  float cgpa;

public:
  student()
  {
    id=0;
    cgpa=0.00;
  }

  student(int i, string sname, float f)
  {
    id=i;
    name = sname;
    cgpa=f;
  }
  void setid(int i)
  {
    id=i;
  }
  void setcgpa(float gp)
  {
    cgpa=gp;
  }

  void setName(string sname)
  {
    name = sname;
  }

  string getName()
  {
    return name;
  }

  int getid()
  {
    return id;
  }
  float getcgpa()
  {
    return cgpa;
  }
};


student getStudent()
{
  student stud;

  int id;
  string name;
  float gpa;

  cout << " Enter Student id :" ;
  cin >> id;
  cout << " Enter Name : " ;
  cin >> name;
  cout << " Enter GPA : " ;
  cin >> gpa;

  stud.setid(id);
  stud.setName(name);
  stud.setcgpa(gpa);

  return stud;
}

int addDataRow()
{
  // get the student data from user 
  student stud = getStudent();
  // cout << stud.getName() << endl;
  std::stringstream strm;
  strm << "insert into student(roll,name,cgpa) values(" << stud.getid() << ",'" << stud.getName() << "'," << stud.getcgpa() << ")";

  string s = strm.str();
  char *str = &s[0];
  // cout << str << endl;
  
  sqlite3_stmt *statement;
  int result;
  // char *query="insert into student(roll,name,cgpa)values(4,'uuu',6.6)";
  char *query = str;
  {
    if(sqlite3_prepare(dbfile,query,-1,&statement,0)==SQLITE_OK)
    {
      int res=sqlite3_step(statement);
      result=res;
      sqlite3_finalize(statement);
    }
    return result;
  }

  return 0;
}



int updateRow()
{
  int rollno;
  float gpa;
  cout << "Enter ID No: ";
  cin >> rollno ;
  cout << "new CGPA : " ;
  cin >> gpa;

  std::stringstream strm;
  strm << "update student set cgpa=" << gpa << " where roll=" << rollno ;

  string s = strm.str();
  char *str = &s[0];
  // cout << str << endl;
  
  sqlite3_stmt *statement;
  int result;
  // char *query="update student set cgpa=3.66 where roll=11";
  char *query = str;  
  
  {
    if(sqlite3_prepare(dbfile,query,-1,&statement,0)==SQLITE_OK)
    {
      int res=sqlite3_step(statement);
      result=res;
      sqlite3_finalize(statement);
    }
    return result;
  }
  
  return 0;
}


int deleteRow()
{
  int rollno;

  cout << "Enter ID No: ";
  cin >> rollno ;
  
  std::stringstream strm;
  strm << "delete from student " << " where roll=" << rollno ;

  string s = strm.str();
  char *str = &s[0];
  //cout << str << endl;

  sqlite3_stmt *statement;
  int result;
  char *query = str;
  {
    if(sqlite3_prepare(dbfile,query,-1,&statement,0)==SQLITE_OK)
    {
      int res=sqlite3_step(statement);
      result=res;
      sqlite3_finalize(statement);
    }
    return result;
  }
  
  return 0;
}

void getTableData()
{
  sqlite3_stmt *statement;  

  char *query = "select * from student";

  if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
  {
    int ctotal = sqlite3_column_count(statement);
    int res = 0;

    while ( 1 )
    
    {
      res = sqlite3_step(statement);

      if ( res == SQLITE_ROW ) 
      {
        for ( int i = 0; i < ctotal; i++ ) 
        {
          string s = (char*)sqlite3_column_text(statement, i);
          cout << s << " " ;
        }

        cout << endl;
      }

      if ( res == SQLITE_DONE )  
      {
        cout << "done " << endl;
        break;
      }  
    }
  }
}


int main()
{
  isOpenDB = ConnectDB();

  if ( isOpenDB ) 
    cout << "Connected Successful" << endl;
  else cout << "connection failed " << endl;

  student st[100];
  while ( 1 ) 
  {
    int chioce;
    cout<<" Choose Operation " << endl;
    cout << "1. Add Student"  << endl;
    cout << "2. List student" << endl;
    cout << "3. Update student" << endl;
    cout << "4. Delete student" << endl;
    cout << "5. Exit " << endl;

    cout << "Enter Operation NO :  ";
    
    cin >> chioce ;
    
    if(chioce == 1)
    {
      int count = addDataRow();

      //cout << count << endl;
      if ( count == SQLITE_DONE ) 
      {
        cout << "insert successful" << endl;
      }
    }
    else if (chioce==2)
    {
      getTableData();
    }
    else if (chioce==3)
    {
      updateRow();
    }

    else if(chioce==4)
    {
      deleteRow();
    }
    else if ( chioce == 5 ) 
    {
      break;
    }

  }
  return 0;
}

bool ConnectDB ()
{
  if ( sqlite3_open(DB, &dbfile) == SQLITE_OK )
  {
    isOpenDB = true;
    return true;
  }     

  return false;
}

void DisonnectDB ()
{
  if ( isOpenDB == true ) 
  {
    sqlite3_close(dbfile);
  }
}
