Instruccions:

Al fitxer "arxiu_configuracio.h" es declara la variable connectionString i a "gestioVideojocs.cpp" (main) s'inicialitza.
En aquest últim fitxer s'han de substituïr el valor de tots els paràmetres que hi apareixen a connectionString, excepte hostaddr. 
Pasos a seguir:

1- Posar al costat de "dbname=" el nom de la base de dades que es vol fer servir.

2- Posar al costat de "user=" el nom d'usuari amb el qual s'accedeix a la base de dades (per defecte, postgres).

3- Posar al costat de "password=" la contrasenya que es fa servir per accedir a la base de dades amb el nom
introduït al pas 1.

4- Posar al costat de "port =" el port del servidor que es vol fer servir (dins de pgadmin, fer click
dret a "PostgreSQL (VERSIO)", que té una icona d'elefant a l'esquerra, fer click a la opció
"Properties", després fer click a la opció "Connection" i a la secció "Port" apareix el port que 
s'ha de fer servir).
