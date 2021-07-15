[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=4381016&assignment_repo_type=AssignmentRepo)
# Actividad colaborativa - Manejo de directorios
Escribe un programa llamado *find* que recibe de línea de comando una cadena de texto a buscar, un directorio base y, de forma opcional, si queremos que la búsqueda sea recursiva o no.

```
$ .\find string initial_directory [-r]
```

Ejemplos de uso:
```
$ .\find
usage: find string initial_directory [-r]
--------------------------------------------------------------------------
$ .\find apt no_existe
find: No such file or directory
--------------------------------------------------------------------------
$ find apt find.c
find: Not a directory
--------------------------------------------------------------------------
$ .\find apt dir1 -x
usage: find string initial_directory [-r]
--------------------------------------------------------------------------
$ .\find apt dir1
Name: chapter2.txt
Path: dir1

Name: chapter1.txt
Path: dir1
--------------------------------------------------------------------------
$ .\find apt dir1 -r
Name: chapter2.txt
Path: dir1

Name: chapter1.txt
Path: dir1

Name: chapter3.txt
Path: dir1/dir2

Name: chapter4.txt
Path: dir1/dir2

Name: chapter6.txt
Path: dir1/dir2/dir3

Name: chapter5.txt
Path: dir1/dir2/dir3

Name: chapter8.txt
Path: dir1/dir2/dir3/dir4

Name: chapter7.txt
Path: dir1/dir2/dir3/dir4

Name: chapter9.txt
Path: dir1/dir2/dir3/dir4/dir5

Name: chapter10.txt
Path: dir1/dir2/dir3/dir4/dir5
```
|     | Ponderación                                                                                                                                                                                                   |
|-----|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| +10 | Verifica que el programa reciba la cantidad correcta de<br>parámetros. En caso de que no sea así, el programa<br>despliega un mensaje adecuado y termina, regresando<br>-1 como resultado de su ejecución.    |
| +10 | Verifica que el directorio exista. En caso de que no<br>sea un directorio o no exista, el programa despliega<br>un mensaje adecuado y termina, regresando -2 como<br>resultado de su ejecución.               |
| +10 | Verifica que el parámetro para indicar la recursión sea<br>correcto. En caso de que no sea correcto, el programa<br>despliega un mensaje adecuado y termina, regresando<br>-3 como resultado de su ejecución. |
| +30 | Busca **SOLO** dentro del directorio *initial_directory*<br>y muestra los archivos que contienen dentro de su<br>nombre la cadena *string*. Regresa 0 como resultado<br>de su ejecución.                      |
| +30 | Busca **RECURSIVAMENTE** dentro del directorio<br>*initial_directory* y muestra los archivos que contienen<br>dentro de su nombre la cadena *string*. Regresa<br>0 como resultado de su ejecución.            |
