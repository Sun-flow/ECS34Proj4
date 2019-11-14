#include "StringUtils.h" 
#include <iostream>
//#include <string>
#include <algorithm> 
#include <cctype>
#include <cstdio>

namespace StringUtils{
    
std::string Slice(const std::string &str, ssize_t start, ssize_t end){ //slices word at starting to end
	std::string s = "";
	if (start < 0) //case when start is negative
		start += str.size(); //instead of starting at "-2" it would start at the str.length() - 2
	if (end <= 0) //if end is negative or zero
		end += str.size();
	for (auto i = start; i < end; ++i) //just add correct chars to string from start to end
	{
		s += str[i];
	}
	
	return s;
}

std::string Capitalize(const std::string &str){ //just capitalizes first letter
	std::string s = str;
	int count = 0;

	for (auto &ch : s)
	{
		if (count == 0) //first instance of alpha
		{
			
			s[count] = toupper(ch);
		}
		else
		{
			s[count] = tolower(ch);
		}
		count++;
	}
	return s;
}

std::string Title(const std::string &str){ //capitalize first letter of each word

	std::string s = str;
	int count = 0;
	bool notAlpha = false; //not alpha char is assumed to be false in beginning
	for (size_t i = 0; i < str.length(); ++i)
	{
		while (s[i] == ' ' || (s[i] >= 48 && s[i] <= 57) || s[i] == 39 || s[i] == 45) // the 48 through 57 is the char 0-9, and the 39 is apostrophe, 45 = '-'
		{
			notAlpha = true; //basically not alphabaic characters have been in the string so far
			++i;
			count = i; //keeps track of index
		}
		if (notAlpha || i == 0) //beginning or first instanse that 'notAlpha' leaves the while loop so first instance of alpha character
		{
			s[count] = toupper(s[count]); //just capatalizes the first alpha encountered
			notAlpha = false; //reset flag for next word
		}
		else if (s[i] != islower(s[i])) //lowers all the rest of the alpha's
			s[i] = tolower(s[i]);

	}
	return s;
}

std::string LStrip(const std::string &str){ //strips all the whitespace from left
	int count = 0;
	bool firstAlpha = true; //Assuming the first char is  alphabeticall
	if (str[0] == ' ')
	{
		firstAlpha = false; //first char is space so we will iterate through loop to get rid of spaces
		for (auto &ch : str)
		{
			if (ch == ' ' && !firstAlpha)
				count++;
			else
				break;  // you found the first alpha break the loop not need to iterate
		}
		return str.substr(count, str.length() - count );
	}
	else
	{
		return str; //no left spaces to remove so just return string
	}
}

std::string RStrip(const std::string &str){ //strips all the whitespace from right
	int count = 0;
	bool firstAlpha = true; //assuming last char is a alpha char
	if (str[str.size() - 1] == ' ') //checks last char for white space
	{
		firstAlpha = false;
		for (int i = str.size() - 1; i > 0; --i) //iterating backwards
		{
			if (str[i] == ' ' && !firstAlpha) //if space and you havent encountered first alpha char
				count++;
			else
				break; // first alpha was found leave loop
		}
		return str.substr(0, str.length() - count);
	}
	else
	{
		return str; //no right spaces to strip
	}
}

std::string Strip(const std::string &str){ //strip both left and right whitespace
	std::string s = str;
	s = LStrip(s);
	s = RStrip(s);
	return s;
}

std::string Center(const std::string &str, int width, char fill){ //adds a "fill" char to center both sides of str
	std::string s = "";
	bool odd = false; //if its even on both aides
	int diff = width - str.length();
	int adj = diff / 2; // Puts correct ammount on both sides
	if (diff % 2 == 1) //then there is a remainder
		odd = true;
	for (int i = 0; i < adj; ++i)
	{
		s.push_back(fill);
	}
	for (size_t i = 0; i < str.length(); ++i)
	{
		s.push_back(str[i]);
	}
	for (int i = 0; i < adj; ++i)
	{
		s.push_back(fill);
	}
	if (odd)
	{
		s.push_back(fill);
	}
	return s;
}

std::string LJust(const std::string &str, int width, char fill){ //left justifies the string with char fill
	std::string s = str;
	int diff = width - str.length();
	for (int i = 0; i < diff; ++i)
	{
		s.push_back(fill);
	}
	return s;
}

std::string RJust(const std::string &str, int width, char fill){ //right justifies string
	std::string s = "";
	int length = width - str.length();
	for (auto i = 0; i < length; ++i) //put spaces first
		s.push_back(fill);
	for (size_t i = 0; i < str.length(); ++i) //then str
		s.push_back(str[i]);
	return s; 
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep){ //replaces first word with the third paramenter every time it sees second param
	std::string s = str;
	auto index = str.find(old); //http://www.cplusplus.com/reference/string/string/find/
	if (index != std::string::npos) //you found the old string
	{
		do
		{
			for (auto &ch : rep) //rep is the string your replacing the old string
			{
				s[index++] = ch; //at the index you found old replace with "rep"
			}
			index = str.find(old, index);
		} while (index != std::string::npos); // keeps swapping until it can't find old string
	}
	return s;
	
}

std::vector< std::string > Split(const std::string &str, const std::string &splt){ //splits the string at every encounter of splt
	std::vector< std::string> res;
	std::string s = str, temp;
	int num = 0;
	bool space = (splt == "" ? true : false);
	size_t old_index = 0, new_index = 0, count = 0;
	new_index = str.find(splt);  //http://www.cplusplus.com/reference/string/string/find/
	if (space ) //space
	{
		new_index = str.find(" ");
		const char tab = '\t';
		const char line = '\n';
		const char blank = ' ';
		size_t IBlank, ITab, ILine = 0;
		for (auto &ch : s)
		{
			if (ch == tab || ch == line || ch == blank || count == str.size() - 1)
			{

				if (old_index == 0) //first instance of splitting the string
				{

					temp = s.substr(old_index, count);
				}
				else if (count == str.size() - 1) //count has reached the end of str
				{
					--count;
					--count;
					if (num + count + 1 < str.size())
					{
						temp = s.substr(old_index + num, count - old_index + 2);
					}
				}
				else
				{
					
					temp = s.substr(old_index + num, (count - old_index - 1));
				}
				IBlank = temp.find(" "); //checking if the new split temp does'nt have " "
				ITab = temp.find("\t");
				ILine = temp.find("\n");

				old_index = count;
				if (IBlank == std::string::npos && ITab == std::string::npos && ILine == std::string::npos)
				{

					num = 1;
					if (temp != "")
						res.push_back(temp);

				}
			}
			count++;
		}
		return res;
	}
	else if (new_index != std::string::npos) //word
	{

		while (new_index != std::string::npos)
		{
			
			if ((old_index + num + new_index - old_index - num) < str.size() && count != 0) //so mid or end of string
				temp = s.substr(old_index + splt.size(), new_index - old_index - splt.size());
			if (count == 0)
				temp = s.substr(old_index, new_index - old_index);
			if (new_index == 0 && s[new_index] == '/')
			{
				res.push_back("");
				num = 1;
			}
			else if (new_index != old_index + 1 && new_index != old_index)
			{
				res.push_back(temp);
				num = 1;
			}
			else if ((new_index == (old_index + 1)) && (s[new_index] != s[old_index + 1]))
			{
				if (temp != "")
				{
					res.push_back(temp);
					num = 1;
				}
			}
			count++;
			old_index = new_index;
			new_index = str.find(splt, old_index + 1);
			if (new_index >= str.size())
				break;
		}
		temp = s.substr(old_index + splt.size(), str.size() - 1);
		res.push_back(temp);

		return res;
	}
	else {
		res.push_back(s);
		return res;
	}
}

std::string Join(const std::string &str, const std::vector< std::string > &vect){ //joins together vector with the str separating each word
	std::string s;
	for (size_t i = 0; i < vect.size(); ++i)
	{
		if (i == 0) //first instance 
		{
			s += vect[i];
		}
		else
		{
			s = s + str + vect[i];
		}
	}
	return s;
}

std::string ExpandTabs(const std::string &str, int tabsize){
	std::string s = str;
	int space = 0, count = 0;
	auto index = s.find('\t');
	while (index != std::string::npos)
	{
		space = (tabsize == 0 ? 0 : tabsize - (index % tabsize)); //adjusts the amount of spaces to tabsize depending on what index your on
		s.erase(index, 1); //deletes the \t
		s.insert(index, space, ' '); //inserts at index character ' ' spaces;
		index = s.find('\t', index + 1);
		count++;
	}

	return s;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase){ //compares the strings to see how different they are
	auto m = 0, n = 0, count = 0;
	m = left.size();
	n = right.size();
	std::string r = right, l = left;
	if (m == n) //same size
	{
		for (auto i = 0; i < m; ++i)
		{
			if (ignorecase & (toupper(l[i]) == toupper(r[i])))
				count++;
			else if (left[i] == right[i])
				count++;
		}
		return m - count;
	}
	else if (n > m) //  right is bigger
	{
		auto i = 0, k = 0;
		while (i < m && k < n) // assumes right is bigger; so if left is bigger you have to switch m and n 
		{
			if (ignorecase & (toupper(r[k]) == toupper(l[i])))
			{
				i++;
				k++;
				count++;
			}
			else if (right[k] == left[i]) //we aren't ignoring cases 
			{
				i++;
				k++;
				count++;
			}
			else if (k != m) // if k (which is iterating through the bigger string) hasn't past the size of the left string's size
			{
				k++;
			}
			else //k has past the left string's size so well increment i to then recompare the strings again
			{
				i++;
				k = i; //resets k
			}

		}
		return n - count;
	}
	else // left is bigger
	{
		auto i = 0, k = 0;
		while (i < m && k < n)
		{
			if (ignorecase & (toupper(r[k]) == toupper(l[i])))
			{
				i++;
				k++;
				count++;
			}
			else if (right[k] == left[i])
			{
				i++;
				k++;
				count++;
			}
			else if (i != n)
			{
				i++;
			}
			else
			{
				k++;
				i = k;
			}

		}
		return m - count;
	}
	return 0;
}

}
