# homework1
## Создание сборочной фермы Windows|Linux

## Задание
+ версия пакета увеличивается от сборки к сборке
+ актуальная версия выводится в приветственном сообщении
+ пакет `helloworld`, содержащий исполняемый файл `helloworld_cli`, опубликован в качестве релиза в репозитории

## Native Build
+ mkdir build
+ cd build
+ cmake ../
+ cmake --build . --config Release|Debug

## Install build
+ cmake --install .

## Run tests (GTest & BoostTest)
### Linux
+ cmake --build . --target test --config Release|Debug
### Windows
+ cmake --build . --target RUN_TESTS --config Release|Debug

## CPack (build ZIP & DEB)
+ cpack -C Release|Debug

## Проверка Linux
+ apt update && apt install -y helloworld-0.0.X-Linux.deb
+ (вместо X – номер билда), после запуска бинарного файла:
+ helloworld_cli
+ появилось сообщение:
+ Version: X
+ Hello, World!
+ (вместо X – опять же, номер билда)

## Проверка Windows
+ unzip helloworld-0.0.X-win(64|32).zip
+ (вместо X – номер билда), после запуска бинарного файла:
+ helloworld_cli
+ появилось сообщение:
+ Version: X
+ Hello, World!
+ (вместо X – опять же, номер билда)