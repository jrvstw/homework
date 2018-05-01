all:
	if [ ! -d "/home/labBook" ]; then\
		mkdir /home/labBook;\
		chown pc341 /home/labBook;\
		chmod 755 /home/labBook;\
	fi
	gcc labBook.c -o labBook
	chown root ./labBook
	chmod +s ./labBook

clean:
	rm -rf /home/labBook
	rm -rf ./labBook
