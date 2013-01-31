
CFLAGS = -std=gnu99

.PHONY: program clean

all: mset glob time



glob: glob.hw2_1.o
	${CC} -o $@ $^ 

time: time.hw2_6.o
	${CC} -o $@ $^ 

mset: mset.hw2_5.o time.hw2_6.o
	${CC} -g -o $@ $^ 

dump: mset
	objdump -SlC $^ > dump

clean:
	rm -rf time glob mset *.o dump

# %: $@.o
# 	${CC} -o $@ $^ 










# #

# ${TARGET}: ${OBJS}
# 	${CC} -o ${TARGET} ${OBJS}
# #allowing make to make the *.o files separatley allows for large projects to 
# # compile faster as all the intermediate files don't have to be regenerated if 
# # their source hasn't changed.

# clean:
# 	rm -f ${TARGET} *.o *.d

# run:
# 	./${TARGET} ?
