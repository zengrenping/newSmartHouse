obj = ./src/main.o ../Socket_Server.o ./src/action/test.o ./src/action/WifiTest.o

LOCAL_CPPFLAGS = -std=c++11
LOCAL_LDFLAGS = -lpthread

smartHouse : $(obj)
	g++ -o $@ $^ $(LOCAL_CPPFLAGS) $(LOCAL_LDFLAGS)
clean:
	rm -rf ./smartHouse ./src/*.o ./src/action/*.o ../*.o