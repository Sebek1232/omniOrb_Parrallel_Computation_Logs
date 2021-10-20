// eg2_impl.cc - This is the source code of example 2 used in Chapter 2
//               "The Basics" of the omniORB user guide.
//
//               This is the object implementation.
//
// Usage: eg2_impl
//
//        On startup, the object reference is printed to cout as a
//        stringified IOR. This string should be used as the argument to
//        eg2_clt.
//

#include <log_parser.hh>

#ifdef HAVE_STD
#  include <iostream>
#  include <vector>
#  include <fstream>
   using namespace std;
#else
#  include <iostream.h>
#endif

vector<string> vector_of_logs = {};

//object interface implementation
class Log_Parser_i : public POA_Log_Parser
{
public:
  inline Log_Parser_i() {}
  virtual ~Log_Parser_i() {}
  virtual char* getLogLine(const int pos);
};

//returns line in log file specified by pos
char* Log_Parser_i::getLogLine(const int pos)
{
  const char* line = vector_of_logs[pos].c_str();
  return CORBA::string_dup(line);
}

//fills shared vector of logs from log file
void fillVector(vector<string> &log_vector, string file)
{
  ifstream logs;
  logs.open(file);
  string tp;
  while(getline(logs, tp))
  {
    log_vector.push_back(tp);
  }
  logs.close();
}
void splitVector(int split)
{

}
//////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  fillVector(vector_of_logs, "logs.txt");
  try {
    //create corba object and create server
    CORBA::ORB_var          orb = CORBA::ORB_init(argc, argv);
    CORBA::Object_var       obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
    cout<< "cobra server created" << endl;
    
    //create log_parser servant 
    PortableServer::Servant_var<Log_Parser_i> myParser = new Log_Parser_i();
    cout << "log_parser servant created" << endl;

    //activate object  
    PortableServer::ObjectId_var myparserId = poa->activate_object(myParser);
    cout << "log_parser activated" << endl;

    // Obtain a reference to the object, and print it out as a
    // stringified IOR.
    obj = myParser->_this();
    Log_Parser_var parserRef = Log_Parser::_narrow(obj);

    cout << "stringified IOR reference to Object:" << endl << endl;
    
    CORBA::String_var sior(orb->object_to_string(obj));
    cout << sior << endl << endl;

    //activate POA manager 
    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    cout << "POA manager activated" << endl;
    cout << "server about to run" << endl;

    //run server
    orb->run();
  }
  catch (CORBA::SystemException& ex) {
    cerr << "Caught CORBA::" << ex._name() << endl;
  }
  catch (CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  return 0;
}
