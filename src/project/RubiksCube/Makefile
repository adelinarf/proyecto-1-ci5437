# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++ -std=c++17
CXL = g++ -std=c++2a
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=0
BASE_FOLDER = ../../psvn-for-ci5437
ALGORITHMS_FOLDER = ../Algoritmos

psvn2c_core.c:
	@cp ${BASE_FOLDER}/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp ${BASE_FOLDER}/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp ${BASE_FOLDER}/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@echo "**** Constructing $@ ..."
	@${BASE_FOLDER}/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ${BASE_FOLDER}/global/succ.c
	@echo "**** Constructing $@ ..."
	@$(CC) $(OPT) ${BASE_FOLDER}/global/succ.c -include $< -o $@
	@rm -f $*.c

%.dist: %.c ${BASE_FOLDER}/global/dist.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ${BASE_FOLDER}/global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c ${BASE_FOLDER}/global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ${BASE_FOLDER}/global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c ${BASE_FOLDER}/global/generator.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ${BASE_FOLDER}/global/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@echo "**** Constructing abstractor ..."
	@$(CXX) $(OPT) ${BASE_FOLDER}/src/abstractor.cpp ${BASE_FOLDER}/src/psvn.cpp -o $@


%.pdb: abstractor
	@rm -f `basename $*`.abst `basename $*`.pdb `basename $*`.psvn
	@echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	@./abstractor `dirname $*`.psvn `basename $*` < `basename $*`.txt > /dev/null
	@make `basename $*`.distSummary
	@echo "**** Constructing PDB `basename $*`.pdb ..."
	@./`basename $*`.distSummary `basename $*`.pdb
	@rm -f abstractor `basename $*`.distSummary

%.dist_pdb: %.c ${BASE_FOLDER}/global/dist_pdb.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ${BASE_FOLDER}/global/dist_pdb.cpp -include $< -o $@
	@rm -f $*.c

%.astar: %.c
	$(CXL) ${ALGORITHMS_FOLDER}/A_Star/astar.cpp ${ALGORITHMS_FOLDER}/A_Star/AStarAlgorithm.cpp -include $< -o $@

%.ida:  %.c
	$(CXX) $(OPT) ${ALGORITHMS_FOLDER}/IDA/ida.cpp -include $< ${ALGORITHMS_FOLDER}/IDA/IDA_Algorithm.cpp -o $@

%.bfs:  %.c
	$(CXL) ${ALGORITHMS_FOLDER}/BFS/bfs.cpp ${ALGORITHMS_FOLDER}/BFS/BFSAlgorithm.cpp -include $< -o $@

all:
	@make abstractor
	@make rubik3Sticker/rubik3x3.pdb
	@make rubik3Sticker.c

bfs:
	@make rubik3Sticker.bfs 

astar:
	@make rubik3Sticker.astar

ida:
	@make rubik3Sticker.ida

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~