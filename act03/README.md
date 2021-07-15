[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=4507179&assignment_repo_type=AssignmentRepo)
# Actividad colaborativa - Manejo de procesos
Escribe un programa llamado descending que recibe de línea de comando un número entero positivo.

```
$ .\descending number
```

El programa generará el siguiente árbol de procesos: el proceso inicial creará un hijo de **NIVEL_1**, el proceso de **NIVEL_1** creará dos procesos de **NIVEL_2**, cada proceso de **NIVEL_2** creará tres procesos de nivel **NIVEL_3**; y así sucesivamente **NIVEL_N-1** creará **N** procesos de **NIV EL_N**. Cada proceso deberá desplegar información sobre el id de su padre y su propio id. Los procesos de nivel **N** dormirán 1 segundo antes de terminar. Cada proceso deberá esperar hasta que todos sus hijos hayan terminado. **TIP:** Para que tengas el mismo resultado, emplea el *PID* del proceso inicial cómo base.

Ejemplos de uso:
```
$ .\descending
usage: descending number
--------------------------------------------------------------------------
$ .\descending texto
descending: the parameter must be a positive integer number
--------------------------------------------------------------------------
$ .\descending -10
descending: the parameter must be a positive integer number
--------------------------------------------------------------------------
$ .\descending 0
descending: the parameter must be a positive integer number
--------------------------------------------------------------------------
$ .\descending 3
PPID = 0 PID = 0 NIVEL = 0
	PPID = 0 PID = 1 NIVEL = 1
		PPID = 1 PID = 2 NIVEL = 2
			PPID = 2 PID = 3 NIVEL = 3
			PPID = 2 PID = 4 NIVEL = 3
			PPID = 2 PID = 5 NIVEL = 3
		PPID = 1 PID = 6 NIVEL = 2
			PPID = 6 PID = 7 NIVEL = 3
			PPID = 6 PID = 8 NIVEL = 3
			PPID = 6 PID = 9 NIVEL = 3
```

|     | Ponderación                                                                                                                                                                                                |
|-----|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| +10 | Verifica que el programa reciba la cantidad correcta de<br>parámetros. En caso de que no sea así, el programa<br>despliega un mensaje adecuado y termina, regresando<br>-1 como resultado de su ejecución. |
| +20 | Verifica que number sea un número entero válido (mayor<br>a cero). En caso de que no sea así, el programa<br>despliega un mensaje adecuado y termina, regresando<br>-2 como resultado de su ejecución.     |
| +60 | El programa implementa una solución correcta. Regresa<br>0 como resultado de su ejecución.                                                                                                                 |
