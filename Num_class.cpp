# include <iostream>
//# include <string>
/* functions used from string class in longnum_calculator
	#str.length();
  	#str.push_back();
  	#str[] -> index based access
  	#str.reverse();
  	# str.begin(), str.end() -> optional 
  	#overload cin, cout
 */

using namespace std;


// NUM only stores integers
// optional check for '.' character 
// check for 0's in front   { NUM.clean() } 
// # NUM.clean();    009 -> 9 & -009 -> -9 
// NUM.reverse(); -> reverse the digits in the number

 

class NUM
{
private:
	char* head ;
	int num_length ;
	// int mem_length ;
	// bool neg;  -> value to denote whether the number is '+ve' or '-ve'
	// int system; -> represents the number system that the num belongs ( Default '10-Digit system' )
	
public:
	// as default the number is set to NULL and length = 0
	NUM()
	{
		head = NULL;
		num_length = 0;
	}

	// example: NUM ex(6) -> 6 digit number.
	NUM(int a)
	{
		head = new char[a + 1];
		num_length = a;
	}

	// example: NUM ex(".....")
	NUM(const char a[])
	{
		int length = 0;
		while (a[length] != '\0') {
			length = length + 1;
		}

		num_length = length;
		this->head = new char[length + 1];
		for (int i = 0; i < length + 1; i++) {
			this->head[i] = a[i];
		}
	}

	int size() { return this->num_length; }
	
	void print() { cout << "# size: " << num_length << ", value: " << head << endl; }

	
	// assign value to NUM_object, if value is already assigned the delete the prev memory 
	void operator= (const char a[])
	{
		if (this->head != NULL) 
		{
			delete this->head;
			this->head = NULL;
		}
		
		int length = 0;
		while (a[length] != '\0') {
			length = length + 1;
		}

		this->head = new char[length + 1];
		for (int i = 0; i < length + 1; i++) {
			this->head[i] = a[i];
		}
		num_length = length ;
	}

	// obj_name[i] -> return type ' char& ', ith element in the character array.
	char& operator[] (int index) 
	{
		if (index >= num_length)
		{
			cout << "Error: index of char_array in NUM is out of bound " << endl ;
			exit(0);
		}
		return head[index] ;
	}

	// for every new entry realloc the memory of the char array (size++)  
	void push_back(const char temp) 
	{
		if(temp != '\n')
		{
			head = (char*)realloc( head, (num_length + 2)*sizeof(char));
			head[num_length + 1] = '\0';
			head[num_length] = temp;
			num_length++;
		}
	}

	// swapping ith term from the start and end.
	void reverse() 
	{
		for(int i = 0; i < num_length/2; i++)
			swap( head[i], head[num_length - i - 1] );
	}

	// friend function declaration -> to enable the access to private members of the class 
	friend ostream & operator << (ostream &out, const NUM &i); 
    friend istream & operator >> (istream &in,  NUM &i);
};

// output to stream - defined in global scope 
ostream & operator << (ostream &out, const NUM &i) 
{ 
    out << i.head; 
    return out; 
} 
 // input from stream - define in global scope 
istream & operator >> (istream &in,  NUM &i) 
{ 
	delete i.head;
	char temp;
	do {
		temp = in.get();
		if (temp == '\n' || temp == ' ')
			break;
		i.push_back(temp);
	} while (true);

	return in;
}


int main() {
	/*
	NUM num1;
	char str[] = "123456789";
	num1 = str;
	num1.print();
	
	NUM num2(4);
	num2 = "-1522";
	num2.print(); 
	

	NUM num3("1998");
	num3.print();
	num3.reverse();
	num3.print();
	num3.push_back('7');
	num3.print();
	cout << num3 << endl;
	
	NUM num4;
	cin >> num4;
	cout << num4 << endl;
	*/

	return 0;
}
