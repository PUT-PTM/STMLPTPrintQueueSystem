# STMLPTPrintQueueSystem
# Plan prac
1. Analiza komunikacji miedzy pc a drukarka HP LaserJest 1100
a) przy pomocy stm32f4discovery i https://www.fussylogic.co.uk/blog/?p=1226
b) Jesli okaze sie ze stworzenie zbioru komunikatow dla drukarki na podstawie zdobytych danych jest zbyt czasochlonne/nie mozliwe, wykorzystanie biblioteki z ardurino http://forum.arduino.cc/index.php?topic=74776.0
2. Webserwis dla pracowników do wywoływania kolejnych petentów
a) serwis WWW dla pracowników i administratora
b) mikroserwis do komunikacji serwer <==> stm

3. Przetłumaczenie w.w na j. angielski


# WebSys
This part of system is a standalone web application created using Symfony 3 framework. It will provide basic
functionality for employees to call next petitioner and allow an administrator to define types of issues
and it's signatures on "number in the queue".
