### BEGIN ejudge auto-generated makefile ###
EJUDGE_PREFIX_DIR ?= /opt/ejudge
EJUDGE_CONTESTS_HOME_DIR ?= /home/judges
EJUDGE_LOCAL_DIR ?= /var/lib/ejudge
EJUDGE_SERVER_BIN_PATH ?= /opt/ejudge/libexec/ejudge/bin

CXX = g++
CXXFLAGS = -Wall -g -O2

EXECUTE = ${EJUDGE_PREFIX_DIR}/bin/ejudge-execute
EXECUTE_FLAGS =  --use-stdin --use-stdout --test-pattern=%02d --corr-pattern=%02d.a --time-limit=4

NORMALIZE = ${EJUDGE_SERVER_BIN_PATH}/ej-normalize
NORMALIZE_FLAGS = --workdir=tests --test-pattern=%02d --corr-pattern=%02d.a

all : clev_qmalpha
check_settings : all normalize

clev_qmalpha : clev_qmalpha.cpp
	${CXX} -DEJUDGE ${CXXFLAGS} clev_qmalpha.cpp -oclev_qmalpha ${CXXLIBS}

answers : clev_qmalpha
	${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-dir=tests --workdir=tests --all-tests clev_qmalpha

answer : clev_qmalpha
	cd tests && ${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-num=${TEST_NUM} ../clev_qmalpha


normalize :
	${NORMALIZE} ${NORMALIZE_FLAGS} --all-tests

clean :
	-rm -f *.o *.class *.exe *~ *.bak clev_qmalpha

### END ejudge auto-generated makefile ###
