CXX = u++					# compile
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -O2
MAKEFLAGS = --no-print-directory

OBJECTS = config.o printer.o bank.o parent.o watcard.o watcardOffice.o student.o vendingMachine.o nameServer.o bottlingPlant.o truck.o driver.o # fill in objects
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda

BANK_OBJECTS = bank.o testBank.o
BANK_DEPENDS = ${BANK_OBJECTS:.o=.d}
BANK_EXEC = bank

TRUCK_OBJECTS = printer.o nameServer.o bottlingPlant.o truck.o testTruck.o
TRUCK_DEPENDS = ${TRUCK_OBJECTS:.o=.d}
TRUCK_EXEC = truck

all : ${EXEC}		# build all executables

${BANK_EXEC} : ${BANK_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${TRUCK_EXEC} : ${TRUCK_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} ${BANK_EXEC} ${TRUCK_EXEC}
