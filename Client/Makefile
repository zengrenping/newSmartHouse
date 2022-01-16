obj = ./src/client.o ../Socket_Server.o

LOCAL_CPPFLAGS = -std=c++11
LOCAL_LDFLAGS = -lpthread

client : $(obj)
	g++ -o $@ $^ $(LOCAL_CPPFLAGS) $(LOCAL_LDFLAGS)
clean:
	rm -rf ./client ./src/*.o ./src/action/*.o ../*.o