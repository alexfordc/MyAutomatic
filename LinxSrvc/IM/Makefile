CUR  = `pwd`
GEN  = $(CUR)/../bin
FLAG = -g -std=c++11 -D_DEBUG 
PTHD = -lpthread
IMLOCAL=../../WinNTKline/MfcUtil/IM
IMFILE=$(IMLOCAL)/IM.cc
CLIENTLOCAL=../../WinNTKline/IMclient
CLIENTFILES=$(IMLOCAL)/IMclient.cpp $(CLIENTLOCAL)/client.cpp
IM:
	[ -z "$(ls $(GEN) &> /dev/null)" ] && mkdir $(GEN) || echo ""
	g++ $(FLAG) $(IMFILE) -o $(GEN)/IM.exe $(PTHD)
client:
	[ -z "$(ls $(GEN) &> /dev/null)" ] && mkdir $(GEN) || echo ""
	g++ $(FLAG) -I$(IMLOCAL) $(CLIENTFILES) -o $(GEN)/client.exe $(PTHD)
Kai:
	g++ -c KaiSocket.cc -std=c++11 -lpthread
all:
	make IM
	make client
clean:
	rm -f $(GEN)/IM.exe $(GEN)/client.exe KaiSocket.o
