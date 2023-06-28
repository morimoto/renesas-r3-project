-include ${CMD}/script/Makefile.common

${TGT}: ${TGT}.o
	${Q}echo ${DEV_VER}/$@
	${Q}${CC} -o $@ ${TGT}.o

${SRC}: ${TOP}/device/${DEVICE}/${SRC} main.c
	${Q}echo ${DEV_VER}/$@
	make ${S} SRC=$${SRC} -f ${CMD}/${DEV_VER}/Makefile

${TGT}.o: ${SRC}
	${Q}echo ${DEV_VER}/$@
	${Q}${CC} ${CFLAGS} ${INCLUDE} ${LFLAGS} -c $< -o $@

${TGT}.depend: ${SRC}
	${Q}echo ${DEV_VER}/$@
	${Q}${CC} ${CFLAGS} -MM -MP $< ${INCLUDE} > $@

-include ${TGT}.depend
