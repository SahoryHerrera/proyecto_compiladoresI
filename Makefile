CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC_DIR = src
BUILD_DIR = build

LEXER = $(SRC_DIR)/lexer/lexer.l
PARSER = $(SRC_DIR)/parser/parser.y
MAIN = $(SRC_DIR)/main.cpp
AST = $(SRC_DIR)/ast/ast.cpp

LEX_C = $(BUILD_DIR)/lex.yy.c
PARSER_C = $(BUILD_DIR)/parser.tab.c
PARSER_H = $(BUILD_DIR)/parser.tab.h
EXEC = $(BUILD_DIR)/compiler

all: $(EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(PARSER_C) $(PARSER_H): $(PARSER) | $(BUILD_DIR)
	bison -d -o $(PARSER_C) $(PARSER)

$(LEX_C): $(LEXER) $(PARSER_H) | $(BUILD_DIR)
	flex -o $(LEX_C) $(LEXER)

$(EXEC): $(PARSER_C) $(LEX_C) $(MAIN) $(AST)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(PARSER_C) $(LEX_C) $(MAIN) $(AST)

clean:
	rm -rf $(BUILD_DIR)