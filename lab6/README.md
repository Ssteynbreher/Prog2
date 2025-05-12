Собрать и слинковать статическую и динамическую библиотеку с помощью cmake. Выбор библиотеки сделать по флагу -D при вызове cmake.
Сборка статической библиотеки  
gcc app.c -c  
gcc log.c -c  

ar rc libMY_LOG.a log.o  

gcc app.o -o static_exe -L. -lMY_LOG  
./static_exe  

Сборка динамической библиотеки  

gcc app.c -c  
gcc log.c -c -fPIC  

gcc --shared app.o log.o -o libMY_LOG.so
