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
	element() { _lexem = ""; }
	element(std::string lexem, std::string type_lexem) {
		_lexem = lexem;
		_type_lexem = type_lexem;
	}

	element(const element& obj) {
		_lexem = obj._lexem;
		_type_lexem = obj._type_lexem;
	}

	std::string lexem() { return _lexem; }

	void set_lexem(std::string lexem) {
		_lexem = lexem;
	}

	void type_lexem(std::string type_lexem) {
		_type_lexem = type_lexem;
	}

	inline element make_element(char lexem, std::string type_lexem) {
		std::string lex;
		lex += lexem;
		element el(lex, type_lexem);
		return el;
	}

	inline element make_element(std::string lexem, std::string type_lexem) {
		element el(lexem, type_lexem);
		return el;
	}

	friend std::ostream& operator<<(std::ostream&, const element&);
	void operator=(element obj) {
		_lexem = obj._lexem;
		_type_lexem = obj._type_lexem;
	}

};

inline std::ostream& operator<<(std::ostream& output, const element& stud) {
	output << stud._type_lexem << " " << stud._lexem;
	return output;
} 





#endif
