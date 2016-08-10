#
#
#
#
check:main.o logdb.o
	g++ main.o logdb.o -o ../Exec/StaticDetect /usr/include/jsoncpp/libjson.a -L/usr/lib64/mysql -lmysqlclient -lclamav  -I/usr/local/ActiveMQ-CPP/include/activemq-cpp-3.9.2 -I/usr/local/apr//include/apr-1   -L/usr/local/ActiveMQ-CPP/lib -lactivemq-cpp
logdb.o:logdb.cpp
	g++ -c logdb.cpp -o logdb.o 
main.o:main.cpp
	g++ -c main.cpp -o main.o /usr/include/jsoncpp/libjson.a -L/usr/lib64/mysql -lmysqlclient -lclamav  -I/usr/local/ActiveMQ-CPP/include/activemq-cpp-3.9.2 -I/usr/local/apr//include/apr-1   -L/usr/local/ActiveMQ-CPP/lib -lactivemq-cpp 
