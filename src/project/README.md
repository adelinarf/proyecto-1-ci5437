
## ¿Cómo ejecutar?

Los archivos se pueden correr de la siguiente manera:

Si psvn_name y psvn_name_in_txt_format.

		make abstractor

		make psvn_name/psvn_name_in_txt_format.pdb

		make psvn_name.c

Para compilar BFS, A* y IDA*:

		make psvn_name.bfs 

		make psvn_name.astar

		make psvn_name.ida

Para correr los algoritmos:

		./psvn_name.bfs psvn_name.c
		./psvn_name.astar pdb_name.pdb TYPE
		./psvn_name.ida pdb_name.pdb TYPE

TYPE puede ser MANHATTAN, MAX o ADD dependiendo de la heurística que se quiera.

Existen Makefiles dentro de cada una de las carpetas que permiten ejecutar estos comandos.