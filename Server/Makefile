TARGET = smartHouse

SRCDIRS = $(shell find . -maxdepth 8 -type d)
SRS_CPP = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
SRS_CPP += ../Socket_Server.cpp ../SendHelper.cpp

OBJ_CPP = $(SRS_CPP:.cpp=.o)

LOCAL_CPPFLAGS = -std=c++11
LOCAL_LDFLAGS = -lpthread

%.o: %.cpp
	g++ -c -o $@ $^ $(LOCAL_CPPFLAGS) $(LOCAL_LDFLAGS)
$(TARGET) : $(OBJ_CPP)
	g++ -o $@ $^ $(LOCAL_CPPFLAGS) $(LOCAL_LDFLAGS)
clean:
	rm -rf ./smartHouse ./src/*.o ./src/action/*.o ../*.o