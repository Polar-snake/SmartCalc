CFLAGS = -Wall -Werror -Wextra -std=c11
OS = $(shell uname)
BACK_FUNCTIONS = Backend/stack_parser.c Backend/stack_functions.c Backend/credit_calc.c
FRONT_FUNCTIONS = Frontend/*.cpp

ifeq ($(OS),Linux)
    det_OS = -lcheck -lm -lrt -lpthread -lsubunit
else
    det_OS = -lcheck -lm -lpthread
endif


all: install dist

install: uninstall
	@echo "Installation"
	@mkdir build
	@cd Frontend/ && qmake && make -j6 && make clean && rm -rf Makefile && mv Frontend.app ../build
	@echo "Application installed"
	@open build
	@open dvi

uninstall:
	@rm -rf build
	@rm -rf dist
	@make clean
	@echo "ANNIHILATION PROCESS STARTED. THERE IS NO WAY BACK!"

runlib: $(BACK_FUNCTIONS) Backend/back.h
	gcc $(CFLAGS) $(BACK_FUNCTIONS) -c
	ar rcs Calc.a *.o
	ranlib Calc.a

test: clean
	@gcc $(CFLAGS) $(BACK_FUNCTIONS) Backend/test.c --coverage -o test_result $(det_OS)
	@./test_result

gcov_report: test
	@lcov -t "smart_calc_check" -o calc.info -q -c -d .
	@genhtml -o report/ calc.info
	@open report/index.html
	@rm -rf *.gcno *gcda *.gcov *.info test_result

dvi:
	@open 'dvi/dvi_instruction.html'

dist:
	@mkdir -p dist
	@cp -R build/Frontend.app dist
	@cd dist && tar cvzf SmartCalc.tar *
	@cd dist && rm -rf Frontend.app dvi_instruction.md

check_clang:
	clang-format -style=Google -n Backend/*.c Backend/*.h Frontend/*.cpp Frontend/*.h

style_fix:
	clang-format -style=Google -i Backend/*.c Backend/*.h Frontend/*.cpp Frontend/*.h

clean:
	@rm -rf test_result report *.gcda *.gcno *.o *.info *.a
	@rm -rf Frontend/.qtc_clangd Frontend/.qmake.stash
	@rm -rf Frontend/qmake_qmake_qm_files.qrc
	@rm -rf Frontend/.qm
	@echo "Cleaned"
install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

install_lcov:
	brew install lcov

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all make test
