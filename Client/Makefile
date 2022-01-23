TARGET = client

SRCDIRS = $(shell find . -maxdepth 8 -type d)
SRS_CPP = $(foreach dir, $(SRCDIRS) .., $(wildcard $(dir)/*.cpp))
DEP_FILES = $(foreach dir, $(SRCDIRS) .. , $(wildcard $(dir)/*.d))
OBJ_CPP = $(SRS_CPP:.cpp=.o)

LOCAL_CPPFLAGS = -std=c++11
LOCAL_LDFLAGS = -lpthread

$(TARGET) : $(OBJ_CPP)
	g++ -o $@ $^ $(LOCAL_CPPFLAGS) $(LOCAL_LDFLAGS)

ifneq ($(DEP_FILES),)
include $(DEP_FILES)
endif

%.o: %.cpp
	g++ -c -o $@ $< -MD -MF $@.d $(LOCAL_CPPFLAGS) $(LOCAL_LDFLAGS)

all: $(TARGET)

.PHONY:clean
clean:
	rm -rf ./client $(OBJ_CPP)
	rm -rf $(DEP_FILES)