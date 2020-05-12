# production-barcode-system
Настройка БД:

1) sudo apt update
2) sudo apt install mysql-server

Теперь запуск скрипта настройки (Введите новый пароль. Везде пишите Y и Enter)
- sudo mysql_secure_installation

После настройки:
1) sudo mysql -u root -p // (Нужно ввести пароль, который задали)
2) После того, как зашло: 
    - CREATE USER 'newuser'@'localhost' IDENTIFIED BY '123456789Qqw_!';
    - GRANT ALL PRIVILEGES ON *.* TO 'newuser'@'localhost' WITH GRANT OPTION;
    
Теперь запустите скрипт из папки InitializeDB



	
	
