
GEN := gen
GEN64 := ../../gen/64
LIB64 := 64
LIBTHIS := fs
GEN64LIB := $(GEN64)/lib$(LIB64).a
GENFSLIB := $(GEN)/lib$(LIBTHIS).a

x2src := File MallocToSimple 
CCFLAGS := -D CODE64 -std=c++11 -fpack-struct=1 -I../../include -L$(GEN64) -L$(GEN)

.PHONY : default mkfs.x2fs listf newf clean


#=============================
.ONESHELL:
.SECONDARYEXPANSION:

default:
	make listf
listf:$(GEN)/listf.exe
	# make gen/listf.exe
newf:$(GEN)/newf.exe
	# make gen/newf.exe
$(GEN)/newf.exe:newFile.cpp $(GEN64LIB) $(GENFSLIB)
	g++ $< -o $@ $(CCFLAGS) -Wl,'-(' -l$(LIB64) -l$(LIBTHIS) -Wl,'-)' -static
	
$(GEN)/listf.exe:listFile.cpp $(GEN64LIB) $(GENFSLIB)
	g++ $< -o $@ $(CCFLAGS) -Wl,'-(' -l$(LIB64) -l$(LIBTHIS) -Wl,'-)' -static
	
mkfs.x2fs:$(GEN)/mkfs.x2fs.exe
	# make gen/mkfs.x2fs.exe
$(GEN)/mkfs.x2fs.exe:$(GEN)/mkfs.x2fs.o $(GEN64)/lib$(LIB64).a $(GEN)/lib$(LIBTHIS).a
	g++  $< -o $@ -D CODE64 -std=c++11 -L$(GEN64) -L$(GEN) -Wl,-\( -l$(LIB64) -l$(LIBTHIS) -Wl,-\) -I../../include -fpack-struct=1 -static
$(GEN)/lib$(LIBTHIS).a:$(patsubst %,%.cpp,$(x2src))
	# make gen/libfs.a
	@
	for i in $^;do g++ -c -I../../include -fpack-struct=1 -D CODE64 -std=c++11 $$i -o $$(basename -s .cpp $$i).o;done
	ar crs $(GEN)/lib$(LIBTHIS).a *.o
	rm *.o
$(GEN)/%.o:%.cpp
	g++ -c $< -o $@ -I../../include -D CODE64 -std=c++11 -fpack-struct=1
clean:
	-rm $(GEN)/*	
	

