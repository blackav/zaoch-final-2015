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
EXECUTE_FLAGS =  --use-stdin --use-stdout --test-pattern=%02d --corr-pattern=%02d.a --time-limit=5

NORMALIZE = ${EJUDGE_SERVER_BIN_PATH}/ej-normalize
NORMALIZE_FLAGS = --workdir=tests --test-pattern=%02d --corr-pattern=%02d.a

all : ks_nlogn 2check 2inter
check_settings : all normalize

ks_nlogn : ks_nlogn.cpp
	${CXX} -DEJUDGE ${CXXFLAGS} ks_nlogn.cpp -oks_nlogn ${CXXLIBS}

2check : 2check.cpp
	${CXX} -DEJUDGE ${CXXLIBCHECKERFLAGS} 2check.cpp -o2check ${CXXLIBCHECKERLIBS}

2inter : 2inter.cpp
	${CXX} -DEJUDGE ${CXXLIBCHECKERFLAGS} 2inter.cpp -o2inter ${CXXLIBCHECKERLIBS}

answers : ks_nlogn
	${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-dir=tests --workdir=tests --all-tests ks_nlogn

answer : ks_nlogn
	cd tests && ${EXECUTE} ${EXECUTE_FLAGS} --update-corr --test-num=${TEST_NUM} ../ks_nlogn


normalize :
	${NORMALIZE} ${NORMALIZE_FLAGS} --all-tests

clean :
	-rm -f *.o *.class *.exe *~ *.bak ks_nlogn 2check 2inter

### END ejudge auto-generated makefile ###
