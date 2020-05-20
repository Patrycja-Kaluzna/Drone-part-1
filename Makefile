CXXFLAGS = -g -Iinc -Wall -pedantic -std=c++11

__start__: ./dron_etap_1
	./dron_etap_1

./dron_etap_1: obj/main.o obj/lacze_do_gnuplota.o obj/powierzchnia.o obj/prostopadloscian.o obj/scena.o
	g++ -Wall -pedantic -std=c++11 -o ./dron_etap_1 obj/main.o obj/lacze_do_gnuplota.o obj/powierzchnia.o\
			obj/prostopadloscian.o obj/scena.o

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh inc/scena.hh
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/powierzchnia.o: src/powierzchnia.cpp inc/powierzchnia.hh inc/SWektor.hh
	g++ -c ${CXXFLAGS} -o obj/powierzchnia.o src/powierzchnia.cpp

obj/prostopadloscian.o: src/prostopadloscian.cpp inc/prostopadloscian.hh inc/powierzchnia.hh inc/SMacierz.hh
	g++ -c ${CXXFLAGS} -o obj/prostopadloscian.o src/prostopadloscian.cpp

obj/scena.o: src/scena.cpp inc/scena.hh inc/powierzchnia_wody.hh inc/powierzchnia_dna.hh inc/dron.hh inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/scena.o src/scena.cpp

clean:
	rm -f obj/*.o ./dron_etap_1