### BEGIN ejudge auto-generated makefile ###
EJUDGE_PREFIX_DIR ?= /opt/ejudge
EJUDGE_CONTESTS_HOME_DIR ?= /home/judges
EJUDGE_LOCAL_DIR ?= /var/lib/ejudge
EJUDGE_SERVER_BIN_PATH ?= /opt/ejudge/libexec/ejudge/bin

CXX = g++
CXXFLAGS = -Wall -g -O2
CXXLIBCHECKERFLAGS = -m32 -Wall -g -O2 -I${EJUDGE_PREFIX_DIR}/include/ejudge -L${EJUDGE_PREFIX_DIR}/lib -Wl,--rpath,${EJUDGE_PREFIX_DIR}/lib
CXXLIBCHECKERLIBS = -lchecker -lm

EXECUTE = ${EJUDGE_PREFIX_DIR}/bin/ejudge-execute
EXECUTE_FLAGS =  --use-stdin --use-stdout --test-pattern=%02d --corr-pattern=%02d.a --time-limit=2

NORMALIZE = ${EJUDGE_SERVER_BIN_PATH}/ej-normalize
NORMALIZE_FLAGS = --workdir=tests --test-pattern=%02d --corr-pattern=%02d.a

all : dictionary_mp_z_100 check
check_settings : all normalize

dictionary_mp_z_100 : dictionary_mp_z_100.cpp
	${CXX} -DEJUDGE ${CXXFLAGS} dictionary_mp_z_100.cpp -odictionary_mp_z_100 ${CXXLIBS}

check : check.cpp
	${CXX} -DEJUDGE ${CXXLIBCHECKERFLAGS} check.cpp -ocheck ${CXXLIBCHECKERLIBS}

answers : dictionary_mp_z_100
	${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-dir=tests --workdir=tests --all-tests dictionary_mp_z_100

answer : dictionary_mp_z_100
	cd tests && ${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-num=${TEST_NUM} ../dictionary_mp_z_100


normalize :
	${NORMALIZE} ${NORMALIZE_FLAGS} --all-tests

clean :
	-rm -f *.o *.class *.exe *~ *.bak dictionary_mp_z_100 check

### END ejudge auto-generated makefile ###
