#include "resource.h"

// Database name & employee table name
//
const WCHAR IM_DEMO_APP_DATABASE[]      = L"IMDemoChatDB.sdf";
const WCHAR TABLE_EMPLOYEE[]        = L"UserTable";

// SQl to create and drop employee table
// must change table name in query too
const WCHAR SQL_CREATE_EMPLOYEES_TABLE[]  = L"CREATE TABLE UserTable (EmployeeID INT, LastName NVARCHAR(20), FirstName NVARCHAR(10), Address NVARCHAR(60), City NVARCHAR(15), Region NVARCHAR(15), PostalCode NVARCHAR(10), Country NVARCHAR(15), HomePhone NVARCHAR(24), Photo IMAGE)";
const WCHAR SQL_CREATE_EMPLOYEES_INDEX[]  = L"CREATE INDEX PK_UserTable on UserTable (EmployeeID ASC)";
// const WCHAR SQL_DROP_EMPLOYEES[]      = L"DROP TABLE UserTable";

// Employee data definition
//
typedef struct EmployeeData
{
  WCHAR* wszEmployeeInfo[9];
  DWORD  dwEmployeePhoto;
} EmployeeData;

// Sample employee data
//
EmployeeData g_SampleEmployeeData[] =
{
  {
    {
      L"1", 
      L"Davolio",
      L"Nancy",
      L"507 - 20th Ave. E. Apt. 2A",
      L"Seattle",
      L"WA",
      L"98122",
      L"USA",
      L"(206) 555-9857"
    },
    IDR_PHOTO_DAVOLIO
  },

  {
    {
      L"2", 
      L"Fuller",
      L"Andrew",
      L"908 W. Capital Way",
      L"Tacoma",
      L"WA",
      L"98401",
      L"USA",
      L"(206) 555-9482"
    },
    IDR_PHOTO_FULLER,
  },

  {
    {
      L"3",
      L"Leverling",
      L"Janet",
      L"722 Moss Bay Blvd.",
      L"Kirkland",
      L"WA",
      L"98033",
      L"USA",
      L"(206) 555-3412"
    },
    IDR_PHOTO_LEVERLING,
  },

  {
    {
      L"4",
      L"Peacock",
      L"Margaret",
      L"4110 Old Redmond Rd.",
      L"Redmond",
      L"WA",
      L"98052",
      L"USA",
      L"(206) 555-8122"
    },
    IDR_PHOTO_PEACOCK,
  },
  
  {
    {
      L"5",
      L"Buchanan",
      L"Steven",
      L"14 Garrett Hill",
      L"London",
      L"",
      L"SW1 8JR",
      L"UK",
      L"(71) 555-4848"
    },
    IDR_PHOTO_BUCHANAN,
  },

  {
    {
      L"6",
      L"Suyama",
      L"Michael",
      L"Coventry House Miner Rd.",
      L"London",
      L"",
      L"EC2 7JR",
      L"UK",
      L"(71) 555-7773"
    },
    IDR_PHOTO_SUYAMA,
  },

  {
    {
      L"7",
      L"King",
      L"Robert",
      L"Edgeham Hollow Winchester Way",
      L"London",
      L"",
      L"RG1 9SP",
      L"UK",
      L"(71) 555-5598"
    },
    IDR_PHOTO_KING,
  },

  {
    {
      L"8",
      L"Callahan",
      L"Laura",
      L"4726 - 11th Ave. N.E.",
      L"Seattle",
      L"WA",
      L"98105",
      L"USA",
      L"(206) 555-1189"
    },
    IDR_PHOTO_CALLAHAN,
  },

  {
    {
      L"9",
      L"Dodsworth",
      L"Anne",
      L"7 Houndstooth Rd.",
      L"London",
      L"",
      L"WG2 7LT",
      L"UK",
      L"(71) 555-4444"
    },
    IDR_PHOTO_DODSWORTH
  }
};
