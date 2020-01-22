/* XML Parser 
Created by Ammar Sheikh
January 2020 */


/* ASSUME XML 1.0  
*/

#include "XMLParser.h"

#include <algorithm>
#include <stack>

//DEBUGGING
#include <iostream>

namespace ammar {


std::string XMLParser::ElementNode::ToString() {
  auto element = "Name: "+ name  + " Text: " + text + " Attributes: ";
  std::for_each(attributes.begin(),
                attributes.end(), [&](attributePair p) {
                element += "{"+ p.first + ":" + p.second + "} "; });
  return element;
}

void XMLParser::build() {
  std::stack<ElementNode*> elements;

  while (!lexer.lexedAllTokens()) {
    lexer.lex();

    if (lexer.getCurrentToken().data == "<") {
      processNewNodeData(elements);
    }
    if (lexer.getCurrentToken().type == Token::TokenType::IDENTIFIER) {
      processCurrentNodeText(elements);
    }
    if (lexer.getCurrentToken().data == "</") {
      closeNodeState(elements);
    }
  }
}


void XMLParser::processNewNodeData(std::stack<ElementNode*>& elements) {
    lexer.lex();
    if (lexer.getCurrentToken().data == ">")
      return;
    ElementNode* addNode = new ElementNode(lexer.getCurrentToken().data);
    if (!root) {
      root = addNode;
      elements.push(root);
    }
    else {
      addNode->parent = elements.top();
      elements.top()->children.push_back(addNode);
      elements.push(addNode);
    }

    std::vector<std::pair<std::string,std::string>> attributeList;

    lexer.lex();
    while (lexer.getCurrentToken().data != ">") {
      
      std::pair<std::string,std::string> pair;
      while (lexer.getCurrentToken().data != "=" ) {
        auto AttributeName = lexer.getCurrentToken().data;
        lexer.lex();
        pair.first = AttributeName;
      }
      lexer.lex();
      if (lexer.getCurrentToken().data == "\"") {
        lexer.lex();
        auto attributeVal = lexer.getCurrentToken().data;
        lexer.lex();
        while (lexer.getCurrentToken().data != "\"") {
          attributeVal += lexer.getCurrentToken().data;
          lexer.lex();
        }
        pair.second = attributeVal;
        attributeList.push_back(std::move(pair));
        lexer.lex();
      }
    }
    addNode->attributes = std::move(attributeList);
}


void XMLParser::processCurrentNodeText(std::stack<ElementNode*>& elements) {
  elements.top()->text += lexer.getCurrentToken().data;
}


void XMLParser::closeNodeState(std::stack<ElementNode*>& elements) {
  elements.pop();
  while (lexer.getCurrentToken().data != ">")
    lexer.lex();
}


//CURRENTLY USED FOR TESTING 
void XMLParser::displayXMLTree() {
  if(!root)
    return;
  std::stack<ElementNode*> s;
  s.push(root);
  while (!s.empty()) {
    ElementNode* node = s.top();
    s.pop();
    for (const auto child : node->children)
      s.push(child);
    std::cout << node->ToString() << "\n";
  }
}

} // namespace ammar