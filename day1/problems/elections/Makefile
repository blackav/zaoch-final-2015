### BEGIN ejudge auto-generated makefile ###
EJUDGE_PREFIX_DIR ?= /opt/ejudge
EJUDGE_CONTESTS_HOME_DIR ?= /home/judges
EJUDGE_LOCAL_DIR ?= /var/lib/ejudge
EJUDGE_SERVER_BIN_PATH ?= /opt/ejudge/libexec/ejudge/bin

CXX = g++
CXXFLAGS = -Wall -g -O2

EXECUTE = ${EJUDGE_PREFIX_DIR}/bin/ejudge-execute
EXECUTE_FLAGS =  --use-stdin --use-stdout --test-pattern=%02d --corr-pattern=%02d.a --time-limit=3

NORMALIZE = ${EJUDGE_SERVER_BIN_PATH}/ej-normalize
NORMALIZE_FLAGS = --workdir=tests --test-pattern=%02d --corr-pattern=%02d.a

all : elections_ra_dp_pairslogk
check_settings : all normalize

elections_ra_dp_pairslogk : elections_ra_dp_pairslogk.cpp
	${CXX} -DEJUDGE ${CXXFLAGS} elections_ra_dp_pairslogk.cpp -oelections_ra_dp_pairslogk ${CXXLIBS}

answers : elections_ra_dp_pairslogk
	${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-dir=tests --workdir=tests --all-tests elections_ra_dp_pairslogk

answer : elections_ra_dp_pairslogk
	cd tests && ${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-num=${TEST_NUM} ../elections_ra_dp_pairslogk


normalize :
	${NORMALIZE} ${NORMALIZE_FLAGS} --all-tests

clean :
	-rm -f *.o *.class *.exe *~ *.bak elections_ra_dp_pairslogk

### END ejudge auto-generated makefile ###
