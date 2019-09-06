# include <iostream>
# include <stdio.h>
//# include <NUM>
using namespace std;

class NUM
{
private:
	char* head ;
	int num_length ;
	// bool neg;  -> value to denote whether the number is '+ve' or '-ve'
	// int system; -> represents the number system that the num belongs ( Default '10-Digit system' )

public:
	// as default the number is "NULL"
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

	int length() { return this->num_length; }
	
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
	char temp;
	do {
		temp = in.get();
		if (temp == '\n' || temp == ' ')
			break;
		i.push_back(temp);
	} while (true);

	return in;
}

class longnum
{	
	private:
		NUM number;

	public: 
		longnum() //constructor: intial value is set to NULL
		{
			//cout << "constructor for longnum is called " << endl;
			number = "";
		}
		
		void print()
		{
			number.print();
		}
		
		void setvalue(NUM x)
		{
			number = x;
			//cout << "value of the longnum is set to : " << number << endl;
		}

		void setvalue() {
			cout << "Enter the number : ";
			cin >> number;
		}

		// addition of two longnum 
		longnum operator+ (const longnum &y)
		{
			longnum ans;
			NUM num1 = this->number, num2 = y.number;
			//check for 'NULL'
			if (num1[0] == 'N' || num2[0] == 'N') 
			{
				cout << "Error: one of the inputs is NULL .... " << endl;
				return ans;
			}

			// varibles to store wheather the numubers are "-ve" or not, initially assumed to be -ve
			int neg1 = 1, neg2 = 1;	
			if (num1[0] != '-') { neg1 = 0; }
			if (num2[0] != '-') { neg2 = 0; }
			//cout << "negtive number check ...." << endl;

			// check whether max integer is num1 or not, if not swap the values
			if ((num1.length() - neg1) < (num2.length() - neg2)) {
				num2 = this->number;
				num1 = y.number;
				int temp = neg1;
				neg1 = neg2;
				neg2 = temp;
			}
			// for NUMs of equal lenght, check the first digit
			else if ((num1.length() - neg1) == (num2.length() - neg2) && num1[neg1] < num2[neg2]) {
				num2 = this->number;
				num1 = y.number;
				int temp = neg1;
				neg1 = neg2;
				neg2 = temp;
			}
			//cout << "# max.num check finish ... " << endl;
 
			// check whether the final ans is '-ve' or not, 'neg_ans' is used to store the value
			// and neg represents substraction as a special case of addition 
			int neg = (neg2 + neg1) % 2;
			int neg_ans = 0;
			if (neg1 == 1) {
				neg_ans = 1;
			}

			NUM sum; 
			int l1 = (num1.length() - neg1) , l2 = (num2.length() - neg2) ; 
			int diff = l1 - l2;
			int carry = 0 , temp_sum = 0;

			//neg1 = 0, neg2 = 0, neg = 0, neg_ans = 0, carry = 0;
			//cout << neg1 << " " << neg2 << " " << ", neg_ans : " << neg_ans <<" , " << neg <<  endl;
			for (int i = l2 - 1; i >= 0; i--) {
				temp_sum = (num1[i + neg1 + diff] - '0') + (1 -2*neg)*(num2[i + neg2] - '0') + carry;
				sum.push_back((temp_sum + 10) % 10 + '0');
				carry = ((temp_sum + 10 ) / 10) - 1;
			}

			for (int i = diff - 1; i >= 0; i--) {
				temp_sum = (num1[i + neg1] - '0') + carry;
				sum.push_back((temp_sum + 10) % 10 + '0');
				carry = ((temp_sum + 10) / 10) - 1;
			}
			if (carry != 0) {
				sum.push_back(carry + '0');
			}

			if (neg_ans == 1) {
				sum.push_back('-');
			}
			sum.reverse();
			ans.setvalue(sum);

			return ans;
		}

		// multiplication of two longnum
		longnum operator* (const longnum &y) 
		{			
			longnum ans;
			NUM num1 = this->number , num2 = y.number ;

			// check for 'NULL'			 
			if (num1[0] == 'N' || num2[0] == 'N')
			{
				cout << "Error: one of the inputs is NULL .... " << endl;
				return ans;
			}
						 
			// checking for negative numbers 
			int neg1 = 1, neg2 = 1;
			if (num1[0] != '-') { neg1 = 0; }
			if (num2[0] != '-') { neg2 = 0; }
			 
			int neg_ans = (neg1 + neg2)%2 ; 

			// check for 'zero' 
			if (num1[0 + neg1] == '0' || num2[0 + neg2] == '0') {
				ans.setvalue("0");
				return ans;
			}
			
			int l1 = (num1.length() - neg1), l2 = (num2.length() - neg2);
			int diff = l1 -l2 ;
			if (diff < 0) {
				diff = (-1)*diff; 
			}

			longnum digit_multi;
			ans.number = "";
			int temp_multi , carry = 0;
			//int itr = 0;
			// logic for multiplication 

			 
			//cout << "for loop multiplication" << endl;
			for( int i = l2 - 1 + neg2; i >= 0 + neg2; i--) {
				int digit = (num2[i] - '0');
				cout << digit << " in loop itrno: " << i << endl;
				digit_multi.number = "" ;
				for (int j = l1 - 1 + neg1; j >= 0 + neg1; j--) {
					int work_digit = (num1[j] - '0');
					cout << work_digit << " < work digit inner itr; " << j << endl;
					int temp_multi = work_digit * digit + carry;
					digit_multi.number.push_back((temp_multi % 10) + '0'); 
					carry = temp_multi / 10;
				}
				if (carry != 0) { digit_multi.number.push_back(carry + '0'); }
				digit_multi.number.reverse();
				for (int k = 0; k < (l2 - 1 - i); k++) { digit_multi.number.push_back('0'); }
				ans = ans + digit_multi; 
			}

			cout << "multi for loop exit" << endl; // debug printout
			if (neg_ans != 0) {
				ans.number.reverse();
				ans.number.push_back('-');
				ans.number.reverse();
			} 
			return ans;
		}

		// division of two longnum  
		longnum operator/ (const longnum &y) {}

		friend ostream& operator << (ostream &out, const longnum &i);

};

// operator overloading
ostream& operator << (ostream &out, const longnum &i)
{
	out << i.number; 
}

int main()
{
	// main function logic
	longnum a, b;
	a.setvalue();
	b.setvalue();
	cout << a + b << endl;
	cout << a * b << endl; 
	return 0;
}