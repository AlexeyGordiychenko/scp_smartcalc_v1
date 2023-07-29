# Constants
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g -fmax-errors=1
LDFLAGS=-lcheck -pthread -lm

ifeq ($(shell uname), Linux)
	LDFLAGS += -lsubunit
endif

# Converage
GCOVFLAGS=--coverage
GCOV_DIR=gcov

# Directories
TEST_DIR=tests
SRC_DIR=.
OBJ_DIR=obj
OBJ_DIR_GCOV=obj/$(GCOV_DIR)
OBJ_DIR_TEST=obj/$(TEST_DIR)

# Files
SRCS=$(wildcard $(SRC_DIR)/s21_*.c)
SRCS_TEST=$(wildcard $(TEST_DIR)/s21_*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_TEST=$(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR_TEST)/%.o,$(SRCS_TEST))
OBJS_GCOV=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR_GCOV)/%.o,$(SRCS))

# Builds
PROGRAM=s21_SmartCalc
LIB=s21_smartcalc.a
TEST=test
TEST_BUILD=test_build

# Docs
DOC=doc_smartcalc

.PHONY: all $(TEST) $(TEST_BUILD) $(LIB) gcov_report clean rebuild clang_n clang_i valgrind

all: $(LIB)

main: main.c $(LIB)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TEST_BUILD): $(OBJS_GCOV) $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(GCOVFLAGS) -o $(TEST)

$(TEST): $(TEST_BUILD)
	./$@

$(LIB): $(OBJS)
	ar rcs $(LIB) $^
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_TEST)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR_TEST)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_GCOV)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR_GCOV)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

gcov_report: $(TEST_BUILD)
	./$(TEST) || true
	mkdir -p $(GCOV_DIR)
	rm -rf $(GCOV_DIR)/*.gcda $(GCOV_DIR)/*.gcno
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter "$(SRC_DIR)/*"
	open $(GCOV_DIR)/index.html

lcov_report: $(TEST_BUILD)
	./$(TEST) || true
	mkdir -p $(GCOV_DIR)
	lcov -o $(GCOV_DIR)/Coverage_Report.info -c -d $(OBJ_DIR_GCOV)
	lcov -r $(GCOV_DIR)/Coverage_Report.info  -o $(GCOV_DIR)/Coverage_Report.info '/Library/*'
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/Coverage_Report.info 
	open $(GCOV_DIR)/index.html

dvi:
	texi2dvi --clean --pdf $(DOC).texi
	open $(DOC).pdf

dist:
	mkdir -p $(PROGRAM)/src
	@cp Makefile s21_*.c s21_*.h *.pro *.cpp *.ui *.user $(PROGRAM)/src 2>/dev/null || true
	tar cvzf $(PROGRAM).tgz $(PROGRAM)/
	rm -rf $(PROGRAM)/

clean:
	rm -rf $(OBJ_DIR) $(GCOV_DIR) $(TEST) $(LIB) $(DOC).pdf

rebuild: clean all

clang_n:
	clang-format -n --style=Google *.[ch] $(SRC_DIR)/*.[ch] $(TEST_DIR)/*.[ch]

clang_i:
	clang-format -i --style=Google *.[ch] $(SRC_DIR)/*.[ch] $(TEST_DIR)/*.[ch]

valgrind: $(TEST_BUILD)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST)
