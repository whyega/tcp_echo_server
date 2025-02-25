# TCP echo server
Простой TCP сервер, экранирующий содержимое текста для HTML

## Зависимости
* [gabime/spdlog](https://github.com/gabime/spdlog) Библиотека для логирования.
* [jarro2783/cxxopts](https://github.com/jarro2783/cxxopts) Библиотека для парсинга аргументов командной строки
* CMake: Система сборки.

## Сборка и запуск
1. Убедитесь, что у вас установлен CMake и компилятор C++ (например, clang или MSVC).
2. Запустите CMake для настройки проекта (`DTCP_ECHO_SERVER_BUILD_TEST` - опция для компиляции примера клиента под Windows):
```bash
cmake -B build -DTCP_ECHO_SERVER_BUILD_TEST=ON
```
3. Соберите проект:
```bash
cmake --build build
```

## Запуск сервера
Откройте папку с готовым бинарным файлом и запустите сервер, передав конфигурацию через аргументы командной строки:
```bash
./tcp_echo_server -p 7777 -m 2 -b 1024 -t 5000
```
* `-p` - Порт сервера
* `-m` - Максимальное количество одновременных подключений (на данный момент бесплолезная, т.к. сервер работает в одном потоке)
* `-b` - Размер буффера для получения данных
* `-t` - Время ожидания запроса от клиента (таймаут)

## Запуск сервера при помощи скрипта
1. Проверьте, установлен ли Python
2. Запустите скрипт `run.py`, который запустит сервер с параметрами `-p 7777 -m 2 -b 1024 -t 5000`
```bash
python run.py
```

## Tcp Client
Файл для проверки работоспособности сервера, компилируется, если при сборке была включена опция `DTCP_ECHO_SERVER_BUILD_TEST`. Принимает на вход два параметра: порт и адрес сервера, в случае успешного подключения и чтения даннных от сервера, создает файл index.html с полученным ответом.
```bash
./tcp_client 7777 127.0.0.1
```
