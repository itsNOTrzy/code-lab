NAME = Sample02
OBJS = $(NAME).obj
RES  = $(NAME).res

$(NAME).exe: $(OBJS)
	Link /SUBSYSTEM:WINDOWS $(OBJS)
.asm.obj:
	ml /c /coff $(NAME).asm
