SRC = main.c
OBJ = ${SRC:.c=.o}
OUT = xwm
LDFLAGS = -lX11


${OUT}: ${OBJ} utils.h
	@${CC} ${OBJ} ${LDFLAGS} -o $@

${OBJ}: $(SRC)
	@${CC} -c $< -o $@

clean:
	@rm ${OBJ} ${OUT}
