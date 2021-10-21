####omniORB Distributed Computing
# Sebastian Greczek
# AWS Deployment Video : https://youtu.be/RDzb-JpqSNM
## Installation

Download omniOrb from  [omniOrb](http://omniorb.sourceforge.net/download.html) 

Follow the instructions provided in the readme files of omniORB to compile on your desired OS.
Make sure you can run the examples in the omniORB directories to make sure everything was complied and linked correctly 

## How To Run This Program
Clone this repo on the machine that omniOrb resides.

Three directories need to be moved form this repo to the omniOrb repo:

githubRepo/build/src/examples/log_parser needs to be moved to omniORB/build/src/examples

githubRepo/idl/log_parser.idl needs to be moved to omniORB/idl

githubRepo/src/examples/log_parser needs to be moved to omniORB/src/examples

Once these files are moved to the omniORB directories navigate to omniORB/build/src/examples/log_parser

Open in terminal and run make

You can now execute ./log_parser_client and ./log_parser_server. More detailed instructions on these executable further down

To run tests navigate to omniOrb/src/examples/log_parser 
run gcc test.cc -lstdc++ to compile 

Then ./a.out to run tests.


## How It Works
two main cc files: log_parser_server.cc and log_parser_client.cc
### log_parser_server.cc
This file creates the CORBA object that will serve clients. Upon execution this server will print a stringified object reference
```cpp
// Obtain a reference to the object, and print it out as a
// stringified IOR.
obj = myParser->_this();
Log_Parser_var parserRef = Log_Parser::_narrow(obj);

cout << "stringified IOR reference to Object:" << endl << endl;
    
CORBA::String_var sior(orb->object_to_string(obj));
cout << sior << endl << endl;
```
The client will use this reference when binding to the server. The server holds the logging information and each client can specify what parts of the logging database it wants. 

### Object Interface:
```cpp
class Log_Parser_i : public POA_Log_Parser
{
public:
  inline Log_Parser_i() {}
  virtual ~Log_Parser_i() {}
  virtual char* getLogLine(const int pos);
};    
```
### Object idl:
```cpp
#ifndef __Log_Parser_IDL__
#define __Log_Parser_IDL__
interface Log_Parser {
  string getLogLine(in long pos);
};
#endif  
```
The object interface specifies what each client can reference with their object. In this case clients can make function call getLogLine between different address spaces.

A CORBA server can handle clients in parallel so multiple clients can do function calls at the same time

### log_parser_client
This is where all the work gets done. This executable ./log_parser_client will create a client process. This executable requires command line arguments in this format: 
```
./log_parser_client <CORBA IOR> <Start Interval> <End Interval> <Start Log> <End Log> <Client Num> <regex> 
```
<CORBA IOR> : stringified object reference

<Start Interval>, <End Interval> : Used for task 1 to specify what time interval we are looking for

<Start Log>, <End Log> : Partition of data on which the client will work on

<Client Num> : Used for naming output files.

<regex> : regex string that each task searches for in each task

#### Task 1 Output example
```
ERROR,02:11:00.403,02:11:58.569,3
INFO,02:11:00.403,02:11:58.56990,317
WARN,02:11:00.403,02:11:58.56984,95
DEBUG,02:11:00.403,02:11:58.56979,50
```
Distribution of log messages between the time interval specified that match the regex pattern specified.

(Type, start, end, number of logs)

#### Task 2 Output example
```
21038292 + 10000, 0
21048294 + 10000, 1
21058298 + 10000, 0
21100000 + 10000, 0
21110010 + 10000, 1
21120014 + 10000, 1
21130022 + 10000, 0
21140023 + 10000, 1
21150031 + 10000, 0
21200006 + 10000, 2
21210012 + 10000, 0
21220019 + 10000, 0
``` 
Number of ERROR logs between a designated time interval that match the regex pattern specified.

((start time + designated time interval), number of Error Messages)

#### Task 3 Output example
```
ERROR,7
INFO,661
WARN,187
DEBUG,96
``` 
Number of Logs of each type that that match the regex pattern specified.

(Type, number of Messages)

#### Task 4 Output example
```
ERROR,58
INFO,90
WARN,84
DEBUG,79
``` 
Highest Number of of character for each log type that matches the regex pattern specified 

(Type, Highest number of characters)


## Running Clients in Parallel 
```
./log_parser_client <CORBA IOR> <Start Interval> <End Interval> <Start Log> <End Log> <Client Num> <regex>
& ./log_parser_client <CORBA IOR> <Start Interval> <End Interval> <Start Log> <End Log> <Client Num> <regex>
& ... & ... & ... & etc.
```

#### Time Comparison
One Client doing all tasks
```
real    0m3.174s
user    0m2.089s
sys     0m0.401s
```
Four Clients doing 1/4 of the work in parallel 
```
real    0m0.788s
user    0m0.322s
sys     0m0.061s
```

## Function Programming in C++
The program mostly uses transform() and accumulate() on vectors to compute the task. The use of induction variables with for loops are necessary when passing data between server and client. COBRA only allows specific data types that can be recognized by the IDL complier. So for example a vector the IDL complier will not recognize so they can not be used in the interface implementation that the client receives a reference to. Upon receival of data from client the program uses induction variables to fill a vector in the client space so functional style functions can be later used to compute each task.       
