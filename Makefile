CXX = u++					# compile
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -O2
MAKEFLAGS = --no-print-directory

OBJECTS = config.o printer.o bank.o parent.o watcard.o watcardOffice.o student.o nameServer.o vendingMachine.o bottlingPlant.o truck.o driver.o # fill in objects
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda

BANK_OBJECTS = bank.o testBank.o
BANK_DEPENDS = ${BANK_OBJECTS:.o=.d}
BANK_EXEC = bank

VM_OBJECTS = printer.o watcard.o nameServer.o vendingMachine.o testVendingMachine.o
VM_DEPENDS = ${VM_OBJECTS:.o=.d}
VM_EXEC = vendingMachine

WATCARD_OBJECTS = watcard.o testWatcard.o
WATCARD_DEPENDS = ${WATCARD_OBJECTS:.o=.d}
WATCARD_EXEC = watcard 

all : ${EXEC}		# build all executables

${BANK_EXEC} : ${BANK_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${VM_EXEC} : ${VM_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${WATCARD_EXEC} : ${WATCARD_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC}
