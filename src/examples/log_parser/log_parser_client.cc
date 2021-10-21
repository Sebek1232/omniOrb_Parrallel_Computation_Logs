// eg2_clt.cc - This is the source code of example 2 used in Chapter 2
//              "The Basics" of the omniORB user guide.
//
//              This is the client. The object reference is given as a
//              stringified IOR on the command line.
//
// Usage: eg2_clt <object reference>
//
#include <log_parser.hh>

#ifdef HAVE_STD
#  include <iostream>
#  include <vector>
#  include <fstream>
#  include <regex>
#  include <numeric> 
#  include <map>
   using namespace std;
#else
#  include <iostream.h>
#endif


//returns a vector of words that make up a log line
const vector<string> tokenizeLogLine(char* log)
{
  vector<string> words = {};
  char* token = strtok(log, " ");
  while(token != NULL)
  {
    string str_token(token);
    words.push_back(str_token);
    token = strtok(NULL, " ");
  }
  return words;
}

//write to file used by task 1
const void writeToCsvFile(string fileName, string type, string start, string end, string num)
{
  ofstream task1;
  task1.open(fileName, ios::app);
  task1 << type << "," << start << "," << end << "," << num << endl;
  task1.close();
}

//write to file used by task 4
const void writeToCsvFileTask4(string fileName, string type, string num)
{
  ofstream task1;
  task1.open(fileName, ios::app);
  task1 << type << "," << num << endl;
  task1.close();
}


const void writeLinesToCsvFile(string fileName, string time, string numOfError)
{
  ofstream task2;
  task2.open(fileName, ios::app);
  task2 << time << ", " << numOfError << endl;
  task2.close();
}

//write to file used by task 3
const void writeNumOfTypes(string fileName, string type, string num)
{
  ofstream task3;
  task3.open(fileName, ios::app);
  task3 << type << "," << num << endl;
  task3.close();
}

//converts time in log file to a integer
const int convertTimeToInt(string time)
{
  time.erase(remove(time.begin(), time.end(), ':'), time.end());
  time.erase(remove(time.begin(), time.end(), '.'), time.end());
  return atoi(time.c_str());
}

//next 4 fucntions are helper functions for task 1 to accumulate
//the sum of each log message type within a specfied time interval
const int sumOfErrorInInterval(int sum, vector<string> words)
{
  if(words[0] > words[6] && words[0] < words[7] && words[2] == "ERROR")
  {
    if(regex_search(words[5], regex(words[8])))
        return sum+1;
    else
        return sum;
  }
  return sum;
}
const int sumOfWarnInInterval(int sum, vector<string> words)
{
  if(words[0] > words[6] && words[0] < words[7] && words[2] == "WARN")
   if(regex_search(words[5], regex(words[8])))
        return sum+1;
    else
        return sum;

  return sum;
}
const int sumOfInfoInInterval(int sum, vector<string> words)
{
  if(words[0] > words[6] && words[0] < words[7]  && words[2] == "INFO")
    {
      if(regex_search(words[5], regex(words[8])))
        return sum+1;
      else
        return sum;
    }
  return sum;
}
const int sumOfDebugInInterval(int sum, vector<string> words)
{
  if(words[0] > words[6] && words[0] < words[7] && words[2] == "DEBUG")
    {
      if(regex_search(words[5], regex(words[8])))
        return sum+1;
      else
        return sum;
    }
  return sum;
}

//task1: accumualte the number of each message type in the log database within a specfied interval.
const void task1(Log_Parser_var parserRef, string start, string end, int startLine, int endLine, int client, string reg)
{
    vector<vector<string>> lines;
    string fileName = "task1_client" + to_string(client);
    remove(fileName.c_str());
    for (CORBA::ULong count=startLine; count<endLine; count++)
    { 
     CORBA::String_var line = parserRef->getLogLine(count);
     string str_line((char*)line);
     vector<string> words = tokenizeLogLine((char*)line);
     words.push_back(start);
     words.push_back(end);
     words.push_back(reg);
     lines.push_back(words);
    }
    const int num_of_error = accumulate(lines.begin(), lines.end(), 0, sumOfErrorInInterval);
    const int num_of_info = accumulate(lines.begin(), lines.end(), 0, sumOfInfoInInterval);
    const int num_of_warn = accumulate(lines.begin(), lines.end(), 0, sumOfWarnInInterval);
    const int num_of_debug = accumulate(lines.begin(), lines.end(), 0, sumOfDebugInInterval);
    writeToCsvFile(fileName, "ERROR", start, end, to_string(num_of_error));
    writeToCsvFile(fileName, "INFO", start, end, to_string(num_of_info));
    writeToCsvFile(fileName, "WARN", start, end, to_string(num_of_warn));
    writeToCsvFile(fileName, "DEBUG", start, end, to_string(num_of_debug));
}

void task2(Log_Parser_var parserRef, int startLine, int endLine, int client, string reg)
{
  vector<vector<string>> lines;
  const int timeInterval = 10000; 
  const string fileName = "task2_client" + to_string(client);
  remove(fileName.c_str());
  for (CORBA::ULong count=startLine; count<endLine; count++)
  { 
    CORBA::String_var line = parserRef->getLogLine(count);
    string str_line((char*)line);
    vector<string> words = tokenizeLogLine((char*)line);
    words.push_back(reg);
    lines.push_back(words);
  }

  int curStart = convertTimeToInt(lines[0][0]);
  int numOfErrors = 0;
  for(vector<string> v : lines)
  {
    const int time = convertTimeToInt(v[0]);
    if(time - curStart > timeInterval)
    {
      const string interval = to_string(curStart) + " + " + to_string(timeInterval);
      writeLinesToCsvFile(fileName, interval, to_string(numOfErrors));
      curStart = time; 
      numOfErrors = 0;
    }
    if(v[2] == "ERROR" && regex_search(v[5], regex(v[6])))
      numOfErrors++;
  }
}

//next 4 fucntions are helper functions for task 3 to accumulate
//the sum of each log message type
const int sumOfError(int sum, vector<string> words)
{
  if(words[2] == "ERROR" && regex_search(words[5], regex(words[6])))
      return sum+1;
    else
      return sum;
}
const int sumOfWarn(int sum, vector<string> words)
{
  if(words[2] == "WARN" && regex_search(words[5], regex(words[6])))
      return sum+1;
    else
      return sum;
}
const int sumOfInfo(int sum, vector<string> words)
{
  if(words[2] == "INFO" && regex_search(words[5], regex(words[6])))
      return sum+1;
    else
      return sum;
}
const int sumOfDebug(int sum, vector<string> words)
{
  if(words[2] == "DEBUG" && regex_search(words[5], regex(words[6])))
      return sum+1;
    else
      return sum;
}

//task3: accumualte the number of each message type in the log database.
const void task3(Log_Parser_var parserRef, int startLine, int endLine, int client, string reg)
{
  string fileName = "task3_client" + to_string(client);
  remove(fileName.c_str());
  vector<vector<string>> lines;
  for (CORBA::ULong count=startLine; count<endLine; count++)
  { 
     CORBA::String_var line = parserRef->getLogLine(count);
     string str_line((char*)line);
     vector<string> words = tokenizeLogLine((char*)line);
     words.push_back(reg);
     lines.push_back(words);
  }
  
  const int num_of_error = accumulate(lines.begin(), lines.end(), 0, sumOfError);
  const int num_of_info = accumulate(lines.begin(), lines.end(), 0, sumOfInfo);
  const int num_of_warn = accumulate(lines.begin(), lines.end(), 0, sumOfWarn);
  const int num_of_debug = accumulate(lines.begin(), lines.end(), 0, sumOfDebug);
  writeNumOfTypes(fileName, "ERROR", to_string(num_of_error));
  writeNumOfTypes(fileName, "INFO", to_string(num_of_info));
  writeNumOfTypes(fileName, "WARN", to_string(num_of_warn));
  writeNumOfTypes(fileName, "DEBUG", to_string(num_of_debug));
}

//next 4 functions are helper functions to find the largest character log
//message of each log type
const int highOfError(int high, vector<string> words)
{
 if(words[2] == "ERROR" && regex_search(words[5], regex(words[6]))) 
    {
       if(words[5].size() > high)
           return words[5].size();
       else 
           return high;
    }
  return high;
}
const int highOfWarn(int high, vector<string> words)
{
   if(words[2] == "WARN" && regex_search(words[5], regex(words[6]))) 
    {
       if(words[5].size() > high)
           return words[5].size();
       else 
           return high;
    }
  return high;
}
const int highOfInfo(int high, vector<string> words)
{
   if(words[2] == "INFO" && regex_search(words[5], regex(words[6]))) 
    {
       if(words[5].size() > high)
           return words[5].size();
       else 
           return high;
    }
  return high;
}
const int highOfDebug(int high, vector<string> words)
{
   if(words[2] == "DEBUG" && regex_search(words[5], regex(words[6]))) 
    {
       if(words[5].size() > high)
           return words[5].size();
       else 
           return high;
    }
  return high;
}

//task4: find the largest number of characters of log messages
//for each log type. 
const void task4(Log_Parser_var parserRef, int startLine, int endLine, int client, string reg)
{
  vector<vector<string>> lines;
  string fileName = "task4_client" + to_string(client);
  remove(fileName.c_str());
  for (CORBA::ULong count=startLine; count<endLine; count++)
  { 
     CORBA::String_var line = parserRef->getLogLine(count);
     string str_line((char*)line);
     vector<string> words = tokenizeLogLine((char*)line);
     words.push_back(reg);
     lines.push_back(words);
  }
  const int highest_char_error = accumulate(lines.begin(), lines.end(), 0, highOfError);
  const int highest_char_info = accumulate(lines.begin(), lines.end(), 0, highOfInfo);
  const int highest_char_warn = accumulate(lines.begin(), lines.end(), 0, highOfWarn);
  const int highest_char_debug = accumulate(lines.begin(), lines.end(), 0, highOfDebug);
  writeToCsvFileTask4(fileName, "ERROR", to_string(highest_char_error));
  writeToCsvFileTask4(fileName, "INFO", to_string(highest_char_info));
  writeToCsvFileTask4(fileName, "WARN", to_string(highest_char_warn));
  writeToCsvFileTask4(fileName, "DEBUG", to_string(highest_char_debug));
}



int main(int argc, char** argv)
{

  const string start(argv[2]);
  const string end(argv[3]);
  const int startLogLine = atoi(argv[4]);
  const int endLogLine = atoi(argv[5]);
  const int client = atoi(argv[6]);
  const string reg(argv[7]);

  try {

    cout << "intilizing corba object" << endl;
    //init Corba
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);


    cout<< "getting stringfied refrence to object" << endl;
    //get stringfied version of object provided by server
    CORBA::Object_var obj = orb->string_to_object(argv[1]);
    
    cout<< "converting stringfied object to object reference" << endl;
    //get refrenece to object recieved from server
    Log_Parser_var parserRef = Log_Parser::_narrow(obj);

    if (CORBA::is_nil(parserRef)) {
      cerr << "Can't narrow reference to type Log_Parser (or it was nil)." << endl;
      return 1;
    }

    cout<< "CORBA object refrence recieved" << endl;
    //client begins tasks

    cout<< "beginning task 1" << endl;
    task1(parserRef, start, end, startLogLine, endLogLine, client, reg);
    cout<< "beginning task 2" << endl;
    task2(parserRef, startLogLine, endLogLine, client, reg);
    cout<< "beginning task 3" << endl;
    task3(parserRef, startLogLine, endLogLine, client, reg);
    cout<< "beginning task 4" << endl;
    task4(parserRef, startLogLine, endLogLine, client, reg);
    orb->destroy();
    cout<< "task finished corba object destroyed" << endl;
  }
  catch (CORBA::TRANSIENT&) {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << endl;
  }
  catch (CORBA::SystemException& ex) {
    cerr << "Caught a CORBA::" << ex._name() << endl;
  }
  catch (CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  return 0;
}
