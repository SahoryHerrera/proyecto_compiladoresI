CXX       = g++
CXXFLAGS  = -std=c++17 -Wall -Wno-unused-function

SRC_DIR   = src
BUILD_DIR = build
TEST_DIR  = tests

LEXER_SRC  = $(SRC_DIR)/lexer/lexer.l
PARSER_SRC = $(SRC_DIR)/parser/parser.y
MAIN_SRC   = $(SRC_DIR)/main.cpp
AST_SRC    = $(SRC_DIR)/ast/ast.cpp
AST_HDR    = $(SRC_DIR)/ast/ast.hpp

LEXER_COPY = $(BUILD_DIR)/lexer.l
LEX_C      = $(BUILD_DIR)/lex.yy.c
PARSER_C   = $(BUILD_DIR)/parser.tab.c
PARSER_H   = $(BUILD_DIR)/parser.tab.h
EXEC       = $(BUILD_DIR)/compiler

all: $(EXEC)
	@echo ""
	@echo "  Compilador listo: $(EXEC)"
	@echo "  Uso: ./$(EXEC) <archivo.rs>"
	@echo ""

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(PARSER_C) $(PARSER_H): $(PARSER_SRC) $(AST_HDR) | $(BUILD_DIR)
	bison -d -o $(PARSER_C) $(PARSER_SRC)

$(LEXER_COPY): $(LEXER_SRC) | $(BUILD_DIR)
	cp $(LEXER_SRC) $(LEXER_COPY)

$(LEX_C): $(LEXER_COPY) $(PARSER_H)
	cd $(BUILD_DIR) && flex -o lex.yy.c lexer.l

$(EXEC): $(PARSER_C) $(LEX_C) $(MAIN_SRC) $(AST_SRC)
	$(CXX) $(CXXFLAGS) \
		-I $(BUILD_DIR) \
		-I $(SRC_DIR) \
		-I $(SRC_DIR)/ast \
		-o $(EXEC) \
		$(PARSER_C) $(LEX_C) $(MAIN_SRC) $(AST_SRC)

test: $(EXEC)
	@echo ""
	@echo "========================================"
	@echo "  Ejecutando pruebas en $(TEST_DIR)/"
	@echo "========================================"
	@for f in $(TEST_DIR)/*.rs; do \
		echo ""; \
		echo ">>> $$f"; \
		./$(EXEC) $$f; \
	done

clean:
	rm -rf $(BUILD_DIR)
	@echo "  Limpiado."

.PHONY: all test clean
