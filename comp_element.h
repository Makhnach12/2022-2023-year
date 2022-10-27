#ifndef COMP_ELEMENT_H
#define COMP_ELEMENT_H
#include <iostream>
#include <string>
#include <fstream>

class element {
private:
	std::string _lexem;
	std::string _type_lexem;
public:
	element(std::string lexem, std::string type_lexem) {
		_lexem = lexem;
		_type_lexem = type_lexem;
	}

	std::string lexem() { return _lexem; }

	void set_lexem(std::string lexem) {
		_lexem = lexem;
	}

	void type_lexem(std::string type_lexem) {
		_type_lexem = type_lexem;
	}

	friend std::ostream& operator<<(std::ostream&, const element&);
};

inline std::ostream& operator<<(std::ostream& output, const element& stud) {
	output << stud._type_lexem << " " << stud._lexem;
	return output;
} 

#endif
