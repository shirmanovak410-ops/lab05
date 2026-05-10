[![CI](https://github.com/shirmanovak410-ops/lab05/actions/workflows/ci.yml/badge.svg)](https://github.com/shirmanovak410-ops/lab05/actions/workflows/ci.yml)

# lab05

Проект с настройкой непрерывной интеграции (CI) через GitHub Actions.

В рамках данной лабораторной работы было выполнено следующее:
1) Скопирован репозиторий из lab03:
```bash
git clone https://github.com/shirmanovak410-ops/lab03.git projects/lab05
Клонирование в «projects/lab05»...
remote: Enumerating objects: 28, done.
remote: Counting objects: 100% (28/28), done.
remote: Compressing objects: 100% (19/19), done.
Получение объектов: 100% (28/28), 7.38 КиБ | 7.38 МиБ/с, готово.
Определение изменений: 100% (5/5), готово.
remote: Total 28 (delta 5), reused 21 (delta 3), pack-reused 0 (from 0)
$ cd projects/lab05
$ git remote remove origin
$ git remote add origin https://github.com/shirmanovak410-ops/lab05.git
```
2) Создан конфигурационный файл ci.yml:
```bash
$ cat github/workflows/ci.yml
name: CMake CI

on:
  push:
    branches: [ master, main ]
  pull_request:
    branches: [ master, main ]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
    
    - name: Install CMake
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake cmake-data
    
    - name: Configure CMake
      run: cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install
    
    - name: Build
      run: cmake --build _build
    
    - name: Install
      run: cmake --build _build --target install

```
```bash
$ git add .github/workflows/ci.yml
$ git commit -m "Fix CMake syntax: use -S instead of -H."
[main b14bba3] Fix CMake syntax: use -S instead of -H.
 1 file changed, 23 insertions(+), 64 deletions(-)
```
3) В резьтате выполнения была найдена ошибка в CMakeList.txt, которая была впоследствии исправлена:
  <img width="1445" height="415" alt="image" src="https://github.com/user-attachments/assets/9912f0f8-9d3e-4208-b0ac-d70e2fb8e82a" />
  
4) В данный README.md добавлен бейдж (находится в самом начале).


