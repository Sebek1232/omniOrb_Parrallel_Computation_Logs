
#  include <regex>
#  include <iostream>
#  include <vector>
using namespace std;

class test 
{
  public:
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
    const int sumOfWarn(int sum, vector<string> words)
    {
        if(words[2] == "WARN" && regex_search(words[5], regex(words[6])))
            return sum+1;
        else
            return sum;
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
    const void test1()
    {
        cout << "running test 1" << endl;
        vector<string> errorLog = {"02:11:10.360", "[scala-execution-context-global-129]", "ERROR",
                               "HelperUtils.Parameters$", "-", 
                               "yk>*(m@1+9k^a.g*hp7zE{:uDZ2t&Zu?.Pa4JCH<}W[BH&}", "02:10:10.360", 
                               "02:12:10.360", "[A-Z]{3,}" };
        const int sum = sumOfErrorInInterval(0, errorLog);
        if(sum)
            cout << "test 1 PASSED" << endl;
        else
            cout << "test 1 FAILED:  INVAILD SUM" << endl;
    }
    const void test2()
    {
        cout << "running test 2" << endl;
        vector<string> errorLog = {"02:11:10.360", "[scala-execution-context-global-129]", "ERROR",
                               "HelperUtils.Parameters$", "-", 
                               "aaaaaaaaaaaaaaaaadddddddddddddddssssssssss", "02:10:10.360", 
                               "02:12:10.360", "[A-Z]{3,}" };
        const int sum = sumOfErrorInInterval(0, errorLog);
        if(!sum)
            cout << "test 1 PASSED" << endl;
        else
            cout << "test 1 FAILED:  INVAILD SUM" << endl;
    }
    const void test3()
    {
        cout << "running test 3" << endl;
        vector<string> warnLog = {"02:11:10.360", "[scala-execution-context-global-129]", "WARN",
                               "HelperUtils.Parameters$", "-", 
                               "yk>*(m@1+9k^a.g*hp7zE{:uDZ2t&Zu?.Pa4JCH<}W[BH&}", "[A-Z]{3,}" };
        const int sum = sumOfWarn(0, warnLog);
        if(sum)
            cout << "test 1 PASSED" << endl;
        else
            cout << "test 1 FAILED:  INVAILD SUM" << endl;
    }
    const void test4()
    {
        cout << "running test 4" << endl;
        vector<string> warnLog = {"02:11:10.360", "[scala-execution-context-global-129]", "WARN",
                               "HelperUtils.Parameters$", "-", 
                               "aavbvvccvvdsfasdfsa", "[A-Z]{3,}" };
        const int sum = sumOfWarn(0, warnLog);
        if(!sum)
            cout << "test 1 PASSED" << endl;
        else
            cout << "test 1 FAILED:  INVAILD SUM" << endl;
    }

    const void test5()
    {
        cout << "running test 5" << endl;
        vector<string> infoLog = {"02:11:10.360", "[scala-execution-context-global-129]", "INFO",
                               "HelperUtils.Parameters$", "-", 
                               "yk>*(m@1+9k^a.g*hp7zE{:uDZ2t&Zu?.Pa4JCH<}W[BH&}", "[A-Z]{3,}" };
        const int sum = highOfInfo(0, infoLog);
        if(sum)
            cout << "test 1 PASSED" << endl;
        else
            cout << "test 1 FAILED:  INVAILD SUM" << endl;
    }

    const void test6()
    {
        cout << "running test 6" << endl;
        vector<string> infoLog = {"02:11:10.360", "[scala-execution-context-global-129]", "INFO",
                               "HelperUtils.Parameters$", "-", 
                               "AS", "[A-Z]{3,}" };
        const int sum = highOfInfo(5, infoLog);
        if(sum)
            cout << "test 1 PASSED" << endl;
        else
            cout << "test 1 FAILED:  INVAILD SUM" << endl;
    }
};

int main(int argc, char** argv)
{
    test Test;
    Test.test1();
    Test.test2();
    Test.test3();
    Test.test4();
    Test.test5();
    Test.test6();
    return 0;
}