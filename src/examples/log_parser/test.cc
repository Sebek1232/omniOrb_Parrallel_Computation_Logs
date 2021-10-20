//testing one helper funciton from each task since logic is the same
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
            cout << "before regex" << endl;
            if(regex_search(words[5], regex(words[8])))
                return sum+1;
            else
                return sum;
        }
        return sum;
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
};

int main(int argc, char** argv)
{
    test Test;
    Test.test1();
    return 0;
}