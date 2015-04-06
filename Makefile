CXX = u++					# compile
CXXFLAGS = -g -Wall -Wno-unused-label -MMD -O2
MAKEFLAGS = --no-print-directory

OBJECTS = config.o printer.o bank.o parent.o watcard.o watcardOffice.o student.o nameServer.o vendingMachine.o bottlingPlant.o truck.o driver.o # fill in objects
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = soda

NS_OBJECTS = printer.o watcard.o nameServer.o vendingMachine.o testNameServer.o
NS_DEPENDS = ${NS_OBJECTS:.o=.d}
NS_EXEC = nameServer

BANK_OBJECTS = bank.o testBank.o
BANK_DEPENDS = ${BANK_OBJECTS:.o=.d}
BANK_EXEC = bank

VM_OBJECTS = printer.o watcard.o nameServer.o vendingMachine.o bottlingPlant.o truck.o testVendingMachine.o
VM_DEPENDS = ${VM_OBJECTS:.o=.d}
VM_EXEC = vendingMachine

STUDENT_OBJECTS = printer.o bank.o watcard.o nameServer.o watcardOffice.o vendingMachine.o student.o testStudent.o
STUDENT_DEPENDS = ${STUDENT_OBJECTS:.o=.d}
STUDENT_EXEC = student

PARENT_OBJECTS = printer.o bank.o parent.o testParent.o
PARENT_DEPENDS = ${PARENT_OBJECTS:.o=.d}
PARENT_EXEC = parent

WATCARD_OBJECTS = watcard.o testWatcard.o
WATCARD_DEPENDS = ${WATCARD_OBJECTS:.o=.d}
WATCARD_EXEC = watcard 

PLANT_OBJECTS = printer.o watcard.o nameServer.o vendingMachine.o bottlingPlant.o truck.o testBottlingPlant.o
PLANT_DEPENDS = ${PLANT_OBJECTS:.o=.d}
PLANT_EXEC = bottlingPlant

TRUCK_OBJECTS = printer.o nameServer.o bottlingPlant.o truck.o testTruck.o
TRUCK_DEPENDS = ${TRUCK_OBJECTS:.o=.d}
TRUCK_EXEC = truck

WATCARD_OFFICE_OBJECTS = printer.o bank.o watcard.o watcardOffice.o testWatcardOffice.o
WATCARD_OFFICE_DEPENDS = ${WATCARD_OFFICE_OBJECTS:.o=.d}
WATCARD_OFFICE_EXEC = watcardOffice 

PRINTER_OBJECTS = printer.o testPrinter.o
PRINTER_DEPENDS = ${PRINTER_OBJECTS:.o=.d}
PRINTER_EXEC = printer 

all : ${EXEC}		# build all executables

${NS_EXEC} : ${NS_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${BANK_EXEC} : ${BANK_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${VM_EXEC} : ${VM_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${STUDENT_EXEC} : ${STUDENT_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${PARENT_EXEC} : ${PARENT_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${WATCARD_EXEC} : ${WATCARD_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${PLANT_EXEC} : ${PLANT_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${TRUCK_EXEC} : ${TRUCK_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${WATCARD_OFFICE_EXEC} : ${WATCARD_OFFICE_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${PRINTER_EXEC} : ${PRINTER_OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXEC} ${BANK_EXEC} ${VM_EXEC} ${STUDENT_EXEC} ${PARENT_EXEC} ${WATCARD_EXEC} ${PLANT_EXEC} ${TRUCK_EXEC} ${WATCARD_OFFICE_EXEC} ${PRINTER_EXEC}
