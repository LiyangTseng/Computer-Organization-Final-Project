#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#include<sys/time.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
using namespace std;

//-----------------------DO NOT CHANGE NAMES, ONLY MODIFY VALUES--------------------------------------------

//Final Values that will be compared for correctness
//You may change the function prototypes and definitions, but you need to present final results in these arrays
//-----------------------------Structures for correctness check-------------------
int **SA_Final_student;
int **L_counts_student;
char *L_student;
// int F_counts_student[]={0,0,0,0};
int C[]={0,0,0,0,0};//C[c] = total # of text characters which are alphabetically smaller than c
map<char, int> charIndex = {
    {'$',0},
    {'A',1},
    {'C',2},
    {'G',3},
    {'T',4}
};
//--------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------


//-----------------------DO NOT CHANGE--------------------------------------------

int read_count = 0;
int read_length = 0;
/*
int **SA_Final;
int **L_counts;
char *L;
int F_counts[]={0,0,0,0};
*/

//Read file to get reads
void inputReads(vector<string> &reads, string &file_path){
    fstream read_file(file_path);
    int ch, lines=0;
    string line;
    while (read_file>>line)
    {
        line += '$';
        reads.push_back(line);
    }
    read_count = reads.size();
    read_length = reads[0].length();
}

//Check correctness of values
/*
int checker(){
    int correct = 1;
    for(int i=0; i<read_count*read_length;i++){
        if(L_student[i]!=L[i])
            correct = 0;
        for(int j=0;j<2;j++){
            if(SA_Final_student[i][j]!=SA_Final[i][j])
                correct = 0;
        }
        for(int j=0;j<4;j++){
            if(L_counts_student[i][j]!=L_counts[i][j])
                correct = 0;
        }
    }
    for(int i=0;i<4;i++){
        if(F_counts_student[i]!=F_counts[i])
            correct = 0;
    }
    return correct;
}
*/

//Generate Sufixes and their SA's for a read
void generateSuffixes(vector<vector<string>> &suffixes, vector<string> &reads){
    // vector<string> suffixes;
    for (int i=0; i<read_count; i++)
    {
        vector<string> suffixesOfOneString;
        for (int j=0; j<read_length; j++)
        {
            string s = reads[i];
            //Rotate read by 1 character using std::rotate()
            rotate(s.begin(), s.begin() + j, s.end());
            suffixesOfOneString.push_back(s);
        }
        suffixes.push_back(suffixesOfOneString);
    }
}

//Calculates the final FM-Index
/*
int** makeFMIndex(vector<vector<string>> suffixes, int read_count, int read_length, int F_count[], char *L){
    int i, j;

    SA_Final = new int*[read_count*read_length];
    for (int i=0; i<read_count*read_length; i++)
        SA_Final[i] = new int[2];

    //Temporary storage for collecting together all suffixes
    vector<string> temp_suffixes;//(read_count*read_length);

    //Initalization of temporary storage
    for(i=0;i<read_count;i++){
        for(j=0;j<read_length;j++){
            temp_suffixes.push_back(suffixes[i][j]);
            
            SA_Final[i*read_length+j][0]=j; //index of string position 
            SA_Final[i*read_length+j][1]=i; //index of string number
        }
    }
    
    string temp;
    
    int** L_count = new int*[read_length*read_count];
    for (int i=0; i<read_length*read_count; i++)
    {
        L_count[i] = new int[4];
        for(j=0;j<4;j++){
            L_count[i][j]=0;
        }
    }

    //Focus on improving this for evaluation purpose
    //Sorting of suffixes
    for(i=0;i<read_count*read_length-1;i++){
        for(j=0;j<read_count*read_length-i-1;j++){
            if(temp_suffixes[j].compare(temp_suffixes[j+1])>0){
                temp = temp_suffixes[j];
                temp_suffixes[j] = temp_suffixes[j+1];
                temp_suffixes[j+1] = temp;
                int temp_int = SA_Final[j][0];
                SA_Final[j][0]=SA_Final[j+1][0];
                SA_Final[j+1][0]=temp_int;
                temp_int = SA_Final[j][1];
                SA_Final[j][1]=SA_Final[j+1][1];
                SA_Final[j+1][1]=temp_int;
            }
        }
    }

    char this_F = '$';
    j=0;
    
    //Calculation of F_count's
    for(i=0;i<read_count*read_length;i++){
        int count=0;
        while(temp_suffixes[i][0]==this_F){
            count++;i++;
        }
        F_count[j++]=j==0?count:count+1;
        this_F = temp_suffixes[i][0];
        if(temp_suffixes[i][0]=='T')
            break;
    }
    
    //Calculation of L's and L_count's
    for(i=0;i<read_count*read_length;i++){
        char ch = temp_suffixes[i][read_length-1];
        L[i]=ch;
        if(i>0){
            for(int k=0;k<4;k++)
                L_count[i][k]=L_count[i-1][k];//cumulate counts from previous results
        }
        if(ch=='A')
            L_count[i][0]++;
        else if(ch=='C')
            L_count[i][1]++;
        else if(ch=='G')
            L_count[i][2]++;
        else if(ch=='T')
            L_count[i][3]++;
    }

    return L_count;
}
*/

//Calculates the final FM-Index -- student version
// void makeFMIndex_student(vector<vector<string>>& suffixes, int (&F_count)[4], char * (&L)){
void makeFMIndex_student(vector<vector<string>>& suffixes, char * (&L)){

    int i, j;

    SA_Final_student = new int*[read_count*read_length];
    for (int i=0; i<read_count*read_length; i++)
        SA_Final_student[i] = new int[2];

    //Temporary storage for collecting together all suffixes
    vector<string> temp_suffixes(read_count*read_length);

    //Initalization of temporary storage
    for(i=0;i<read_count;i++){
        for(j=0;j<read_length;j++){
            temp_suffixes[i*read_length+j] = suffixes[i][j];
            SA_Final_student[i*read_length+j][0]=j;
            SA_Final_student[i*read_length+j][1]=i;
        }
    }
    
    string temp;
    L_counts_student = new int*[read_length*read_count];
    for (int i=0; i<read_length*read_count; i++)
    {
        L_counts_student[i] = new int[5];
        for(j=0;j<5;j++){
            L_counts_student[i][j]=0;
        }
    }
    vector<pair<string, int*> >pairs;
    for (int i=0; i<read_count*read_length; i++)
        pairs.push_back(make_pair(temp_suffixes[i], SA_Final_student[i]));
    
    //Focus on improving this for evaluation purpose
    //Sorting of suffixes
    sort(pairs.begin(), pairs.end(), 
    [](pair<string, int*> &p1, pair<string, int*> &p2) -> bool{ 
        return p1.first<p2.first; 
    });

    for (int i=0; i<read_count*read_length; i++)
    {
        temp_suffixes[i] = pairs[i].first;
        SA_Final_student[i] = pairs[i].second;
    }
/*
    cout << endl;
    for (int i=0; i<temp_suffixes.size(); i++)
        cout << temp_suffixes[i] << endl;
    cout << endl;
*/
    char this_F = '$';
    j=0;
    
    //Calculation of L's and L_counts_student's
    for(i=0;i<read_count*read_length;i++){
        char ch = temp_suffixes[i][read_length-1];
        L_student[i]=ch;
        if(i>0){
            for(int k=0;k<5;k++)
                L_counts_student[i][k]=L_counts_student[i-1][k];
        }
        L_counts_student[i][charIndex.find(ch)->second]++;
    }
}

//-----------------------DO NOT CHANGE--------------------------------------------

int main(int argc, char *argv[])
{
    string read_data_file= "P10000.txt";   // input DATA

    vector<string> reads;
    inputReads(reads, read_data_file);//Input reads from file

    // vector<vector<string>> suffixes;
    vector<vector<string>> suffixes_student;

    //-----------------------------Structures for correctness check----------------------------------------------
    // L=(char*)malloc(read_count*read_length*sizeof(char*));//Final storage for last column of sorted suffixes
    L_student=(char*)malloc(read_count*read_length*sizeof(char*));//Final storage for last column of sorted suffixes
    //-----------------------------Structures for correctness check----------------------------------------------
    

    //-----------Default implementation----------------
    //-----------Time capture start--------------------
    struct timeval  TimeValue_Start;
    struct timeval  TimeValue_Final;
    struct timezone TimeZone_Start;
    struct timezone TimeZone_Final;
    long time_start, time_end;
    double time_overhead_default, time_overhead_student;

   //Generate read-wise suffixes
/*    
    gettimeofday(&TimeValue_Start, &TimeZone_Start);

    generateSuffixes(suffixes, reads);
    //Calculate finl FM-Index
    L_counts = makeFMIndex(suffixes, read_count, read_length, F_counts, L);
    
    gettimeofday(&TimeValue_Final, &TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead_default = (time_end - time_start)/1000000.0;
    cout << "time_overhead_default" << time_overhead_default << "seconds" << endl;
    //------------Time capture end----------------------
    
*/
    //--------------------------------------------------

    string queryString;//string to search
    cout << "enter your query" << endl;
    cin >> queryString;
    // -----------Your implementations------------------
    gettimeofday(&TimeValue_Start, &TimeZone_Start); 
    //-----------Call your functions here--------------------

    // Generate read-wise suffixes
    generateSuffixes(suffixes_student, reads);
    
    //Calculate finl FM-Index
    makeFMIndex_student(suffixes_student, L_student);
    
    //----------------For debug purpose only-----------------
/*  
    for(int i=0;i<read_count*read_length;i++)        
        cout<<L_student[i]<<"\t"<<SA_Final_student[i][0]<<","<<SA_Final_student[i][1]<<"\t"<<L_counts_student[i][0]<<","<<L_counts_student[i][1]<<","<<L_counts_student[i][2]<<","<<L_counts_student[i][3]<<","<<L_counts_student[i][4]<<endl;
*/
    //--------------------------------------------------
    C[1] = L_counts_student[read_count*read_length-1][0];//A=moneysign
    C[2] = C[1]+L_counts_student[read_count*read_length-1][1];//C=moneysign+A
    C[3] = C[2]+L_counts_student[read_count*read_length-1][2];//G=moneysign+A+C
    C[4] = C[3]+L_counts_student[read_count*read_length-1][3];//G=moneysign+A+C+G
    
/*
    cout << endl;
    cout << "C table:" <<  endl;
    for (int i=0; i<5; i++)
        cout << C[i] << " ";
    cout << endl;
    cout << endl;
*/
    int i = 0;
    int j = read_count*read_length-1;
    char c = queryString[queryString.length()-1];
    i = C[charIndex.find(c)->second] + 0;
    j = C[charIndex.find(c)->second] + L_counts_student[j][charIndex.find(c)->second]-1;

    if (i < j)
    {
        for (int k=queryString.length()-2; k>=0; k--)
        {
            c = queryString[k];
            i = C[charIndex.find(c)->second] + L_counts_student[i-1][charIndex.find(c)->second];
            j = C[charIndex.find(c)->second] + L_counts_student[j][charIndex.find(c)->second]-1;
        
            if (i >= j)
                break;
            // cout << i << "~" << j << endl;
        }

    }
/*
    if (i<j)
        cout << "occurence at index " << i << "~" << j << endl;
    else if (i==j)
        cout << "occurence at index " << i << endl;
    else
        cout << "no occurence" << endl;    
*/
    vector<int> counter;
    for (int k=i; k<=j; k++)
    {
        //concept: if SA_Final_student[k][1] is new => increment counter 
        //might be the key of performance!!
        //https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object
        if(std::find(counter.begin(), counter.end(), SA_Final_student[k][1]) == counter.end()) 
            counter.push_back(SA_Final_student[k][1]);

    }
    //-----------Call your functions here--------------------
    gettimeofday(&TimeValue_Final, &TimeZone_Final);


    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead_student = (time_end - time_start)/1000000.0;
    cout << "number of occurences: " << counter.size() << endl;
    cout << "time_overhead_student" << time_overhead_student << "seconds" << endl;
    //--------------------------------------------------

    //---------------Correction check and speedup calculation----------------------
/*
    float speedup=0.0;
    if(checker()==1)
       speedup = time_overhead_default/time_overhead_student;
    cout<<"Speedup="<<speedup<<endl;
    //-----------------------------------------------------------------------------
*/
    
    //dynamicallly free space
    for (int i=0; i<read_count*read_length; i++)
    {
        // delete []SA_Final[i];
        delete []SA_Final_student[i];
    }
    // delete []SA_Final;
    delete []SA_Final_student;

    return 0;
}
