CPP = g++
CFLAGS = -W -Wall -g
LFLAGS = -L/usr/local/lib -lboost_locale-mt -lboost_wserialization-mt -lboost_regex-mt

TARGET = cppjosa.exe
OBJECTS = main.o myevan_korean.o system_text.o

all: $(TARGET)

clean:
	rm -rf *.o
	rm -rf $(TARGET)

depend:
	rm -rf Depend
	touch Depend
	$(CPP) $(CFLAGS) -MM *.cc >> Depend

$(TARGET): $(OBJECTS)
	$(CPP) $(LFLAGS) $(CFLGAS) -o $(TARGET) $^

.cc.o: 
	$(CPP) $(CFLAGS) -c $<

include Depend
