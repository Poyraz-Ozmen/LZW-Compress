 #include <string>
 #include <map>
 #include <iostream>
 #include <iterator>
 #include <vector>
 #include <fstream>
 #include <iterator>
 #include <string>
 #include <cstdlib>
#include <sstream>
 
 using namespace std;
 
template <typename Iterator>
 string decompress_data(Iterator begin, Iterator end) 
{
  // Building the dictionary.
  int myDictionary_Size2 = 256;
  map<int,string> values_dic2;
  for (int i = 0; i < 256; i++)
    values_dic2[i] = string(1, i);
 
  string dummy_str(1, *begin++);
  string result = dummy_str;
  string cin_value; //entry
  for ( ; begin != end; begin++) {
    int aa = *begin;
    if (values_dic2.count(aa))
      cin_value = values_dic2[aa];
    else if (aa == myDictionary_Size2)
      cin_value = dummy_str + dummy_str[0]; //entry=cin_value
    else
      throw "Something wrong with compression"; //if it goes wrong
 
    result =result +  cin_value;
 
    // Dictionary Update
    values_dic2[myDictionary_Size2++] = dummy_str + cin_value[0];
 
    dummy_str = cin_value;
  }
  return result;
}

 // not necessary we are doing decompression
template <typename Iterator>
Iterator compress_data(const string &uncompressed, Iterator result) {
  // Building the dictionary.
  int myDictionary_Size = 256;                                     
  map<string,int> values_dic;                 
  for (int i = 0; i < 256; i++)        // I trust ASCII
    values_dic[string(1, i)] = i;
 
  string storage_string;
 
  for (string::const_iterator my_iter = uncompressed.begin();
       my_iter != uncompressed.end(); ++my_iter) {
    char c = *my_iter;
    string storage_string_modify = storage_string+ c;
    if (values_dic.count(storage_string_modify))
      storage_string = storage_string_modify;
    else { 
    //Inserting new data into dictionary
      *result++ = values_dic[storage_string];      
      values_dic[storage_string_modify] = myDictionary_Size++;
      storage_string = string(1, c);
    }
  }
 
  // Output the code for storage_string incase it is left out
  if (!storage_string.empty())
    *result++ = values_dic[storage_string];
  return result;
} 
 

int main() {
       
     string main_str="";
   string line1;
 
  ifstream input ("compout.txt");
  if (input.is_open())
  {
    while ( getline (input,line1) )
    {
      main_str=main_str+line1;
    }
    
    input.close(); // ne olur ne olmaz
  } 

  else
  {
  cout << "File is not opening"<<endl; 
  return 0;
  }
  
  /****************************************DECOMPRESSION**************************************************/
  
  vector<int> compressed;
  stringstream iss( main_str );

	int number;
	//vector<int> myNumbers; // not necessary
	while ( iss >> number )
	{
  compressed.push_back( number );
	}
	cout <<"DECOMPRESS STARTED....\n\n";  
  string str_decompression_data = decompress_data(compressed.begin(), compressed.end());

 //writing the decompressed data to a file
  ofstream decomp_outfile;
  decomp_outfile.open ("decompout.txt");
  decomp_outfile<<str_decompression_data; 
  decomp_outfile.close();  
  cout << "DECOMPRESS FINISHED\n\n";


  
   



  return 0;
}


  