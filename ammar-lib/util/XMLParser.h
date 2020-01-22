/* XML Parser 
Created by Ammar Sheikh
January 2020 */


/* ASSUME XML 1.0 
*/

#ifndef AMMARLIB_XMLPARSER_H
#define AMMARLIB_XMLPARSER_H

#include "Lexer.h"

#include <vector>
#include <string>
#include <fstream>

//#define NDEBUG
#include <cassert>
#include <cctype>
#include <stack>
#include <algorithm>

// TODO:
// Finish iterator class
// ignore optional xml declaration tag
// tree display fuction

namespace ammar {

// XMLParser builds the elementTree, and provides iteration over data
// over data

class ElementNode;

class XMLParser {

  static constexpr std::initializer_list<char> identifers {'a', 'b', 'c', 'd',
  'e', 'f', 'g', 'h', 'i', 'j' ,'k', 'l', 'm', 'n', 'o', 'p' ,'q', 'r','s', 
  't', 'u', 'v', 'w', 'x', 'y' ,'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
  'I', 'J', 'K', 'L','M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 
  'X', 'Y', 'Z', '.', '_', '-', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
  '0', ':'};

  static constexpr std::initializer_list<char> operators {'<', '>','=', '/'};
  static constexpr std::initializer_list<char> literals {'\"'};
  static constexpr std::initializer_list<char> differs {'>', '<'};

  struct ElementNode {

    using attributePair = std::pair<std::string,std::string>;
   
    ElementNode(const std::string& element_name, ElementNode* prnt = nullptr) :
              name(element_name), parent(prnt)  {};
   
    std::string ToString();

    std::vector<ElementNode*> children;
    std::vector<attributePair> attributes;
    std::string name;
    std::string text;
    ElementNode* parent;
  };

  // Holds root to XMLTree
  ElementNode* root; 

  // Handles Tokenization of xml file
  Lexer lexer;

  void processNewNodeData(std::stack<ElementNode*>& elements);
  void processCurrentNodeText(std::stack<ElementNode*>& elements);
  void closeNodeState(std::stack<ElementNode*>& elements);

 public:
  XMLParser(const char* file_name, std::size_t bufferSize = 256) :
  lexer(file_name, XMLParser::operators, XMLParser::identifers, 
  XMLParser::literals, {}, XMLParser::differs, bufferSize), root(nullptr) {}
  //Add another constructor to give the option of 
  // providing the ops,idents, lits, and keywords

  //redundant 
  XMLParser(const XMLParser& x) = delete;


  // Iterator class

  //Iterator class
  class iterator {
    ElementNode* current;

  };


  void build();
  void displayXMLTree();

  iterator begin();
  iterator end();


  
};

} // namespace ammar

#endif // AMMARLIB_XMLPARSER_H