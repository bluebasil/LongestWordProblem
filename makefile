# super simple makefile
# call it using 'make NAME=name_of_code_file_without_extension'
# (assumes a .cpp extension)
NAME = "main"
frame-rate = "30"
speed = "5"
#
# Add $(MAC_OPT) to the compile line for Mac OSX.
MAC_OPT = "-I/opt/X11/include"

all:
	@echo "Compiling..."
	g++ -o $(NAME) $(NAME).cpp 
	./$(NAME)

run: all
	@echo "Running..."
	./$(NAME) 

clean:
	-rm $(NAME)